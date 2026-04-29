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
  * [v0.3.0 (WIP)](#v030--wip-)
<!-- TOC -->

</details>

---

## [v0.1.0 (2025-01-13)](https://github.com/scalpelspace/momentum_driver/releases/tag/v0.1.0)

- Initial release.

---

## [v0.2.0 (2026-03-11)](https://github.com/scalpelspace/momentum_driver/releases/tag/v0.2.0)

- **Modifications:**
    - Update to new CAN ID scheme.
        - Update DBC CAN IDs and update DBC auto-generated code.
    - Minor fixes for DBC including:
        - Renaming of "gps" to "gnss".
        - Simplification of datetime (RTC) message.
    - Correct all incorrect references of "gps" to "gnss".

---

## [v0.2.1 (2026-04-22)](https://github.com/scalpelspace/momentum_driver/releases/tag/v0.2.1)

- **Modifications:**
    - Update `can_driver` to `v0.3.6`.
    - Minor DBC cleanup (remove unsupported DBC property).

---

## [v0.2.2 (2026-04-22)](https://github.com/scalpelspace/momentum_driver/releases/tag/v0.2.2)

- **Modifications:**
    - Fix critical bug in the CAN DBC using signed property incorrectly.
        - Several CAN signals were declared `is_signed = true` while using an
          unsigned-with-bias encoding (`offset = -min_value`), causing
          `physical_to_raw` to clamp raw values at 2^(N-1)-1 and collapse the
          upper
          half of each physical range to ~0.
        - The fix applied is to flip those signals to `is_signed = false`.

---

## [v0.3.0 (WIP)](https://github.com/scalpelspace/momentum_driver/releases/tag/v0.3.0)

- **Modifications:**
    - Add `magnetometer` message as ID `256` and bump subsequent messages.
    - Rename IMU messages for specific sensor data type.
    - Refactor DBC signal encoding conventions for use of signed signals.
        - Add documentation regarding DBC implementation.
