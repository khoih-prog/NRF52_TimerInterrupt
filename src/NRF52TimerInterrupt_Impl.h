/****************************************************************************************************************************
  NRF52TimerInterrupt_Impl.h
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
/*
  nRF52 has 5 Hardware TIMERs: NRF_TIMER0-NRF_TIMER4
  NRF_TIMER0 is used by the soft device, NRF_TIMER1-NRF_TIMER4 are available

  Defined in file ./adafruit/hardware/nrf52/0.21.0/cores/nRF5/nordic/nrfx/mdk/nrf52.h

  #define NRF_TIMER0_BASE             0x40008000UL
  #define NRF_TIMER1_BASE             0x40009000UL
  #define NRF_TIMER2_BASE             0x4000A000UL
  #define NRF_TIMER3_BASE             0x4001A000UL
  #define NRF_TIMER4_BASE             0x4001B000UL
  ...
  #define NRF_TIMER0                  ((NRF_TIMER_Type*)         NRF_TIMER0_BASE)
  #define NRF_TIMER1                  ((NRF_TIMER_Type*)         NRF_TIMER1_BASE)
  #define NRF_TIMER2                  ((NRF_TIMER_Type*)         NRF_TIMER2_BASE)
  #define NRF_TIMER3                  ((NRF_TIMER_Type*)         NRF_TIMER3_BASE)
  #define NRF_TIMER4                  ((NRF_TIMER_Type*)         NRF_TIMER4_BASE)

  ===============================================================================

  Defined in ./adafruit/hardware/nrf52/0.21.0/cores/nRF5/nordic/nrfx/hal/nrf_timer.h

  Timer prescalers
  typedef enum
  {
      NRF_TIMER_FREQ_16MHz = 0, ///< Timer frequency 16 MHz.
      NRF_TIMER_FREQ_8MHz,      ///< Timer frequency 8 MHz.
      NRF_TIMER_FREQ_4MHz,      ///< Timer frequency 4 MHz.
      NRF_TIMER_FREQ_2MHz,      ///< Timer frequency 2 MHz.
      NRF_TIMER_FREQ_1MHz,      ///< Timer frequency 1 MHz.
      NRF_TIMER_FREQ_500kHz,    ///< Timer frequency 500 kHz.
      NRF_TIMER_FREQ_250kHz,    ///< Timer frequency 250 kHz.
      NRF_TIMER_FREQ_125kHz,    ///< Timer frequency 125 kHz.
      NRF_TIMER_FREQ_62500Hz,   ///< Timer frequency 62500 Hz.
      NRF_TIMER_FREQ_31250Hz    ///< Timer frequency 31250 Hz.
  } nrf_timer_frequency_t;

*/
#pragma once

#ifndef NRF52_TIMER_INTERRUPT_IMPL_H
#define NRF52_TIMER_INTERRUPT_IMPL_H

#include <Arduino.h>
#include "nrf_timer.h"

#include "TimerInterrupt_Generic_Debug.h"

////////////////////////////////////////

// Timer 0 is used by the soft device but Timer 1, 2, 3 and 4 are available
extern "C" void TIMER1_IRQHandler()
{
  if (nRF52Timers[1])
  {
    nRF52Timers[1]->detachInterrupt();

    (*(nRF52Timers[1]->getCallback()))();

    nRF52Timers[1]->enableTimer();
  }
}

////////////////////////////////////////

extern "C" void TIMER2_IRQHandler()
{
  if (nRF52Timers[2])
  {
    nRF52Timers[2]->detachInterrupt();

    (*(nRF52Timers[2]->getCallback()))();

    nRF52Timers[2]->enableTimer();
  }
}

////////////////////////////////////////

extern "C" void TIMER3_IRQHandler()
{
  if (nRF52Timers[3])
  {
    nRF52Timers[3]->detachInterrupt();

    (*(nRF52Timers[3]->getCallback()))();

    nRF52Timers[3]->enableTimer();
  }
}

////////////////////////////////////////

extern "C" void TIMER4_IRQHandler()
{
  if (nRF52Timers[4])
  {
    nRF52Timers[4]->detachInterrupt();

    (*(nRF52Timers[4]->getCallback()))();

    nRF52Timers[4]->enableTimer();
  }
}

////////////////////////////////////////

#endif    // NRF52_TIMER_INTERRUPT_IMPL_H
