/****************************************************************************************************************************
  NRF52TimerInterrupt.hpp
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

#ifndef NRF52_TIMER_INTERRUPT_HPP
#define NRF52_TIMER_INTERRUPT_HPP

////////////////////////////////////////

#if !(defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
      defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || \
      defined(NRF52840_CLUE) || defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) || \
      defined(NRF52840_LED_GLASSES) || defined(MDBT50Q_RX) || defined(NINA_B302_ublox) || defined(NINA_B112_ublox) || \
      defined(ARDUINO_Seeed_XIAO_nRF52840) || defined(ARDUINO_Seeed_XIAO_nRF52840_Sense) )
  #error This code is designed to run on Adafruit or Seeed nRF52 platform! Please check your Tools->Board setting.
#endif

////////////////////////////////////////

#if !defined(BOARD_NAME)
	#if defined(ARDUINO_Seeed_XIAO_nRF52840)
		#define BOARD_NAME		"Seeed_XIAO_nRF52840"
	#elif defined(ARDUINO_Seeed_XIAO_nRF52840_Sense)
		#define BOARD_NAME		"Seeed_XIAO_nRF52840_Sense"
	#endif
#endif

////////////////////////////////////////

#include <Arduino.h>
#include "nrf_timer.h"

////////////////////////////////////////

#ifndef NRF52_TIMER_INTERRUPT_VERSION
  #define NRF52_TIMER_INTERRUPT_VERSION       "NRF52TimerInterrupt v1.4.2"
  
  #define NRF52_TIMER_INTERRUPT_VERSION_MAJOR      1
  #define NRF52_TIMER_INTERRUPT_VERSION_MINOR      4
  #define NRF52_TIMER_INTERRUPT_VERSION_PATCH      2

  #define NRF52_TIMER_INTERRUPT_VERSION_INT        1004002
#endif

////////////////////////////////////////

#include "TimerInterrupt_Generic_Debug.h"

class NRF52TimerInterrupt;

typedef NRF52TimerInterrupt NRF52Timer;

typedef void (*timerCallback)  ();

////////////////////////////////////////

typedef enum
{
  NRF_TIMER_0 = 0,
  NRF_TIMER_1 = 1,
  NRF_TIMER_2 = 2,
  NRF_TIMER_3 = 3,
  NRF_TIMER_4 = 4,
  NRF_MAX_TIMER
} NRF52TimerNumber;

////////////////////////////////////////

static const char* NRF52TimerName[NRF_MAX_TIMER] =
{
  "NRF_TIMER0-DON'T_USE_THIS",
  "NRF_TIMER1",
  "NRF_TIMER2",
  "NRF_TIMER3",
  "NRF_TIMER4",
};

////////////////////////////////////////

/*
typedef enum
{
    NRF_TIMER_CC_CHANNEL0 = 0, ///< Timer capture/compare channel 0.
    NRF_TIMER_CC_CHANNEL1,     ///< Timer capture/compare channel 1.
    NRF_TIMER_CC_CHANNEL2,     ///< Timer capture/compare channel 2.
    NRF_TIMER_CC_CHANNEL3,     ///< Timer capture/compare channel 3.
#ifdef NRF52
    NRF_TIMER_CC_CHANNEL4,     ///< Timer capture/compare channel 4.
    NRF_TIMER_CC_CHANNEL5,     ///< Timer capture/compare channel 5.
#endif
} nrf_timer_cc_channel_t;
*/

////////////////////////////////////////

class NRF52TimerInterrupt;

static NRF_TIMER_Type* nrf_timers    [NRF_MAX_TIMER] = { NRF_TIMER0, NRF_TIMER1, NRF_TIMER2, NRF_TIMER3, NRF_TIMER4 };

static IRQn_Type       nrf_timers_irq[NRF_MAX_TIMER] = { TIMER0_IRQn, TIMER1_IRQn, TIMER2_IRQn, TIMER3_IRQn, TIMER4_IRQn };

static NRF52TimerInterrupt*  nRF52Timers [NRF_MAX_TIMER] = { NULL, NULL, NULL, NULL, NULL };

////////////////////////////////////////

class NRF52TimerInterrupt
{
  private:
    uint8_t               _timer       = NRF_TIMER_1;
    
