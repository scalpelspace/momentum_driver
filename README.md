# momentum_driver

![black_formatter](https://github.com/scalpelspace/momentum_driver/actions/workflows/black_formatter.yaml/badge.svg)

Low level communication drivers for the Momentum dev board running the [
`momentum`](https://github.com/scalpelspace/momentum) firmware.

---

<details markdown="1">
  <summary>Table of Contents</summary>

<!-- TOC -->
* [momentum_driver](#momentum_driver)
  * [1 Overview](#1-overview)
  * [2 SPI Drivers](#2-spi-drivers)
  * [3 CAN Bus Drivers](#3-can-bus-drivers)
    * [3.1 CAN DBC Notes](#31-can-dbc-notes)
<!-- TOC -->

</details>

---

## 1 Overview

The Momentum dev board provides 3 direct communication interfaces:

1. UART-to-USB
2. SPI
3. CAN (classic)

**SPI and CAN** are supported natively through the software included in this
driver package. The UART-to-USB interface is intended primarily as a programming
or customizable interface for advanced users.

Both SPI and CAN drivers are included in
the [momentum_driver.h](momentum_driver.h) file for simple implementation.

---

## 2 SPI Drivers

SPI drivers are directly implemented in the following files:

1. [momentum_spi_driver.c](momentum_spi_driver.c)
2. [momentum_spi_driver.h](momentum_spi_driver.h)

---

## 3 CAN Bus Drivers

CAN drivers are implemented via
the [`can_driver`](https://github.com/scalpelspace/can_driver) submodule.

### 3.1 CAN DBC Notes

The `temperature` signal in `barometric` uses `@1+` unsigned despite having
negative values. The full -40 to +85 degC span requires ~65534 raw counts,
exceeding the signed 16-bit limit of 32767.

`quaternion` message components are bounded at +-0.99998, not +-1. The
`BNO085`/`BNO086` uses Q15 fixed-point internally and physically cannot output
exactly +-1.0.
