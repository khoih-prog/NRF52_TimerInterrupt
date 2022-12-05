# NRF52_TimerInterrupt Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/NRF52_TimerInterrupt.svg?)](https://www.ardu-badge.com/NRF52_TimerInterrupt)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/NRF52_TimerInterrupt.svg)](https://github.com/khoih-prog/NRF52_TimerInterrupt/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/NRF52_TimerInterrupt/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/NRF52_TimerInterrupt.svg)](http://github.com/khoih-prog/NRF52_TimerInterrupt/issues)


<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>

---
---

## Table of Contents

* [Changelog](#changelog)
  * [Releases v1.4.2](#releases-v142)
  * [Releases v1.4.1](#releases-v141)
  * [Releases v1.4.0](#releases-v140)
  * [Releases v1.3.0](#releases-v130)
  * [Releases v1.2.0](#releases-v120)
  * [Releases v1.1.1](#releases-v111)
  * [Releases v1.0.2](#releases-v102)
  * [Releases v1.0.1](#releases-v101)
  * [Releases v1.0.0](#releases-v100)

---
---

## Changelog

### Releases v1.4.2

1. Add support to Seeeduino nRF52840-based boards such as **Seeed_XIAO_NRF52840 and Seeed_XIAO_NRF52840_SENSE**, etc. using Seeeduino `nRF52` core
2. Add astyle using `allman` style. Restyle the library
3. Update all examples

### Releases v1.4.1

1. Add support to `Sparkfun Pro nRF52840 Mini`
2. Update `Packages_Patches`

### Releases v1.4.0

1. Fix `multiple-definitions` linker error. Drop `src_cpp` and `src_h` directories
2. Add example [multiFileProject](examples/multiFileProject) to demo for multiple-file project.
3. Fix `reattachInterrupt()` bug. Check [bugfix: reattachInterrupt() pass wrong frequency value to setFrequency() #19](https://github.com/khoih-prog/ESP8266TimerInterrupt/pull/19)
4. Add support to Adafruit `NRF52840_LED_GLASSES`
5. Optimize library code by using `reference-passing` instead of `value-passing`
6. Update all examples
7. Update `Packages_Patches`

### Releases v1.3.0

1. Add support to Adafruit nRF52 core v0.22.0+
2. Add support to Raytac MDBT50Q_RX Dongle

**Warnings for Releases v1.2.0-** : Use [`Adafruit nRF52 v0.22.0+`](https://github.com/adafruit/Adafruit_nRF52_Arduino/releases/tag/0.22.0) will create **compiler errors**. If so, please use the [`Adafruit nRF52 v0.21.0`](https://github.com/adafruit/Adafruit_nRF52_Arduino/releases/tag/0.21.0). It's advisable to update to Releases v1.3.0+

### Releases v1.2.0

1. Add better debug feature.
2. Optimize code and examples to reduce RAM usage
3. Add Table of Contents

### Releases v1.1.1

1. Add example [**Change_Interval**](examples/Change_Interval) and [**FakeAnalogWrite**](examples/FakeAnalogWrite)
2. Bump up version to sync with other TimerInterrupt Libraries. Modify Version String.

### Releases v1.0.2

1. Add complicated example [ISR_16_Timers_Array_Complex](examples/ISR_16_Timers_Array_Complex)
2. Optimize examples

### Releases v1.0.1

1. Add complicated example [ISR_16_Timers_Array](examples/ISR_16_Timers_Array) utilizing and demonstrating the full usage of 16 independent ISR Timers.

### Releases v1.0.0

1. Permit up to 16 super-long-time, super-accurate ISR-based timers to avoid being blocked
2. Using cpp code besides Impl.h code to use if Multiple-Definition linker error.


