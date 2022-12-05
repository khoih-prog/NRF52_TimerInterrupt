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

* [Important Change from v1.4.0](#Important-Change-from-v140)
* [Why do we need this NRF52_TimerInterrupt library](#why-do-we-need-this-nrf52_timerinterrupt-library)
  * [Features](#features)
  * [Why using ISR-based Hardware Timer Interrupt is better](#why-using-isr-based-hardware-timer-interrupt-is-better)
  * [Currently supported Boards](#currently-supported-boards)
  * [Important Notes about ISR](#important-notes-about-isr)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For Adafruit nRF52840 and nRF52832 boards](#1-for-adafruit-nRF52840-and-nRF52832-boards)
* [Libraries' Patches](#libraries-patches)
  * [1. For application requiring 2K+ HTML page](#1-for-application-requiring-2k-html-page)
  * [2. For Ethernet library](#2-for-ethernet-library)
  * [3. For EthernetLarge library](#3-for-ethernetlarge-library)
  * [4. For Etherne2 library](#4-for-ethernet2-library)
  * [5. For Ethernet3 library](#5-for-ethernet3-library)
  * [6. For UIPEthernet library](#6-for-uipethernet-library)
* [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)
* [New from v1.0.0](#new-from-v100)
* [Usage](#usage)
  * [1. Using only Hardware Timer directly](#1-using-only-hardware-timer-directly)
    * [1.1 Init Hardware Timer](#11-init-hardware-timer)
    * [1.2 Set Hardware Timer Interval and attach Timer Interrupt Handler function](#12-set-hardware-timer-interval-and-attach-timer-interrupt-handler-function)
    * [1.3 Set Hardware Timer Frequency and attach Timer Interrupt Handler function](#13-set-hardware-timer-frequency-and-attach-timer-interrupt-handler-function)
  * [2. Using 16 ISR_based Timers from 1 Hardware Timer](#2-using-16-isr_based-timers-from-1-hardware-timer)
    * [2.1 Important Note](#21-important-note)
    * [2.2 Init Hardware Timer and ISR-based Timer](#22-init-hardware-timer-and-isr-based-timer)
    * [2.3 Set Hardware Timer Interval and attach Timer Interrupt Handler functions](#23-set-hardware-timer-interval-and-attach-timer-interrupt-handler-functions)
* [Examples](#examples)
  * [  1. Argument_None](examples/Argument_None)
  * [  2. ISR_16_Timers_Array](examples/ISR_16_Timers_Array)
  * [  3. ISR_16_Timers_Array_Complex](examples/ISR_16_Timers_Array_Complex)
  * [  4. ISR_RPM_Measure](examples/ISR_RPM_Measure)
  * [  5. ISR_Timer_Complex_Ethernet](examples/ISR_Timer_Complex_Ethernet)
  * [  6. ISR_Timer_Complex_WiFiNINA](examples/ISR_Timer_Complex_WiFiNINA)
  * [  7. RPM_Measure](examples/RPM_Measure)
  * [  8. SwitchDebounce](examples/SwitchDebounce)
  * [  9. TimerInterruptTest](examples/TimerInterruptTest)
  * [ 10. TimerInterruptLEDDemo](examples/TimerInterruptLEDDemo)
  * [ 11. **FakeAnalogWrite**](examples/FakeAnalogWrite)
  * [ 12. **Change_Interval**](examples/Change_Interval)
  * [ 13. **multiFileProject**](examples/multiFileProject) **New**
* [Example ISR_16_Timers_Array_Complex](#example-ISR_16_Timers_Array_Complex)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. ISR_Timer_Complex_Ethernet on Adafruit NRF52840_FEATHER using W5500 Ethernet](#1-isr_timer_complex_ethernet-on-adafruit-nrf52840_feather-using-w5500-ethernet)
  * [2. TimerInterruptTest on Adafruit NRF52840_FEATHER](#2-timerinterrupttest-on-adafruit-nrf52840_feather)
  * [3. Argument_None on Adafruit NRF52840_FEATHER](#3-argument_none-on-adafruit-nrf52840_feather)
  * [4. ISR_16_Timers_Array_Complex on Adafruit NRF52840_FEATHER](#4-isr_16_timers_array_complex-on-adafruit-nrf52840_feather)
  * [5. SwitchDebounce on Adafruit NRF52840_FEATHER](#5-switchdebounce-on-adafruit-nrf52840_feather)
  * [6. Change_Interval on Adafruit NRF52840_FEATHER](#6-change_interval-on-adafruit-nrf52840_feather)
  * [7. FakeAnalogWrite on Adafruit NRF52840_FEATHER](#7-fakeanalogwrite-on-adafruit-nrf52840_feather)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Releases](#releases)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Important Change from v1.4.0

Please have a look at [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)

### Why do we need this [NRF52_TimerInterrupt library](https://github.com/khoih-prog/NRF52_TimerInterrupt)

### Features

This library enables you to use Interrupt from Hardware Timers on an nRF52-based board, such as AdaFruit Itsy-Bitsy nRF52840, Feather nRF52840 Express, etc.

As **Hardware Timers are rare, and very precious assets** of any board, this library now enables you to use up to **16 ISR-based Timers, while consuming only 1 Hardware Timer**. Timers' interval is very long (**ulong millisecs**).

Now with these new **16 ISR-based timers**, the maximum interval is **practically unlimited** (limited only by unsigned long milliseconds) while **the accuracy is nearly perfect** compared to software timers. 

The most important feature is they're ISR-based timers. Therefore, their executions are **not blocked by bad-behaving functions / tasks**. This important feature is absolutely necessary for mission-critical tasks. 

The [**ISR_Timer_Complex**](examples/ISR_Timer_Complex) example will demonstrate the nearly perfect accuracy compared to software timers by printing the actual elapsed millisecs of each type of timers.

Being ISR-based timers, their executions are not blocked by bad-behaving functions / tasks, such as connecting to WiFi, Internet and Blynk services. You can also have many `(up to 16)` timers to use.

This non-being-blocked important feature is absolutely necessary for mission-critical tasks.

You'll see blynkTimer Software is blocked while system is connecting to WiFi / Internet / Blynk, as well as by blocking task 
in loop(), using delay() function as an example. The elapsed time then is very unaccurate

### Why using ISR-based Hardware Timer Interrupt is better

Imagine you have a system with a **mission-critical** function, measuring water level and control the sump pump or doing something much more important. You normally use a software timer to poll, or even place the function in loop(). But what if another function is **blocking** the loop() or setup().

So your function **might not be executed, and the result would be disastrous.**

You'd prefer to have your function called, no matter what happening with other functions (busy loop, bug, etc.).

The correct choice is to use a Hardware Timer with **Interrupt** to call your function.

These hardware timers, using interrupt, still work even if other functions are blocking. Moreover, they are much more **precise** (certainly depending on clock frequency accuracy) than other software timers using millis() or micros(). That's necessary if you need to measure some data requiring better accuracy.

Functions using normal software timers, relying on loop() and calling millis(), won't work if the loop() or setup() is blocked by certain operation. For example, certain function is blocking while it's connecting to WiFi or some services.

The catch is **your function is now part of an ISR (Interrupt Service Routine), and must be lean / mean, and follow certain rules.** More to read on:

[**HOWTO Attach Interrupt**](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)

---

### Currently supported Boards

1. **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox etc.**
2. **Sparkfun Pro nRF52840 Mini**
3. **Seeeduino nRF52840-based boards such as SEEED_XIAO_NRF52840 and SEEED_XIAO_NRF52840_SENSE**, etc. using Seeeduino `nRF%2` core

---

### Important Notes about ISR

1. Inside the attached function, **delay() won’t work and the value returned by millis() will not increment.** Serial data received while in the function may be lost. You should declare as **volatile any variables that you modify within the attached function.**

2. Typically global variables are used to pass data between an ISR and the main program. To make sure variables shared between an ISR and the main program are updated correctly, declare them as volatile.


---
---

## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`Adafruit nRF52 v1.3.0+`](https://github.com/adafruit/Adafruit_nRF52_Arduino) for nRF52 boards such as Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, **NINA_B302_ublox**, etc. [![GitHub release](https://img.shields.io/github/release/adafruit/Adafruit_nRF52_Arduino.svg)](https://github.com/adafruit/Adafruit_nRF52_Arduino/releases/latest)
 3. [`Seeeduino nRF52 core 1.0.0+`](https://github.com/Seeed-Studio/Adafruit_nRF52_Arduino) for Seeeduino nRF52840-based boards such as **Seeed_XIAO_NRF52840 and Seeed_XIAO_NRF52840_SENSE**. [![GitHub release](https://img.shields.io/github/release/Seeed-Studio/Adafruit_nRF52_Arduino.svg)](https://github.com/Seeed-Studio/Adafruit_nRF52_Arduino/releases/latest)
 4. [`Blynk library 1.1.0`](https://github.com/blynkkk/blynk-library/releases). [![Latest release](https://img.shields.io/github/release/blynkkk/blynk-library.svg)](https://github.com/blynkkk/blynk-library/releases/latest/) to use with certain example.
 5. To use with certain example, depending on which Ethernet card you're using:
   - [`Ethernet_Generic library v2.7.1+`](https://github.com/khoih-prog/Ethernet_Generic) for W5100, W5200 and W5500.  [![GitHub release](https://img.shields.io/github/release/khoih-prog/Ethernet_Generic.svg)](https://github.com/khoih-prog/Ethernet_Generic/releases/latest)
   - [`EthernetENC library v2.0.3+`](https://github.com/jandrassy/EthernetENC) for ENC28J60. [![GitHub release](https://img.shields.io/github/release/jandrassy/EthernetENC.svg)](https://github.com/jandrassy/EthernetENC/releases/latest). **New and Better**
   - [`UIPEthernet library v2.0.12+`](https://github.com/UIPEthernet/UIPEthernet) for ENC28J60. [![GitHub release](https://img.shields.io/github/release/UIPEthernet/UIPEthernet.svg)](https://github.com/UIPEthernet/UIPEthernet/releases/latest)
 6. [`WiFiNINA_Generic library v1.8.15-1+`](https://github.com/khoih-prog/WiFiNINA_Generic) to use WiFiNINA modules/shields. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiNINA_Generic.svg?)](https://www.ardu-badge.com/WiFiNINA_Generic) if using WiFiNINA for boards such as nRF52, etc.
 7. [`Blynk_WiFiNINA_WM library 1.1.2+`](https://github.com/khoih-prog/Blynk_WiFiNINA_WM) to use with Blynk-WiFiNINA-related example. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/Blynk_WiFiNINA_WM.svg?)](https://www.ardu-badge.com/Blynk_WiFiNINA_WM)
 8. To use with certain example
   - [`SimpleTimer library`](https://github.com/jfturcot/SimpleTimer) for [ISR_16_Timers_Array](examples/ISR_16_Timers_Array) and [ISR_16_Timers_Array_Complex](examples/ISR_16_Timers_Array_Complex) examples.
   
---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for [**NRF52_TimerInterrupt**](https://github.com/khoih-prog/NRF52_TimerInterrupt), then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/NRF52_TimerInterrupt.svg?)](https://www.ardu-badge.com/NRF52_TimerInterrupt) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [**NRF52_TimerInterrupt**](https://github.com/khoih-prog/NRF52_TimerInterrupt) page.
2. Download the latest release `NRF52_TimerInterrupt-main.zip`.
3. Extract the zip file to `NRF52_TimerInterrupt-main` directory 
4. Copy whole `NRF52_TimerInterrupt-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**NRF52_TimerInterrupt** library](https://registry.platformio.org/libraries/khoih-prog/NRF52_TimerInterrupt) by using [Library Manager](https://registry.platformio.org/libraries/NRF52_TimerInterrupt/installation). Search for **NRF52_TimerInterrupt** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

#### 1. For Adafruit nRF52840 and nRF52832 boards

**To be able to compile, run and automatically detect and display BOARD_NAME on nRF52840/nRF52832 boards**, you have to copy the whole [nRF52 1.3.0](Packages_Patches/adafruit/hardware/nrf52/1.3.0) directory into Adafruit nRF52 directory (~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0). 

Supposing the Adafruit nRF52 version is 1.3.0. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**

---

To use `Sparkfun Pro nRF52840 Mini`, you must install `Packages_Patches` and use Adafruit nrf52 core v1.0.0+

---
---

### Libraries' Patches

#### Notes: These patches are totally optional and necessary only when you use the related Ethernet library and get certain error or issues.

#### 1. For application requiring 2K+ HTML page

If your application requires 2K+ HTML page, the current [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) must be modified if you are using W5200/W5500 Ethernet shields. W5100 is not supported for 2K+ buffer. If you use boards requiring different CS/SS pin for W5x00 Ethernet shield, for example ESP32, ESP8266, nRF52, etc., you also have to modify the following libraries to be able to specify the CS/SS pin correctly.

#### 2. For Ethernet library

To fix [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet), just copy these following files into the [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) directory to overwrite the old files:
- [Ethernet.h](LibraryPatches/Ethernet/src/Ethernet.h)
- [Ethernet.cpp](LibraryPatches/Ethernet/src/Ethernet.cpp)
- [EthernetServer.cpp](LibraryPatches/Ethernet/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/Ethernet/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/Ethernet/src/utility/w5100.cpp)

#### 3. For EthernetLarge library

To fix [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge), just copy these following files into the [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge) directory to overwrite the old files:
- [EthernetLarge.h](LibraryPatches/EthernetLarge/src/EthernetLarge.h)
- [EthernetLarge.cpp](LibraryPatches/EthernetLarge/src/EthernetLarge.cpp)
- [EthernetServer.cpp](LibraryPatches/EthernetLarge/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/EthernetLarge/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/EthernetLarge/src/utility/w5100.cpp)


#### 4. For Ethernet2 library

To fix [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2), just copy these following files into the [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2) directory to overwrite the old files:

- [Ethernet2.h](LibraryPatches/Ethernet2/src/Ethernet2.h)
- [Ethernet2.cpp](LibraryPatches/Ethernet2/src/Ethernet2.cpp)

To add UDP Multicast support, necessary for the [**UPnP_Generic library**](https://github.com/khoih-prog/UPnP_Generic):

- [EthernetUdp2.h](LibraryPatches/Ethernet2/src/EthernetUdp2.h)
- [EthernetUdp2.cpp](LibraryPatches/Ethernet2/src/EthernetUdp2.cpp)

#### 5. For Ethernet3 library

5. To fix [`Ethernet3 library`](https://github.com/sstaub/Ethernet3), just copy these following files into the [`Ethernet3 library`](https://github.com/sstaub/Ethernet3) directory to overwrite the old files:
- [Ethernet3.h](LibraryPatches/Ethernet3/src/Ethernet3.h)
- [Ethernet3.cpp](LibraryPatches/Ethernet3/src/Ethernet3.cpp)

#### 6. For UIPEthernet library

***To be able to compile and run on nRF52 boards with ENC28J60 using UIPEthernet library***, you have to copy these following files into the UIPEthernet `utility` directory to overwrite the old files:

- For [UIPEthernet v2.0.8](https://github.com/UIPEthernet/UIPEthernet)

  - [UIPEthernet.h](LibraryPatches/UIPEthernet/UIPEthernet.h)
  - [UIPEthernet.cpp](LibraryPatches/UIPEthernet/UIPEthernet.cpp)
  - [Enc28J60Network.h](LibraryPatches/UIPEthernet/utility/Enc28J60Network.h)
  - [Enc28J60Network.cpp](LibraryPatches/UIPEthernet/utility/Enc28J60Network.cpp)

- For [UIPEthernet v2.0.9](https://github.com/UIPEthernet/UIPEthernet)

  - [UIPEthernet.h](LibraryPatches/UIPEthernet-2.0.9/UIPEthernet.h)
  - [UIPEthernet.cpp](LibraryPatches/UIPEthernet-2.0.9/UIPEthernet.cpp)
  - [Enc28J60Network.h](LibraryPatches/UIPEthernet-2.0.9/utility/Enc28J60Network.h)
  - [Enc28J60Network.cpp](LibraryPatches/UIPEthernet-2.0.9/utility/Enc28J60Network.cpp)

---
---

### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using `xyz-Impl.h` instead of standard `xyz.cpp`, possibly creates certain `Multiple Definitions` Linker error in certain use cases.

You can include `.hpp`

```cpp
// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "NRF52TimerInterrupt.hpp"     //https://github.com/khoih-prog/NRF52_TimerInterrupt

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "NRF52_ISR_Timer.hpp"         //https://github.com/khoih-prog/NRF52_TimerInterrupt
```

in many files. But be sure to use the following `.h` files **in just 1 `.h`, `.cpp` or `.ino` file**, which must **not be included in any other file**, to avoid `Multiple Definitions` Linker Error

```cpp
// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "NRF52TimerInterrupt.h"       //https://github.com/khoih-prog/NRF52_TimerInterrupt

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "NRF52_ISR_Timer.h"           //https://github.com/khoih-prog/NRF52_TimerInterrupt
```

---
---


## New from v1.0.0

Now with these new `16 ISR-based timers` (while consuming only **1 hardware timer**), the maximum interval is practically unlimited (limited only by unsigned long milliseconds). The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers Therefore, their executions are not blocked by bad-behaving functions / tasks.
This important feature is absolutely necessary for mission-critical tasks. 

The [**ISR_16_Timers_Array**](examples/ISR_16_Timers_Array), [**ISR_Timer_Complex_Ethernet**](examples/ISR_Timer_Complex_Ethernet) and [**ISR_Timer_Complex_WiFiNINA**](examples/ISR_Timer_Complex_WiFiNINA) examples will demonstrate the nearly perfect accuracy compared to software timers by printing the actual elapsed millisecs of each type of timers.
Being ISR-based timers, their executions are not blocked by bad-behaving functions / tasks, such as connecting to WiFi, Internet and Blynk services. You can also have many `(up to 16)` timers to use.
This non-being-blocked important feature is absolutely necessary for mission-critical tasks. 
You'll see blynkTimer Software is blocked while system is connecting to WiFi / Internet / Blynk, as well as by blocking task 
in loop(), using delay() function as an example. The elapsed time then is very unaccurate

---
---

## Usage

Before using any Timer, you have to make sure the Timer has not been used by any other purpose.

### 1. Using only Hardware Timer directly

### 1.1 Init Hardware Timer

```cpp
// Depending on the board, you can select NRF52 Hardware Timer from NRF_TIMER_1-NRF_TIMER_4 (1 to 4)
// If you select the already-used NRF_TIMER_0, it'll be auto modified to use NRF_TIMER_1

// Init NRF52 timer NRF_TIMER1
NRF52Timer ITimer(NRF_TIMER_1);
```

### 1.2 Set Hardware Timer Interval and attach Timer Interrupt Handler function

Use one of these functions with **interval in unsigned long milliseconds**

```cpp
// interval (in microseconds).
// No params and duration now. To be added in the future by adding similar functions here or to NRF52-hal-timer.c
bool setInterval(unsigned long interval, timerCallback callback);

// interval (in microseconds).
// No params and duration now. To be added in the future by adding similar functions here or to NRF52-hal-timer.c
bool attachInterruptInterval(unsigned long interval, timerCallback callback);
```

as follows


```cpp
void TimerHandler(void)
{
  // Doing something here inside ISR
}

#define TIMER_INTERVAL_MS        1000      // 1s = 1000ms
void setup()
{
  ....
  
  // Interval in microsecs
  if (ITimer.attachInterruptInterval(TIMER_INTERVAL_MS * 1000, TimerHandler0))
  {
    Serial.print(F("Starting ITimer0 OK, millis() = ")); Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer0. Select another freq. or timer));
}  
```

### 1.3 Set Hardware Timer Frequency and attach Timer Interrupt Handler function

Use one of these functions with **frequency in float Hz**

```cpp
// frequency (in hertz).
// No params and duration now. To be added in the future by adding similar functions here or to NRF52-hal-timer.c
bool setFrequency(float frequency, timerCallback callback);

// frequency (in hertz).
bool attachInterrupt(float frequency, timerCallback callback);
```

as follows

```cpp
void TimerHandler0()
{
  // Doing something here inside ISR
}

#define TIMER0_FREQ_HZ        5555.555

void setup()
{
  ....
  
  // Frequency in float Hz
  if (ITimer0.attachInterrupt(TIMER0_FREQ_HZ, TimerHandler0))
  {
    Serial.print(F("Starting ITimer0 OK, millis() = ")); Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer0. Select another freq. or timer));
}  
```

### 2. Using 16 ISR_based Timers from 1 Hardware Timer

### 2.1 Important Note

The 16 ISR_based Timers, designed for long timer intervals, only support using **unsigned long millisec intervals**. If you have to use much higher frequency or sub-millisecond interval, you have to use the Hardware Timers directly as in [1.3 Set Hardware Timer Frequency and attach Timer Interrupt Handler function](#13-set-hardware-timer-frequency-and-attach-timer-interrupt-handler-function)


### 2.2 Init Hardware Timer and ISR-based Timer

```cpp
/// Depending on the board, you can select NRF52 Hardware Timer from NRF_TIMER_1-NRF_TIMER_4 (1 to 4)
// If you select the already-used NRF_TIMER_0, it'll be auto modified to use NRF_TIMER_1

// Init NRF52 timer NRF_TIMER2
NRF52Timer ITimer(NRF_TIMER_2);

// Init NRF52_ISR_Timer
// Each NRF52_ISR_Timer can service 16 different ISR-based timers
NRF52_ISR_Timer ISR_Timer;
```

### 2.3 Set Hardware Timer Interval and attach Timer Interrupt Handler functions

```cpp
void TimerHandler(void)
{
  ISR_Timer.run();
}

#define HW_TIMER_INTERVAL_MS          50L

#define TIMER_INTERVAL_2S             2000L
#define TIMER_INTERVAL_5S             5000L
#define TIMER_INTERVAL_11S            11000L
#define TIMER_INTERVAL_101S           101000L

// In NRF52, avoid doing something fancy in ISR, for example complex Serial.print with String() argument
// The pure simple Serial.prints here are just for demonstration and testing. Must be eliminate in working environment
// Or you can get this run-time error / crash
void doingSomething2s()
{
  // Doing something here inside ISR
}
  
void doingSomething5s()
{
  // Doing something here inside ISR
}

void doingSomething11s()
{
  // Doing something here inside ISR
}

void doingSomething101s()
{
  // Doing something here inside ISR
}

void setup()
{
  ....
  
  // Interval in microsecs
  if (ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_MS * 1000, TimerHandler))
  {
    lastMillis = millis();
    Serial.print(F("Starting ITimer OK, millis() = ")); Serial.println(lastMillis);
  }
  else
    Serial.println(F("Can't set ITimer correctly. Select another freq. or interval"));

  // Just to demonstrate, don't use too many ISR Timers if not absolutely necessary
  // You can use up to 16 timer for each ISR_Timer
  ISR_Timer.setInterval(TIMER_INTERVAL_2S, doingSomething2s);
  ISR_Timer.setInterval(TIMER_INTERVAL_5S, doingSomething5s);
  ISR_Timer.setInterval(TIMER_INTERVAL_11S, doingSomething11s);
  ISR_Timer.setInterval(TIMER_INTERVAL_101S, doingSomething101s);
}  
```

---
---

### Examples: 

 1. [Argument_None](examples/Argument_None)
 2. [ISR_16_Timers_Array](examples/ISR_16_Timers_Array)
 3. [ISR_16_Timers_Array_Complex](examples/ISR_16_Timers_Array_Complex)
 4. [ISR_RPM_Measure](examples/ISR_RPM_Measure)
 5. [ISR_Timer_Complex_Ethernet](examples/ISR_Timer_Complex_Ethernet)
 6. [ISR_Timer_Complex_WiFiNINA](examples/ISR_Timer_Complex_WiFiNINA)
 7. [RPM_Measure](examples/RPM_Measure)
 8. [SwitchDebounce](examples/SwitchDebounce)
 9. [TimerInterruptTest](examples/TimerInterruptTest)
10. [TimerInterruptLEDDemo](examples/TimerInterruptLEDDemo)
11. [**FakeAnalogWrite**](examples/FakeAnalogWrite).
12. [**Change_Interval**](examples/Change_Interval).
13. [**multiFileProject**](examples/multiFileProject). **New**

---
---

### Example [ISR_16_Timers_Array_Complex](examples/ISR_16_Timers_Array_Complex)

https://github.com/khoih-prog/NRF52_TimerInterrupt/blob/3cdaf91d2c2fd952dd81f60246ff8bbaffdcf7df/examples/ISR_16_Timers_Array_Complex/ISR_16_Timers_Array_Complex.ino#L35-L381


---
---

### Debug Terminal Output Samples

### 1. ISR_Timer_Complex_Ethernet on Adafruit NRF52840_FEATHER using W5500 Ethernet

The following is the sample terminal output when running example [ISR_Timer_Complex_Ethernet](examples/ISR_Timer_Complex_Ethernet) on **Adafruit NRF52840_FEATHER EXPRESS using W5500 Ethernet* to demonstrate the accuracy of ISR Hardware Timer, **especially when system is very busy**.  The ISR timer is **programmed for 2s, is activated exactly after 2.000s !!!**

While software timer, **programmed for 2s, is activated after 4.867s !!!**. Then in loop(), it's also activated **every 3s**.

```
Starting ISR_Timer_Complex_Ethernet on NRF52840_FEATHER
NRF52TimerInterrupt v1.4.2
CPU Frequency = 64 MHz
[TISR] F_CPU (MHz) = 64, Timer = NRF_TIMER2, Timer Clock (Hz) = 1000000.00
[TISR] Frequency = 20.00, _count = 10000
Starting  ITimer OK, millis() = 1419
[1419] Getting IP...
[1419] MAC: FE-BE-97-DA-C3-EA
_pinCS = 0
W5100 init, using SS_PIN_DEFAULT = 10, new ss_pin = 10, W5100Class::ss_pin = 10
W5100::init: W5500, SSIZE =4096
[3104] IP:192.168.2.129
[3104] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on ARDUINO_NRF52_ADAFRUIT

[3106] BlynkArduinoClient.connect: Connecting to account.duckdns.org:8080
[3218] Ready (ping: 8ms).
IP = 192.168.2.129
2s: Delta ms = 2000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 4867
2s: Delta ms = 2000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
2s: Delta ms = 2000
5s: Delta ms = 5000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
5s: Delta ms = 5000
2s: Delta ms = 2000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
5s: Delta ms = 5000
2s: Delta ms = 2000
11s: Delta ms = 11000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
5s: Delta ms = 5000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
2s: Delta ms = 2000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
5s: Delta ms = 5000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
11s: Delta ms = 11000
2s: Delta ms = 2000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
5s: Delta ms = 5000
2s: Delta ms = 2000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
2s: Delta ms = 2000
5s: Delta ms = 5000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
21s: Delta ms = 21000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
11s: Delta ms = 11000
5s: Delta ms = 5000
2s: Delta ms = 2000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
5s: Delta ms = 5000
2s: Delta ms = 2000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
5s: Delta ms = 5000
11s: Delta ms = 11000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
```

---

### 2. TimerInterruptTest on Adafruit NRF52840_FEATHER

The following is the sample terminal output when running example [**TimerInterruptTest**](examples/TimerInterruptTest) on **Adafruit NRF52840_FEATHER** to demonstrate the accuracy and how to start/stop Hardware Timers.

```
Starting TimerInterruptTest on NRF52840_FEATHER
NRF52TimerInterrupt v1.4.2
CPU Frequency = 64 MHz
[TISR] F_CPU (MHz) = 64, Timer = NRF_TIMER1, Timer Clock (Hz) = 1000000.00
[TISR] Frequency = 1.00, _count = 1000000
Starting  ITimer0 OK, millis() = 1020
[TISR] F_CPU (MHz) = 64, Timer = NRF_TIMER4, Timer Clock (Hz) = 1000000.00
[TISR] Frequency = 0.33, _count = 3000000
Starting  ITimer1 OK, millis() = 1021
Stop ITimer0, millis() = 5001
Start ITimer0, millis() = 10002
Stop ITimer1, millis() = 15001
Stop ITimer0, millis() = 15003
Start ITimer0, millis() = 20004
Stop ITimer0, millis() = 25005
Start ITimer1, millis() = 30002
Start ITimer0, millis() = 30006
Stop ITimer0, millis() = 35007
Start ITimer0, millis() = 40008
Stop ITimer1, millis() = 45003
Stop ITimer0, millis() = 45009
Start ITimer0, millis() = 50010
Stop ITimer0, millis() = 55011
Start ITimer1, millis() = 60004
Start ITimer0, millis() = 60012
Stop ITimer0, millis() = 65013
Start ITimer0, millis() = 70014
Stop ITimer1, millis() = 75005
Stop ITimer0, millis() = 75015
Start ITimer0, millis() = 80016
Stop ITimer0, millis() = 85017
```

---

### 3. Argument_None on Adafruit NRF52840_FEATHER

The following is the sample terminal output when running example [**Argument_None**](examples/Argument_None) on **Adafruit NRF52840_FEATHER** to demonstrate the accuracy of Hardware Timers.

```
Starting Argument_None on NRF52840_FEATHER
NRF52TimerInterrupt v1.4.2
CPU Frequency = 64 MHz
[TISR] F_CPU (MHz) = 64, Timer = NRF_TIMER1, Timer Clock (Hz) = 1000000.00
[TISR] Frequency = 1.00, _count = 1000000
Starting ITimer0 OK, millis() = 1024
[TISR] F_CPU (MHz) = 64, Timer = NRF_TIMER2, Timer Clock (Hz) = 1000000.00
[TISR] Frequency = 0.20, _count = 5000000
Starting ITimer1 OK, millis() = 1025
Time = 10001, Timer0Count = 8, , Timer1Count = 1
Time = 20002, Timer0Count = 18, , Timer1Count = 3
Time = 30003, Timer0Count = 28, , Timer1Count = 5
Time = 40004, Timer0Count = 38, , Timer1Count = 7
Time = 50005, Timer0Count = 48, , Timer1Count = 9
Time = 60006, Timer0Count = 58, , Timer1Count = 11
Time = 70007, Timer0Count = 68, , Timer1Count = 13
Time = 80008, Timer0Count = 78, , Timer1Count = 15
Time = 90009, Timer0Count = 88, , Timer1Count = 17

```

---

### 4. ISR_16_Timers_Array_Complex on Adafruit NRF52840_FEATHER

The following is the sample terminal output when running new example [ISR_16_Timers_Array_Complex](examples/ISR_16_Timers_Array_Complex) on **Adafruit NRF52840_FEATHER** to demonstrate the accuracy of ISR Hardware Timer, **especially when system is very busy or blocked**. The 16 independent ISR timers are **programmed to be activated repetitively after certain intervals, is activated exactly after that programmed interval !!!**

While software timer, **programmed for 2s, is activated after 10.000s in loop()!!!**.

In this example, 16 independent ISR Timers are used, yet utilized just one Hardware Timer. The Timer Intervals and Function Pointers are stored in arrays to facilitate the code modification.


```
Starting ISR_16_Timers_Array_Complex on NRF52840_FEATHER
NRF52TimerInterrupt v1.4.2
CPU Frequency = 64 MHz
[TISR] F_CPU (MHz) = 64, Timer = NRF_TIMER2, Timer Clock (Hz) = 1000000.00
[TISR] Frequency = 100.00, _count = 10000
Starting ITimer OK, millis() = 1518
SimpleTimer : 2s, ms = 11409, Dms : 10000
Timer : 0, programmed : 5000, actual : 5005
Timer : 1, programmed : 10000, actual : 0
Timer : 2, programmed : 15000, actual : 0
Timer : 3, programmed : 20000, actual : 0
Timer : 4, programmed : 25000, actual : 0
Timer : 5, programmed : 30000, actual : 0
Timer : 6, programmed : 35000, actual : 0
Timer : 7, programmed : 40000, actual : 0
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2s, ms = 21415, Dms : 10006
Timer : 0, programmed : 5000, actual : 4992
Timer : 1, programmed : 10000, actual : 9993
Timer : 2, programmed : 15000, actual : 15008
Timer : 3, programmed : 20000, actual : 20000
Timer : 4, programmed : 25000, actual : 0
Timer : 5, programmed : 30000, actual : 0
Timer : 6, programmed : 35000, actual : 0
Timer : 7, programmed : 40000, actual : 0
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2s, ms = 31416, Dms : 10001
Timer : 0, programmed : 5000, actual : 4994
Timer : 1, programmed : 10000, actual : 10001
Timer : 2, programmed : 15000, actual : 14993
Timer : 3, programmed : 20000, actual : 20000
Timer : 4, programmed : 25000, actual : 25007
Timer : 5, programmed : 30000, actual : 30001
Timer : 6, programmed : 35000, actual : 0
Timer : 7, programmed : 40000, actual : 0
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2s, ms = 41417, Dms : 10001
Timer : 0, programmed : 5000, actual : 4994
Timer : 1, programmed : 10000, actual : 10000
Timer : 2, programmed : 15000, actual : 14993
Timer : 3, programmed : 20000, actual : 20001
Timer : 4, programmed : 25000, actual : 25007
Timer : 5, programmed : 30000, actual : 30001
Timer : 6, programmed : 35000, actual : 35007
Timer : 7, programmed : 40000, actual : 40001
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2s, ms = 51438, Dms : 10021
Timer : 0, programmed : 5000, actual : 5005
Timer : 1, programmed : 10000, actual : 10006
Timer : 2, programmed : 15000, actual : 15001
Timer : 3, programmed : 20000, actual : 20001
Timer : 4, programmed : 25000, actual : 25000
Timer : 5, programmed : 30000, actual : 30001
Timer : 6, programmed : 35000, actual : 35007
Timer : 7, programmed : 40000, actual : 40001
Timer : 8, programmed : 45000, actual : 45002
Timer : 9, programmed : 50000, actual : 50007
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2s, ms = 61440, Dms : 10002
Timer : 0, programmed : 5000, actual : 4998
Timer : 1, programmed : 10000, actual : 9996
Timer : 2, programmed : 15000, actual : 15001
Timer : 3, programmed : 20000, actual : 20002
Timer : 4, programmed : 25000, actual : 25000
Timer : 5, programmed : 30000, actual : 30002
Timer : 6, programmed : 35000, actual : 35007
Timer : 7, programmed : 40000, actual : 40001
Timer : 8, programmed : 45000, actual : 45002
Timer : 9, programmed : 50000, actual : 50007
Timer : 10, programmed : 55000, actual : 55005
Timer : 11, programmed : 60000, actual : 60003
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2s, ms = 71444, Dms : 10004
Timer : 0, programmed : 5000, actual : 4994
Timer : 1, programmed : 10000, actual : 9998
Timer : 2, programmed : 15000, actual : 15001
Timer : 3, programmed : 20000, actual : 20002
Timer : 4, programmed : 25000, actual : 25000
Timer : 5, programmed : 30000, actual : 30002
Timer : 6, programmed : 35000, actual : 34994
Timer : 7, programmed : 40000, actual : 40001
Timer : 8, programmed : 45000, actual : 45002
Timer : 9, programmed : 50000, actual : 50007
Timer : 10, programmed : 55000, actual : 55005
Timer : 11, programmed : 60000, actual : 60003
Timer : 12, programmed : 65000, actual : 65007
Timer : 13, programmed : 70000, actual : 70001
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2s, ms = 81448, Dms : 10004
Timer : 0, programmed : 5000, actual : 4993
Timer : 1, programmed : 10000, actual : 9999
Timer : 2, programmed : 15000, actual : 15004
Timer : 3, programmed : 20000, actual : 19997
Timer : 4, programmed : 25000, actual : 25000
Timer : 5, programmed : 30000, actual : 30002
Timer : 6, programmed : 35000, actual : 34994
Timer : 7, programmed : 40000, actual : 39999
Timer : 8, programmed : 45000, actual : 45002
Timer : 9, programmed : 50000, actual : 50007
Timer : 10, programmed : 55000, actual : 55005
Timer : 11, programmed : 60000, actual : 60003
Timer : 12, programmed : 65000, actual : 65007
Timer : 13, programmed : 70000, actual : 70001
Timer : 14, programmed : 75000, actual : 75007
Timer : 15, programmed : 80000, actual : 80000
```

---

### 5. SwitchDebounce on Adafruit NRF52840_FEATHER

The following is the sample terminal output when running example [**SwitchDebounce**](examples/SwitchDebounce) on **Adafruit NRF52840_FEATHER** to demonstrate the usage of Hardware Timers for Switch Debouncing.

```
Starting SwitchDebounce on NRF52840_FEATHER
NRF52TimerInterrupt v1.4.2
CPU Frequency = 64 MHz
[TISR] F_CPU (MHz) = 64, Timer = NRF_TIMER1, Timer Clock (Hz) = 1000000.00
[TISR] Frequency = 100.00, _count = 10000
Starting  ITimer OK, millis() = 1560
Time = 1560, Switch = Released
Time = 2561, Switch = Released
Time = 3562, Switch = Released
Time = 4563, Switch = Released
...
Time = 73632, Switch = Released
Time = 74633, Switch = Released
Time = 75634, Switch = Released
Time = 76635, Switch = Released
Time = 77636, Switch = Pressed
Time = 78637, Switch = Pressed
Time = 79638, Switch = Pressed
Time = 80639, Switch = Pressed
Time = 81640, Switch = Pressed
Time = 82641, Switch = LongPressed
Time = 83642, Switch = LongPressed
Time = 84643, Switch = LongPressed
Time = 85644, Switch = Released
Time = 86645, Switch = Released
Time = 87646, Switch = Released
```

---

### 6. Change_Interval on Adafruit NRF52840_FEATHER

The following is the sample terminal output when running example [Change_Interval](examples/Change_Interval) on **Adafruit NRF52840_FEATHER** to demonstrate how to change Timer Interval on-the-fly

```
Starting Change_Interval on NRF52840_FEATHER
NRF52TimerInterrupt v1.4.2
CPU Frequency = 64 MHz
[TISR] F_CPU (MHz) = 64, Timer = NRF_TIMER4, Timer Clock (Hz) = 1000000.00
[TISR] Frequency = 2.00, _count = 500000
Starting ITimer0 OK, millis() = 1321
[TISR] F_CPU (MHz) = 64, Timer = NRF_TIMER3, Timer Clock (Hz) = 1000000.00
[TISR] Frequency = 0.50, _count = 2000000
Starting ITimer1 OK, millis() = 1322
Time = 10001, Timer0Count = 17, , Timer1Count = 4
Time = 20002, Timer0Count = 37, , Timer1Count = 9
Changing Interval, Timer0 = 1000,  Timer1 = 4000
Time = 30003, Timer0Count = 47, , Timer1Count = 11
Time = 40004, Timer0Count = 57, , Timer1Count = 14
Changing Interval, Timer0 = 500,  Timer1 = 2000
Time = 50005, Timer0Count = 77, , Timer1Count = 19
Time = 60006, Timer0Count = 97, , Timer1Count = 24
Changing Interval, Timer0 = 1000,  Timer1 = 4000
Time = 70007, Timer0Count = 107, , Timer1Count = 26
Time = 80008, Timer0Count = 117, , Timer1Count = 29
Changing Interval, Timer0 = 500,  Timer1 = 2000
Time = 90009, Timer0Count = 137, , Timer1Count = 34
Time = 100010, Timer0Count = 157, , Timer1Count = 39
Changing Interval, Timer0 = 1000,  Timer1 = 4000
Time = 110011, Timer0Count = 167, , Timer1Count = 41
Time = 120012, Timer0Count = 177, , Timer1Count = 44
Changing Interval, Timer0 = 500,  Timer1 = 2000
Time = 130013, Timer0Count = 197, , Timer1Count = 49
Time = 140014, Timer0Count = 217, , Timer1Count = 54
Changing Interval, Timer0 = 1000,  Timer1 = 4000
Time = 150015, Timer0Count = 227, , Timer1Count = 56
Time = 160016, Timer0Count = 237, , Timer1Count = 59
Changing Interval, Timer0 = 500,  Timer1 = 2000
Time = 170017, Timer0Count = 257, , Timer1Count = 64
Time = 180018, Timer0Count = 277, , Timer1Count = 69
```

---

### 7. FakeAnalogWrite on Adafruit NRF52840_FEATHER

The following is the sample terminal output when running example [FakeAnalogWrite](examples/FakeAnalogWrite) on **Adafruit NRF52840_FEATHER** to demonstrate how to use analogWrite to many pins to overcome the limitation of nRF52 analogWrite to only 4 pins or crash. Check [**Arduino Nano 33 BLE mbed os crashes when PWM on more than 3 digital pins**](https://forum.arduino.cc/index.php?topic=715883.0)

```
Starting FakeAnalogWrite on NRF52840_FEATHER
NRF52TimerInterrupt v1.4.2
CPU Frequency = 64 MHz
[TISR] F_CPU (MHz) = 64, Timer = NRF_TIMER3, Timer Clock (Hz) = 1000000.00
[TISR] Frequency = 10000.00, _count = 100
Starting ITimer OK, millis() = 1024
Add index = 0, pin = 2, input PWM_Value = 0, mapped PWM_Value = 0
Add index = 1, pin = 3, input PWM_Value = 0, mapped PWM_Value = 0
Add index = 2, pin = 4, input PWM_Value = 0, mapped PWM_Value = 0
Add index = 3, pin = 5, input PWM_Value = 0, mapped PWM_Value = 0
Add index = 4, pin = 6, input PWM_Value = 0, mapped PWM_Value = 0
Add index = 5, pin = 7, input PWM_Value = 0, mapped PWM_Value = 0
Add index = 6, pin = 8, input PWM_Value = 0, mapped PWM_Value = 0
Add index = 7, pin = 9, input PWM_Value = 0, mapped PWM_Value = 0
Test PWM_Value = 0, max = 255
Update index 0, pin = 2, input PWM_Value=5, mapped PWM_Value= 14
Update index 1, pin = 3, input PWM_Value=5, mapped PWM_Value= 14
Update index 2, pin = 4, input PWM_Value=5, mapped PWM_Value= 14
Update index 3, pin = 5, input PWM_Value=5, mapped PWM_Value= 14
Update index 4, pin = 6, input PWM_Value=5, mapped PWM_Value= 14
Update index 5, pin = 7, input PWM_Value=5, mapped PWM_Value= 14
Update index 6, pin = 8, input PWM_Value=5, mapped PWM_Value= 14
Update index 7, pin = 9, input PWM_Value=5, mapped PWM_Value= 14
Test PWM_Value = 5, max = 255
Update index 0, pin = 2, input PWM_Value=10, mapped PWM_Value= 27
Update index 1, pin = 3, input PWM_Value=10, mapped PWM_Value= 27
Update index 2, pin = 4, input PWM_Value=10, mapped PWM_Value= 27
Update index 3, pin = 5, input PWM_Value=10, mapped PWM_Value= 27
Update index 4, pin = 6, input PWM_Value=10, mapped PWM_Value= 27
Update index 5, pin = 7, input PWM_Value=10, mapped PWM_Value= 27
Update index 6, pin = 8, input PWM_Value=10, mapped PWM_Value= 27
Update index 7, pin = 9, input PWM_Value=10, mapped PWM_Value= 27
...
Test PWM_Value = 145, max = 255
Update index 0, pin = 2, input PWM_Value=150, mapped PWM_Value= 135
Update index 1, pin = 3, input PWM_Value=150, mapped PWM_Value= 135
Update index 2, pin = 4, input PWM_Value=150, mapped PWM_Value= 135
Update index 3, pin = 5, input PWM_Value=150, mapped PWM_Value= 135
Update index 4, pin = 6, input PWM_Value=150, mapped PWM_Value= 135
Update index 5, pin = 7, input PWM_Value=150, mapped PWM_Value= 135
Update index 6, pin = 8, input PWM_Value=150, mapped PWM_Value= 135
Update index 7, pin = 9, input PWM_Value=150, mapped PWM_Value= 135
Test PWM_Value = 150, max = 255
Update index 0, pin = 2, input PWM_Value=155, mapped PWM_Value= 137
Update index 1, pin = 3, input PWM_Value=155, mapped PWM_Value= 137
Update index 2, pin = 4, input PWM_Value=155, mapped PWM_Value= 137
Update index 3, pin = 5, input PWM_Value=155, mapped PWM_Value= 137
Update index 4, pin = 6, input PWM_Value=155, mapped PWM_Value= 137
Update index 5, pin = 7, input PWM_Value=155, mapped PWM_Value= 137
Update index 6, pin = 8, input PWM_Value=155, mapped PWM_Value= 137
Update index 7, pin = 9, input PWM_Value=155, mapped PWM_Value= 137
Test PWM_Value = 155, max = 255
Update index 0, pin = 2, input PWM_Value=160, mapped PWM_Value= 138
Update index 1, pin = 3, input PWM_Value=160, mapped PWM_Value= 138
Update index 2, pin = 4, input PWM_Value=160, mapped PWM_Value= 138
Update index 3, pin = 5, input PWM_Value=160, mapped PWM_Value= 138
Update index 4, pin = 6, input PWM_Value=160, mapped PWM_Value= 138
Update index 5, pin = 7, input PWM_Value=160, mapped PWM_Value= 138
Update index 6, pin = 8, input PWM_Value=160, mapped PWM_Value= 138
Update index 7, pin = 9, input PWM_Value=160, mapped PWM_Value= 138
Test PWM_Value = 160, max = 255
Update index 0, pin = 2, input PWM_Value=165, mapped PWM_Value= 141
Update index 1, pin = 3, input PWM_Value=165, mapped PWM_Value= 141
Update index 2, pin = 4, input PWM_Value=165, mapped PWM_Value= 141
Update index 3, pin = 5, input PWM_Value=165, mapped PWM_Value= 141
Update index 4, pin = 6, input PWM_Value=165, mapped PWM_Value= 141
Update index 5, pin = 7, input PWM_Value=165, mapped PWM_Value= 141
Update index 6, pin = 8, input PWM_Value=165, mapped PWM_Value= 141
Update index 7, pin = 9, input PWM_Value=165, mapped PWM_Value= 141
Test PWM_Value = 165, max = 255
Update index 0, pin = 2, input PWM_Value=170, mapped PWM_Value= 143
Update index 1, pin = 3, input PWM_Value=170, mapped PWM_Value= 143
Update index 2, pin = 4, input PWM_Value=170, mapped PWM_Value= 143
Update index 3, pin = 5, input PWM_Value=170, mapped PWM_Value= 143
Update index 4, pin = 6, input PWM_Value=170, mapped PWM_Value= 143
Update index 5, pin = 7, input PWM_Value=170, mapped PWM_Value= 143
Update index 6, pin = 8, input PWM_Value=170, mapped PWM_Value= 143
Update index 7, pin = 9, input PWM_Value=170, mapped PWM_Value= 143
Test PWM_Value = 170, max = 255
```

---
---

### Debug

Debug is enabled by default on Serial.

You can also change the debugging level (_TIMERINTERRUPT_LOGLEVEL_) from 0 to 4

```cpp
// These define's must be placed at the beginning before #include "NRF52TimerInterrupt.h"
// _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
// Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define TIMER_INTERRUPT_DEBUG         0
#define _TIMERINTERRUPT_LOGLEVEL_     0
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the core for Arduino boards.

Sometimes, the library will only work if you update the board core to the latest version because I am using newly added functions.

---
---

### Issues

Submit issues to: [NRF52_TimerInterrupt issues](https://github.com/khoih-prog/NRF52_TimerInterrupt/issues)

---

## TO DO

1. Search for bug and improvement.

---

## DONE

 1. Basic hardware timers for `NRF52832` and `NRF52840`
 2. More hardware-initiated software-enabled timers
 3. Longer time interval
 4. Similar features for remaining Arduino boards such as AVR, ESP32, ESP8266, STM32, SAM-DUE, SAMD21/SAMD51, mbed-nRF52, Teensy, etc.
 5. Add Table of Contents
 6. Fix `multiple-definitions` linker error
 7. Optimize library code by using `reference-passing` instead of `value-passing`
 8. Add support to `Sparkfun Pro nRF52840 Mini`
 9. Add support to Seeeduino nRF52840-based boards such as **SEEED_XIAO_NRF52840 and SEEED_XIAO_NRF52840_SENSE**, etc. using Seeeduino `nRF%2` core
10. Add astyle using `allman` style. Restyle the library

---
---

### Contributions and Thanks

Many thanks for everyone for bug reporting, new feature suggesting, testing and contributing to the development of this library.

1. Thanks to good work of [Miguel Wisintainer](https://github.com/tcpipchip) for working with, developing, debugging and testing.

<table>
  <tr>
    <td align="center"><a href="https://github.com/tcpipchip"><img src="https://github.com/tcpipchip.png" width="100px;" alt="tcpipchip"/><br /><sub><b> Miguel Wisintainer</b></sub></a><br /></td>
  </tr> 
</table>

---

## Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/NRF52_TimerInterrupt/blob/main/LICENSE)

---

## Copyright

Copyright 2020- Khoi Hoang


