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

CAN drivers are implemented in the following files:

1. [momentum_can_driver.c](momentum_can_driver.c)
2. [momentum_can_driver.h](momentum_can_driver.h)

The CAN driver relies on a DBC structure defined in
the [can_momentum.dbc](can_momentum.dbc).

- To translate this DBC file into the custom CAN
  structures, [generate_can_defs.py](generate_can_defs.py) is used to generate
  the following files:

    1. [momentum_can_dbc.c](momentum_can_dbc.c)
    2. [momentum_can_dbc.h](momentum_can_dbc.h)

    - These generated files declare the message and signals in the appropriate
      type structs.
