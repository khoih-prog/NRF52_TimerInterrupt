/****************************************************************************************************************************
   TimerInterruptLEDDemo.ino
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

   Version: 1.0.2

   Version Modified By   Date      Comments
   ------- -----------  ---------- -----------
   1.0.0   K Hoang      02/11/2020 Initial coding
   1.0.1   K Hoang      06/11/2020 Add complicated example ISR_16_Timers_Array using all 16 independent ISR Timers.
   1.0.2   K Hoang      24/11/2020 Add complicated example ISR_16_Timers_Array_Complex and optimize examples
*****************************************************************************************************************************/

/*
   Notes:
   Special design is necessary to share data between interrupt code and the rest of your program.
   Variables usually need to be "volatile" types. Volatile tells the compiler to avoid optimizations that assume
   variable can not spontaneously change. Because your function may change variables while your program is using them,
   the compiler needs this hint. But volatile alone is often not enough.
   When accessing shared variables, usually interrupts must be disabled. Even with volatile,
   if the interrupt changes a multi-byte variable between a sequence of instructions, it can be read incorrectly.
   If your data is multiple variables, such as an array and a count, usually interrupts need to be disabled
   or the entire sequence of your code which accesses the data.
*/

#if !(defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
      defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || \
      defined(NRF52840_CLUE) || defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) \
      || defined(NINA_B302_ublox) || defined(NINA_B112_ublox) )
  #error This code is designed to run on nRF52 platform! Please check your Tools->Board setting.
#endif

// These define's must be placed at the beginning before #include "NRF52TimerInterrupt.h"
// Don't define NRF52_TIMER_INTERRUPT_DEBUG > 2. Only for special ISR debugging only. Can hang the system.
#define NRF52_TIMER_INTERRUPT_DEBUG      1

//#ifndef LED_BUILTIN
//  #define LED_BUILTIN         3
//#endif

#ifndef LED_BLUE_PIN
  #define LED_BLUE_PIN          7
#endif

#ifndef LED_RED
  #define LED_RED               8
#endif
   
#include "NRF52TimerInterrupt.h"
#include "NRF52_ISR_Timer.h"

#define HW_TIMER_INTERVAL_MS      1

// Depending on the board, you can select NRF52 Hardware Timer from NRF_TIMER_1-NRF_TIMER_4 (1 to 4)
// If you select the already-used NRF_TIMER_0, it'll be auto modified to use NRF_TIMER_1

// Init NRF52 timer NRF_TIMER1
NRF52Timer ITimer(NRF_TIMER_1);

// Init NRF52_ISR_Timer
// Each NRF52_ISR_Timer can service 16 different ISR-based timers
NRF52_ISR_Timer ISR_Timer;

#define TIMER_INTERVAL_1S             1000L
#define TIMER_INTERVAL_2S             2000L
#define TIMER_INTERVAL_5S             5000L

void TimerHandler(void)
{
  ISR_Timer.run();
}

// In NRF52, avoid doing something fancy in ISR, for example complex Serial.print with String() argument
// The pure simple Serial.prints here are just for demonstration and testing. Must be eliminate in working environment
// Or you can get this run-time error / crash
void doingSomething1()
{
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void doingSomething2()
{
  digitalWrite(LED_BLUE, !digitalRead(LED_BLUE));
}
void doingSomething3()
{
  digitalWrite(LED_RED, !digitalRead(LED_RED));
}

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.printf("\nStarting TimerInterruptLEDDemo on %s\n", BOARD_NAME);
  Serial.printf("Version : v%s\n", NRF52_TIMER_INTERRUPT_VERSION);
  Serial.println("CPU Frequency = " + String(F_CPU / 1000000) + " MHz");

  // configure pin in output mode
  pinMode(LED_BUILTIN,  OUTPUT);
  pinMode(LED_BLUE,     OUTPUT);
  pinMode(LED_RED,      OUTPUT);

  // Interval in microsecs
  if (ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_MS * 1000, TimerHandler))
  {
    Serial.printf("Starting  ITimer OK, millis() = %ld\n", millis());
  }
  else
    Serial.println("Can't set ITimer correctly. Select another freq. or interval");

  // Just to demonstrate, don't use too many ISR Timers if not absolutely necessary
  // You can use up to 16 timer for each ISR_Timer
  ISR_Timer.setInterval(TIMER_INTERVAL_1S,  doingSomething1);
  ISR_Timer.setInterval(TIMER_INTERVAL_2S,  doingSomething2);
  ISR_Timer.setInterval(TIMER_INTERVAL_5S,  doingSomething3);
}


void loop()
{
  /* Nothing to do all is done by hardware. Even no interrupt required. */
}
