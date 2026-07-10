# Changelog

---

<details markdown="1">
  <summary>Table of Contents</summary>

<!-- TOC -->
* [Changelog](#changelog)
  * [v0.1.0 (2025-01-13)](#v010--2025-01-13-)
  * [v0.2.0 (2026-03-11)](#v020--2026-03-11-)
  * [v0.2.1 (2026-04-22)](#v021--2026-04-22-)
  * [v0.2.2 (2026-04-22)](#v022--2026-04-22-)
  * [v0.3.0 (2026-04-28)](#v030--2026-04-28-)
  * [v0.3.2 (2026-05-01)](#v032--2026-05-01-)
  * [v0.3.3 (2026-05-03)](#v033--2026-05-03-)
  * [v0.3.4 (2026-06-07)](#v034--2026-06-07-)
  * [v0.3.5 (2026-06-11)](#v035--2026-06-11-)
  * [v0.4.0 (2026-07-06)](#v040--2026-07-06-)
  * [v0.4.1 (2026-07-09)](#v041--2026-07-09-)
  * [v0.4.2 (2026-07-10)](#v042--2026-07-10-)
<!-- TOC -->

</details>

---

## [v0.1.0 (2025-01-13)](https://github.com/scalpelspace/momentum_driver/releases/tag/v0.1.0)

- Initial release.

---

## [v0.2.0 (2026-03-11)](https://github.com/scalpelspace/momentum_driver/releases/tag/v0.2.0)

- Update to new CAN ID scheme.
    - Update DBC CAN IDs and update DBC auto-generated code.
- Minor fixes for DBC including:
    - Renaming of "gps" to "gnss".
    - Simplification of datetime (RTC) message.
- Correct all incorrect references of "gps" to "gnss".

---

## [v0.2.1 (2026-04-22)](https://github.com/scalpelspace/momentum_driver/releases/tag/v0.2.1)

- Update `can_driver` to v0.3.6.
- Minor DBC cleanup (remove unsupported DBC property).

---

## [v0.2.2 (2026-04-22)](https://github.com/scalpelspace/momentum_driver/releases/tag/v0.2.2)

- Fix critical bug in the CAN DBC using signed property incorrectly.
    - Several CAN signals were declared `is_signed = true` while using an
      unsigned-with-bias encoding (`offset = -min_value`), causing
      `physical_to_raw` to clamp raw values at 2^(N-1)-1 and collapse the upper
      half of each physical range to ~0.
    - The fix applied is to flip those signals to `is_signed = false`.

---

## [v0.3.0 (2026-04-28)](https://github.com/scalpelspace/momentum_driver/releases/tag/v0.3.0)

- Add `magnetometer` message as ID 256 and bump subsequent messages.
- Rename IMU messages for specific sensor data type.
- Refactor DBC signal encoding conventions for use of signed signals.
    - Add documentation regarding DBC implementation.

---

## [v0.3.2 (2026-05-01)](https://github.com/scalpelspace/momentum_driver/releases/tag/v0.3.2)

- Add `gnss_utc_get` message as ID 448.
- Add `gnss_utc_get_response` message as ID 480.
- Add `rgb_led_set` message as ID 512.
- Update `can_driver` to v0.3.7.

---

## [v0.3.3 (2026-05-03)](https://github.com/scalpelspace/momentum_driver/releases/tag/v0.3.3)

- Update SPI drivers to add `magnetometer` data.

---

## [v0.3.4 (2026-06-07)](https://github.com/scalpelspace/momentum_driver/releases/tag/v0.3.4)

- Update `can_driver` to v0.3.7.
- Rename CAN bus messages for improved "get" vs "response" clarity.
- Refactor rename `LICENSE.txt` to `LICENSE`.

---

## [v0.3.5 (2026-06-11)](https://github.com/scalpelspace/momentum_driver/releases/tag/v0.3.5)

- Update `state` message to include an 8-bit MCU core temperature value.

---

## [v0.4.0 (2026-07-06)](https://github.com/scalpelspace/momentum_driver/releases/tag/v0.4.0)

- Update `can_driver` for tagged version v0.4.0 for muxed signal support.
    - Update DBC code generation.

---

## [v0.4.1 (2026-07-09)](https://github.com/scalpelspace/momentum_driver/releases/tag/v0.4.1)

- Cleanup `CHANGELOG.md` for formatting and syntax consistency.
- Improve `README.md` docs.

---

## [v0.4.2 (2026-07-10)](https://github.com/scalpelspace/momentum_driver/releases/tag/v0.4.2)

- Update `can_driver` to tagged version v0.5.0.
