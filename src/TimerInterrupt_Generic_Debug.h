/****************************************************************************************************************************
  TimerInterrupt_Generic_Debug.h
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

#ifndef TIMERINTERRUPT_GENERIC_DEBUG_H
#define TIMERINTERRUPT_GENERIC_DEBUG_H

#include <Adafruit_TinyUSB.h>

#ifdef TIMERINTERRUPT_DEBUG_PORT
  #define TISR_DBG_PORT      TIMERINTERRUPT_DEBUG_PORT
#else
  #define TISR_DBG_PORT      Serial
#endif

///////////////////////////////////////

// Change _TIMERINTERRUPT_LOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug

#ifndef _TIMERINTERRUPT_LOGLEVEL_
  #define _TIMERINTERRUPT_LOGLEVEL_       1
#endif

///////////////////////////////////////

const char TISR_MARK[]  = "[TISR] ";
const char TISR_SPACE[] = " ";
const char TISR_LINE[]  = "========================================\n";

#define TISR_PRINT        TISR_DBG_PORT.print
#define TISR_PRINTLN      TISR_DBG_PORT.println

#define TISR_PRINT_MARK   TISR_PRINT(TISR_MARK)
#define TISR_PRINT_SP     TISR_PRINT(TISR_SPACE)
#define TISR_PRINT_LINE   TISR_PRINT(TISR_LINE)

///////////////////////////////////////

#define TISR_LOGERROR(x)         if(_TIMERINTERRUPT_LOGLEVEL_>0) { TISR_PRINT_MARK; TISR_PRINTLN(x); }
#define TISR_LOGERROR0(x)        if(_TIMERINTERRUPT_LOGLEVEL_>0) { TISR_PRINT(x); }
#define TISR_LOGERROR1(x,y)      if(_TIMERINTERRUPT_LOGLEVEL_>0) { TISR_PRINT_MARK; TISR_PRINT(x); TISR_PRINTLN(y); }
#define TISR_LOGERROR2(x,y,z)    if(_TIMERINTERRUPT_LOGLEVEL_>0) { TISR_PRINT_MARK; TISR_PRINT(x); TISR_PRINT(y); TISR_PRINTLN(z); }
#define TISR_LOGERROR3(x,y,z,w)  if(_TIMERINTERRUPT_LOGLEVEL_>0) { TISR_PRINT_MARK; TISR_PRINT(x); TISR_PRINT(y); TISR_PRINT(z); TISR_PRINTLN(w); }
#define TISR_LOGERROR5(x,y,z,w, xx, yy)  if(_TIMERINTERRUPT_LOGLEVEL_>0) { TISR_PRINT_MARK; TISR_PRINT(x); TISR_PRINT(y); TISR_PRINT(z); TISR_PRINT(w); TISR_PRINT(xx); TISR_PRINTLN(yy); }

///////////////////////////////////////

#define TISR_LOGWARN(x)          if(_TIMERINTERRUPT_LOGLEVEL_>1) { TISR_PRINT_MARK; TISR_PRINTLN(x); }
#define TISR_LOGWARN0(x)         if(_TIMERINTERRUPT_LOGLEVEL_>1) { TISR_PRINT(x); }
#define TISR_LOGWARN1(x,y)       if(_TIMERINTERRUPT_LOGLEVEL_>1) { TISR_PRINT_MARK; TISR_PRINT(x); TISR_PRINTLN(y); }
#define TISR_LOGWARN2(x,y,z)     if(_TIMERINTERRUPT_LOGLEVEL_>1) { TISR_PRINT_MARK; TISR_PRINT(x); TISR_PRINT(y); TISR_PRINTLN(z); }
#define TISR_LOGWARN3(x,y,z,w)   if(_TIMERINTERRUPT_LOGLEVEL_>1) { TISR_PRINT_MARK; TISR_PRINT(x); TISR_PRINT(y); TISR_PRINT(z); TISR_PRINTLN(w); }
#define TISR_LOGWARN5(x,y,z,w, xx, yy)  if(_TIMERINTERRUPT_LOGLEVEL_>1) { TISR_PRINT_MARK; TISR_PRINT(x); TISR_PRINT(y); TISR_PRINT(z); TISR_PRINT(w); TISR_PRINT(xx); TISR_PRINTLN(yy); }

///////////////////////////////////////

#define TISR_LOGINFO(x)          if(_TIMERINTERRUPT_LOGLEVEL_>2) { TISR_PRINT_MARK; TISR_PRINTLN(x); }
#define TISR_LOGINFO0(x)         if(_TIMERINTERRUPT_LOGLEVEL_>2) { TISR_PRINT(x); }
#define TISR_LOGINFO1(x,y)       if(_TIMERINTERRUPT_LOGLEVEL_>2) { TISR_PRINT_MARK; TISR_PRINT(x); TISR_PRINTLN(y); }
#define TISR_LOGINFO2(x,y,z)     if(_TIMERINTERRUPT_LOGLEVEL_>2) { TISR_PRINT_MARK; TISR_PRINT(x); TISR_PRINT(y); TISR_PRINTLN(z); }
#define TISR_LOGINFO3(x,y,z,w)   if(_TIMERINTERRUPT_LOGLEVEL_>2) { TISR_PRINT_MARK; TISR_PRINT(x); TISR_PRINT(y); TISR_PRINT(z); TISR_PRINTLN(w); }
#define TISR_LOGINFO5(x,y,z,w, xx, yy)  if(_TIMERINTERRUPT_LOGLEVEL_>2) { TISR_PRINT_MARK; TISR_PRINT(x); TISR_PRINT(y); TISR_PRINT(z); TISR_PRINT(w); TISR_PRINT(xx); TISR_PRINTLN(yy); }

///////////////////////////////////////

#define TISR_LOGDEBUG(x)         if(_TIMERINTERRUPT_LOGLEVEL_>3) { TISR_PRINT_MARK; TISR_PRINTLN(x); }
#define TISR_LOGDEBUG0(x)        if(_TIMERINTERRUPT_LOGLEVEL_>3) { TISR_PRINT(x); }
#define TISR_LOGDEBUG1(x,y)      if(_TIMERINTERRUPT_LOGLEVEL_>3) { TISR_PRINT_MARK; TISR_PRINT(x); TISR_PRINTLN(y); }
#define TISR_LOGDEBUG2(x,y,z)    if(_TIMERINTERRUPT_LOGLEVEL_>3) { TISR_PRINT_MARK; TISR_PRINT(x); TISR_PRINT(y); TISR_PRINTLN(z); }
#define TISR_LOGDEBUG3(x,y,z,w)  if(_TIMERINTERRUPT_LOGLEVEL_>3) { TISR_PRINT_MARK; TISR_PRINT(x); TISR_PRINT(y); TISR_PRINT(z); TISR_PRINTLN(w); }
#define TISR_LOGDEBUG5(x,y,z,w, xx, yy)  if(_TIMERINTERRUPT_LOGLEVEL_>3) { TISR_PRINT_MARK; TISR_PRINT(x); TISR_PRINT(y); TISR_PRINT(z); TISR_PRINT(w); TISR_PRINT(xx); TISR_PRINTLN(yy); }

///////////////////////////////////////

#endif    //TIMERINTERRUPT_GENERIC_DEBUG_H