    NRF_TIMER_Type*        nrf_timer  = NRF_TIMER1;
    nrf_timer_cc_channel_t cc_channel = NRF_TIMER_CC_CHANNEL0;
    
    IRQn_Type              _timer_IRQ;

    timerCallback        _callback;        // pointer to the callback function
    
    // NRF_TIMER_FREQ_16MHz,NRF_TIMER_FREQ_8MHz,...,NRF_TIMER_FREQ_31250Hz
    nrf_timer_frequency_t _frequency_t = NRF_TIMER_FREQ_1MHz;
    
    float                 TIM_CLOCK_FREQ;   // Timer Clock frequency
    float                 _frequency;       // Timer frequency
    uint32_t              _timerCount;      // count to activate timer

  public:

    ////////////////////////////////////////

    NRF52TimerInterrupt(uint8_t timer = NRF_TIMER_1)
    {
      // KH, force to use NRF_TIMER1 if accidentally select already used NRF_TIMER0
      // To store to know which to delete in destructor
      if (timer == NRF_TIMER_0)
        _timer = NRF_TIMER_1;
      else
        _timer = timer;
      
      nrf_timer   = nrf_timers[_timer];
      
      _timer_IRQ  = nrf_timers_irq[_timer];

      // Update to use in TIMERx_IRQHandler
      nRF52Timers[_timer] = this;
        
      _callback = NULL;
      
      // Timer mode with 32bit width
      nrf_timer_bit_width_set(nrf_timer, NRF_TIMER_BIT_WIDTH_32);
      nrf_timer_mode_set(nrf_timer, NRF_TIMER_MODE_TIMER);
      
      // KH, just 1MHz is enough. 16MHz can have better accuracy, but shorter time range.
      nrf_timer_frequency_set(nrf_timer, _frequency_t);
      
      switch (_frequency_t)
      {
      case NRF_TIMER_FREQ_16MHz:
        TIM_CLOCK_FREQ = 16000000.0f;
        
        break;
      case NRF_TIMER_FREQ_8MHz:
        TIM_CLOCK_FREQ = 8000000.0f;
        
        break;
        case NRF_TIMER_FREQ_4MHz:
        TIM_CLOCK_FREQ = 4000000.0f;
        
        break;
      case NRF_TIMER_FREQ_2MHz:
        TIM_CLOCK_FREQ = 2000000.0f;
        
        break;
      case NRF_TIMER_FREQ_1MHz:
        TIM_CLOCK_FREQ = 1000000.0f;
        
        break;
      default:
        TIM_CLOCK_FREQ = 1000000.0f;
        break;            
      } 
    };

    ////////////////////////////////////////
    
    ~NRF52TimerInterrupt()
    {
      nRF52Timers[_timer] = NULL;
    }

    ////////////////////////////////////////

    // frequency (in hertz) and duration (in milliseconds). Duration = 0 or not specified => run indefinitely
    // No params and duration now. To be addes in the future by adding similar functions here or to NRF52-hal-timer.c
    bool setFrequency(const float& frequency, timerCallback callback)
    {
      // This function will be called when time out interrupt will occur
      if (callback) 
      {
          _callback = callback;
      } 
      else 
      {
          TISR_LOGERROR(F("NRF52TimerInterrupt: ERROR: NULL callback function pointer."));
          
          return false;
      }
      
      if ( (frequency <= 0) || (frequency > TIM_CLOCK_FREQ / 10.0f) )     
      {
        TISR_LOGERROR1(F("NRF52TimerInterrupt: ERROR: Negative or Too high frequency. Must be <="), TIM_CLOCK_FREQ/10.0f);
        
        return false;
      }
      
      // select timer frequency is 1MHz for better accuracy as well as longer timer. We don't use 16-bit prescaler for now.
      // Will use later if very low frequency is needed.
      _frequency  = frequency;      
      _timerCount = (uint32_t) TIM_CLOCK_FREQ / frequency;
      
      TISR_LOGWARN5(F("F_CPU (MHz) = "), F_CPU/1000000, F(", Timer = "), NRF52TimerName[_timer], F(", Timer Clock (Hz) = "), TIM_CLOCK_FREQ);
      TISR_LOGWARN3(F("Frequency = "), frequency, F(", _count = "), (uint32_t) (_timerCount));

      // Start if not already running (and reset?)
      nrf_timer_task_trigger(nrf_timer, NRF_TIMER_TASK_START);
      nrf_timer_task_trigger(nrf_timer, NRF_TIMER_TASK_CLEAR);

      // Clear and enable compare interrupt
      nrf_timer_int_mask_t channel_mask = nrf_timer_compare_int_get(cc_channel);
      nrf_timer_int_enable(nrf_timer, channel_mask);
      
      NVIC_EnableIRQ(_timer_IRQ);
           
      //nrf_timer_cc_write(nrf_timer, cc_channel, _timerCount);
      // New for Adafruit nRF52 core 0.21.0
      nrf_timer_cc_set(nrf_timer, cc_channel, _timerCount);

      return true;
    }

