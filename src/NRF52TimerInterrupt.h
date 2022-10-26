/****************************************************************************************************************************
  NRF52TimerInterrupt.h
  For NRF52 boards
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/NRF52_TimerInterrupt
  Licensed under MIT license

  Now even you use all these new 16 ISR-based timers,with their maximum interval practically unlimited (limited only by
  unsigned long miliseconds), you just consume only one NRF52 timer and avoid conflicting with other cores' tasks.
  The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers
  Therefore, their executions are not blocked by bad-behaving functions / tasks.
  This important feature is absolutely necessary for mission-critical tasks.

  Based on SimpleTimer - A timer library for Arduino.
  Author: mromani@ottotecnica.com
  Copyright (c) 2010 OTTOTECNICA Italy

  Based on BlynkTimer.h
  Author: Volodymyr Shymanskyy

  Version: 1.4.2

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      02/11/2020 Initial coding
  1.0.1   K Hoang      06/11/2020 Add complicated example ISR_16_Timers_Array using all 16 independent ISR Timers.
  1.0.2   K Hoang      24/11/2020 Add complicated example ISR_16_Timers_Array_Complex and optimize examples
  1.1.1   K.Hoang      06/12/2020 Add Change_Interval example. Bump up version to sync with other TimerInterrupt Libraries
  1.2.0   K.Hoang      11/01/2021 Add better debug feature. Optimize code and examples to reduce RAM usage
  1.3.0   K.Hoang      13/08/2021 Add support to Adafruit nRF52 core v0.22.0+
  1.4.0   K.Hoang      21/01/2022 Fix `multiple-definitions` linker error. Fix bug
  1.4.1   K.Hoang      03/03/2022 Add support to Sparkfun Pro nRF52840 Mini
  1.4.2   K.Hoang      03/03/2022 26/10/2022 Add support to Seeed_XIAO_NRF52840 and Seeed_XIAO_NRF52840_SENSE
*****************************************************************************************************************************/

#pragma once

#ifndef NRF52_TIMER_INTERRUPT_H
#define NRF52_TIMER_INTERRUPT_H

#include "NRF52TimerInterrupt.hpp"
#include "NRF52TimerInterrupt_Impl.h"


#endif    // NRF52_TIMER_INTERRUPT_H
