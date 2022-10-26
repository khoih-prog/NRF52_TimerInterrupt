/****************************************************************************************************************************
  NRF52_ISR_Timer.hpp
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

#ifndef ISR_TIMER_GENERIC_HPP
#define ISR_TIMER_GENERIC_HPP

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

#ifndef NRF52_TIMER_INTERRUPT_VERSION
  #define NRF52_TIMER_INTERRUPT_VERSION       "NRF52TimerInterrupt v1.4.2"
  
  #define NRF52_TIMER_INTERRUPT_VERSION_MAJOR      1
  #define NRF52_TIMER_INTERRUPT_VERSION_MINOR      4
  #define NRF52_TIMER_INTERRUPT_VERSION_PATCH      2

  #define NRF52_TIMER_INTERRUPT_VERSION_INT        1004002
#endif

////////////////////////////////////////

#include "TimerInterrupt_Generic_Debug.h"

#include <stddef.h>

#include <inttypes.h>

#if defined(ARDUINO)
  #if ARDUINO >= 100
    #include <Arduino.h>
  #else
    #include <WProgram.h>
  #endif
#endif

////////////////////////////////////////

#define NRF52_ISR_Timer NRF52_ISRTimer

typedef void (*timerCallback)();
typedef void (*timerCallback_p)(void *);

////////////////////////////////////////

class NRF52_ISR_Timer 
{
  public:
    // maximum number of timers
#define MAX_NUMBER_TIMERS         16
#define TIMER_RUN_FOREVER         0
#define TIMER_RUN_ONCE            1

    // constructor
    NRF52_ISR_Timer();

    void init();

    // this function must be called inside loop()
    void run();

    // Timer will call function 'f' every 'd' milliseconds forever
    // returns the timer number (numTimer) on success or
    // -1 on failure (f == NULL) or no free timers
    int setInterval(const unsigned long& d, timerCallback f);

    // Timer will call function 'f' with parameter 'p' every 'd' milliseconds forever
    // returns the timer number (numTimer) on success or
    // -1 on failure (f == NULL) or no free timers
    int setInterval(const unsigned long& d, timerCallback_p f, void* p);

    // Timer will call function 'f' after 'd' milliseconds one time
    // returns the timer number (numTimer) on success or
    // -1 on failure (f == NULL) or no free timers
    int setTimeout(const unsigned long& d, timerCallback f);

    // Timer will call function 'f' with parameter 'p' after 'd' milliseconds one time
    // returns the timer number (numTimer) on success or
    // -1 on failure (f == NULL) or no free timers
    int setTimeout(const unsigned long& d, timerCallback_p f, void* p);

    // Timer will call function 'f' every 'd' milliseconds 'n' times
    // returns the timer number (numTimer) on success or
    // -1 on failure (f == NULL) or no free timers
    int setTimer(const unsigned long& d, timerCallback f, const unsigned& n);

    // Timer will call function 'f' with parameter 'p' every 'd' milliseconds 'n' times
    // returns the timer number (numTimer) on success or
    // -1 on failure (f == NULL) or no free timers
    int setTimer(const unsigned long& d, timerCallback_p f, void* p, const unsigned& n);

    // updates interval of the specified timer
    bool changeInterval(const unsigned& numTimer, const unsigned long& d);

    // destroy the specified timer
    void deleteTimer(const unsigned& numTimer);

    // restart the specified timer
    void restartTimer(const unsigned& numTimer);

    // returns true if the specified timer is enabled
    bool isEnabled(const unsigned& numTimer);

    // enables the specified timer
    void enable(const unsigned& numTimer);

    // disables the specified timer
    void disable(const unsigned& numTimer);

    // enables all timers
    void enableAll();

    // disables all timers
    void disableAll();

    // enables the specified timer if it's currently disabled, and vice-versa
    void toggle(const unsigned& numTimer);

    // returns the number of used timers
    unsigned getNumTimers();

    ////////////////////////////////////////

    // returns the number of available timers
    inline unsigned getNumAvailableTimers() 
    {
      return MAX_NUMBER_TIMERS - numTimers;
    };

    ////////////////////////////////////////

  private:
    // deferred call constants
#define TIMER_DEFCALL_DONTRUN       0       // don't call the callback function
#define TIMER_DEFCALL_RUNONLY       1       // call the callback function but don't delete the timer
#define TIMER_DEFCALL_RUNANDDEL     2       // call the callback function and delete the timer

    // low level function to initialize and enable a new timer
    // returns the timer number (numTimer) on success or
    // -1 on failure (f == NULL) or no free timers
    int setupTimer(const unsigned long& d, void* f, void* p, bool h, const unsigned& n);

    // find the first available slot
    int findFirstFreeSlot();

    ////////////////////////////////////////

    typedef struct 
    {
      unsigned long prev_millis;        // value returned by the millis() function in the previous run() call
      void*         callback;           // pointer to the callback function
      void*         param;              // function parameter
      bool          hasParam;           // true if callback takes a parameter
      unsigned long delay;              // delay value
      unsigned      maxNumRuns;         // number of runs to be executed
      unsigned      numRuns;            // number of executed runs
      bool          enabled;            // true if enabled
      unsigned      toBeCalled;         // deferred function call (sort of) - N.B.: only used in run()
    } timer_t;

    ////////////////////////////////////////

    volatile timer_t timer[MAX_NUMBER_TIMERS];

    // actual number of timers in use (-1 means uninitialized)
    volatile int numTimers;
};

#endif    // ISR_TIMER_GENERIC_HPP