    ////////////////////////////////////////

    // interval (in microseconds) and duration (in milliseconds). Duration = 0 or not specified => run indefinitely
    // No params and duration now. To be addes in the future by adding similar functions here or to NRF52-hal-timer.c
    bool setInterval(const unsigned long& interval, timerCallback callback)
    {
      return setFrequency((float) (1000000.0f / interval), callback);
    }

    ////////////////////////////////////////

    bool attachInterrupt(const float& frequency, timerCallback callback)
    {
      return setFrequency(frequency, callback);
    }

    ////////////////////////////////////////

    // interval (in microseconds) and duration (in milliseconds). Duration = 0 or not specified => run indefinitely
    // No params and duration now. To be addes in the future by adding similar functions here or to NRF52-hal-timer.c
    bool attachInterruptInterval(const unsigned long& interval, timerCallback callback)
    {
      return setFrequency( (float) ( 1000000.0f / interval), callback);
    }

    ////////////////////////////////////////

    void detachInterrupt()
    {
      NVIC_DisableIRQ(_timer_IRQ);
      
      // Stop timer
      nrf_timer_task_trigger(nrf_timer, NRF_TIMER_TASK_STOP);

      // Disable timer compare interrupt
      nrf_timer_int_mask_t channel_mask = nrf_timer_compare_int_get(cc_channel);
      nrf_timer_int_disable(nrf_timer, channel_mask);

      // Clear event
      nrf_timer_event_t event = nrf_timer_compare_event_get(channel_mask);
      nrf_timer_event_clear(nrf_timer, event);
    }

    ////////////////////////////////////////

    void disableTimer()
    {
      detachInterrupt();
    }

    ////////////////////////////////////////

    // Duration (in milliseconds). Duration = 0 or not specified => run indefinitely
    void reattachInterrupt()
    {
      setFrequency(_frequency, _callback);
    }

    ////////////////////////////////////////

    // Duration (in milliseconds). Duration = 0 or not specified => run indefinitely
    void enableTimer()
    {
      // Start if not already running (and reset?)
      nrf_timer_task_trigger(nrf_timer, NRF_TIMER_TASK_START);
      nrf_timer_task_trigger(nrf_timer, NRF_TIMER_TASK_CLEAR);

      // Clear and enable compare interrupt
      nrf_timer_int_mask_t channel_mask = nrf_timer_compare_int_get(cc_channel);
      nrf_timer_int_enable(nrf_timer, channel_mask);
      
      NVIC_EnableIRQ(_timer_IRQ);
      
      //nrf_timer_cc_write(nrf_timer, cc_channel, _timerCount);
      // New for Adafruit nRF52 core 0.21.0
      nrf_timer_cc_set(nrf_timer, cc_channel, _timerCount);
    }

    ////////////////////////////////////////

    // Just stop clock source, clear the count
    void stopTimer()
    {
      disableTimer();
    }

    ////////////////////////////////////////

    // Just reconnect clock source, start current count from 0
    void restartTimer()
    {
      enableTimer();
    }

    ////////////////////////////////////////
    
    inline timerCallback getCallback()
    {
      return _callback;
    }

    ////////////////////////////////////////
    
    inline IRQn_Type getTimerIRQn()
    {
      return _timer_IRQ;
    }

    ////////////////////////////////////////   
}; // class NRF52TimerInterrupt

#endif    // NRF52_TIMER_INTERRUPT_HPP
