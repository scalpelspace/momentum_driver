# momentum_driver

Low level communication drivers for the Momentum sensor board running
the [`momentum`](https://github.com/scalpelspace/momentum) firmware.

---

<details markdown="1">
  <summary>Table of Contents</summary>

<!-- TOC -->
* [momentum_driver](#momentum_driver)
  * [1 Overview](#1-overview)
  * [2 CAN Bus Drivers](#2-can-bus-drivers)
  * [3 CAN Bus Messages](#3-can-bus-messages)
    * [3.1 Message Table](#31-message-table)
    * [3.2 Additional Notes](#32-additional-notes)
  * [4 SPI Drivers](#4-spi-drivers)
    * [4.1 Frame Format](#41-frame-format)
    * [4.2 Frame Types](#42-frame-types)
<!-- TOC -->

</details>

---

## 1 Overview

CAN drivers are included in the [`momentum_driver.h`](momentum_driver.h) file
for
simple implementation.

This repository defines the CAN **protocol contract** for Momentum: message IDs,
DLCs, signal layouts and scaling. The source of truth is the DBC file: [
`can_momentum.dbc`](can_momentum.dbc).

> **Note:** Behavioural semantics (controls state machine, safety gating of
> config commands, telemetry rates, fault handling) are owned by the
> [`momentum`](https://github.com/scalpelspace/momentum) firmware and are
> documented there.

---

## 2 CAN Bus Drivers

CAN drivers are implemented via the [
`can_driver`](https://github.com/scalpelspace/can_driver) submodule.

All CAN IDs follow the ScalpelSpace node CAN ID standard defined by
`can_driver`: the 11-bit classic CAN ID is split into a 6-bit `message_id` and
a 5-bit `node_id`, so a node's on-bus ID is its base message ID plus its
assigned node ID. Node IDs `0` (unassigned) and `31` (broadcast) are reserved,
and node IDs are assigned at runtime via the dynamic allocation protocol.

> See the [`can_driver` README](can_driver/README.md) for the full ID scheme,
> reserved ID ranges and the node ID allocation protocol.

---

## 3 CAN Bus Messages

### 3.1 Message Table

Direction is from the Momentum node's perspective: **TX** = transmitted by
Momentum, **RX** = received by Momentum.

| Base ID (hex) | Message                 | DLC | Direction | Description                                                    |
|--------------:|-------------------------|----:|-----------|----------------------------------------------------------------|
|          0x20 | `state`                 |   2 | TX        | System state and MCU temperature.                              |
|          0x40 | `barometric`            |   8 | TX        | Barometric pressure, temperature and sensor state.             |
|          0x60 | `gnss1`                 |   8 | TX        | GNSS latitude and longitude.                                   |
|          0x80 | `gnss2`                 |   8 | TX        | GNSS speed, course, position fix, satellite count and HDOP.    |
|          0xA0 | `gnss3`                 |   7 | TX        | GNSS altitude, geoid separation and sensor state.              |
|          0xC0 | `quaternion`            |   8 | TX        | IMU rotation quaternion (x, y, z, w).                          |
|          0xE0 | `gyroscope`             |   6 | TX        | IMU calibrated gyroscope (x, y, z).                            |
|         0x100 | `magnetometer`          |   8 | TX        | IMU calibrated magnetometer (x, y, z).                         |
|         0x120 | `accelerometer`         |   6 | TX        | IMU calibrated accelerometer (x, y, z).                        |
|         0x140 | `linear_accelerometer`  |   6 | TX        | IMU linear acceleration, gravity removed (x, y, z).            |
|         0x160 | `gravity_accelerometer` |   6 | TX        | IMU gravity vector (x, y, z).                                  |
|         0x180 | `datetime_get`          |   0 | RX        | Request the RTC date and time.                                 |
|         0x1A0 | `datetime_response`     |   7 | TX        | Response to `datetime_get`: RTC date, weekday and time.        |
|         0x1C0 | `gnss_utc_get`          |   0 | RX        | Request the GNSS UTC date and time.                            |
|         0x1E0 | `gnss_utc_response`     |   7 | TX        | Response to `gnss_utc_get`: GNSS UTC date and time.            |
|         0x200 | `rgb_led_set`           |   3 | RX        | Set the on-board RGB LED colour.                               |
|         0x3C0 | `version_get`           |   0 | RX        | Request the firmware version.                                  |
|         0x3E0 | `version_response`      |   4 | TX        | Response to `version_get`: major, minor, patch and identifier. |

### 3.2 Additional Notes

The `temperature` signal in `barometric` uses `@1+` unsigned despite having
negative values. The full -40 to +85 degC span requires ~65534 raw counts,
exceeding the signed 16-bit limit of 32767.

`quaternion` message components are bounded at +-0.99998, not +-1. The
`BNO085`/`BNO086` uses Q15 fixed-point internally and physically cannot output
exactly +-1.0.

---

## 4 SPI Drivers

SPI drivers are directly implemented in the following files:

1. [`momentum_spi_driver.c`](momentum_spi_driver.c)
2. [`momentum_spi_driver.h`](momentum_spi_driver.h)

### 4.1 Frame Format

All SPI communication uses a fixed `momentum_frame_t` frame:

| Field            | Size (bytes) | Description                                                                                           |
|------------------|-------------:|-------------------------------------------------------------------------------------------------------|
| `start_of_frame` |            1 | Start of frame (SOF), identifies the frame category.                                                  |
| `frame_type`     |            1 | Frame type identifier (see [4.2 Frame Types](#42-frame-types)).                                       |
| `sequence`       |            1 | Roll-over counter.                                                                                    |
| `length`         |            1 | Number of valid payload bytes.                                                                        |
| `payload`        |           32 | Data payload (`MOMENTUM_MAX_DATA_SIZE`).                                                              |
| `crc`            |            2 | CRC-16-CCITT (initial value `0xFFFF`) computed over `frame_type`, `sequence`, `length` and `payload`. |

SOF values:

| SOF    | Frame category | Description                                |
|--------|----------------|--------------------------------------------|
| `0x00` | Command        | Master command, no response from Momentum. |
| `0x40` | Request        | Master request for data.                   |
| `0x41` | Response       | Momentum response to a request.            |

### 4.2 Frame Types

Command frame types (no response from Momentum):

| Frame type | Name    | Description               |
|------------|---------|---------------------------|
| `0x06`     | `RESET` | Reset the Momentum board. |
| `0x10`     | `LED`   | Set the on-board RGB LED. |

Request/response frame types (IMU types are the SH-2 report ID + `0x70`):

| Frame type | Name             | Description                                           |
|------------|------------------|-------------------------------------------------------|
| `0x42`     | `VERSION`        | Firmware version: major, minor, patch and identifier. |
| `0x71`     | `IMU_ACCEL`      | IMU calibrated accelerometer (x, y, z).               |
| `0x72`     | `IMU_GYRO`       | IMU calibrated gyroscope (x, y, z).                   |
| `0x73`     | `IMU_MAG`        | IMU calibrated magnetometer (x, y, z).                |
| `0x74`     | `IMU_LINACCEL`   | IMU linear acceleration, gravity removed (x, y, z).   |
| `0x75`     | `IMU_QUAT`       | IMU rotation quaternion (i, j, k, real) and accuracy. |
| `0x76`     | `IMU_GRAV`       | IMU gravity vector (x, y, z).                         |
| `0xA0`     | `BAR_ENV`        | Barometric pressure and temperature.                  |
| `0xB0`     | `GNSS_DATETIME`  | GNSS date and time.                                   |
| `0xB1`     | `GNSS_COORD`     | GNSS latitude and longitude with directions.          |
| `0xB2`     | `GNSS_ALT_SPEED` | GNSS altitude, geoid separation and ground speed.     |
| `0xB3`     | `GNSS_HEAD`      | GNSS course and magnetic variation.                   |
| `0xB4`     | `GNSS_STATS`     | GNSS position fix, satellite count and HDOP.          |

Received frames are validated by `parse_momentum_response_frame`, which returns
a `momentum_status_t`: `MOMENTUM_OK`, `MOMENTUM_ERROR_CRC` (CRC mismatch),
`MOMENTUM_ERROR_FRAME_TYPE` (unknown frame type) or `MOMENTUM_ERROR_BAD_FRAME`
(invalid SOF or length).
