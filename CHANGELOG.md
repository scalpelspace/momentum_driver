# Changelog

---

<details markdown="1">
  <summary>Table of Contents</summary>

<!-- TOC -->
* [Changelog](#changelog)
  * [v0.1.0 (2025-01-13)](#v010--2025-01-13-)
  * [v0.2.0 (2026-03-11)](#v020--2026-03-11-)
  * [v0.2.1 (2026-04-22)](#v021--2026-04-22-)
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
