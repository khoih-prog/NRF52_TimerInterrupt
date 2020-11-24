/****************************************************************************************************************************
   SwitchDebounce.ino
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

   Switch Debouncing uses high frequency hardware timer 50Hz == 20ms) to measure the time from the SW is pressed,
   debouncing time is 100ms => SW is considered pressed if timer count is > 5, then call / flag SW is pressed
   When the SW is released, timer will count (debounce) until more than 50ms until consider SW is released.
   We can set to flag or call a function whenever SW is pressed more than certain predetermined time, even before
   SW is released.
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

#include "NRF52TimerInterrupt.h"

//#ifndef LED_BUILTIN
//  #define LED_BUILTIN       13
//#endif

#ifndef LED_BLUE
  #define LED_BLUE          7
#endif

#ifndef LED_RED
  #define LED_RED           8
#endif

unsigned int SWPin = 11;

#define TIMER_INTERVAL_MS         10
#define DEBOUNCING_INTERVAL_MS    100
#define LONG_PRESS_INTERVAL_MS    5000

// Depending on the board, you can select NRF52 Hardware Timer from NRF_TIMER_1-NRF_TIMER_4 (1 to 4)
// If you select the already-used NRF_TIMER_0, it'll be auto modified to use NRF_TIMER_1

// Init NRF52 timer NRF_TIMER1
NRF52Timer ITimer(NRF_TIMER_1);

volatile bool SWPressed     = false;
volatile bool SWLongPressed = false;

unsigned int debounceCountSWPressed  = 0;
unsigned int debounceCountSWReleased = 0;
bool toggle0 = false;
bool toggle1 = false;
  
void TimerHandler(void)
{
  if ( (!digitalRead(SWPin)) )
  {
    // Start debouncing counting debounceCountSWPressed and clear debounceCountSWReleased
    debounceCountSWReleased = 0;

    if (++debounceCountSWPressed >= DEBOUNCING_INTERVAL_MS / TIMER_INTERVAL_MS)
    {
      // Call and flag SWPressed
      if (!SWPressed)
      {
        SWPressed = true;
        // Do something for SWPressed here in ISR
        // But it's better to use outside software timer to do your job instead of inside ISR
        //Your_Response_To_Press();
        digitalWrite(LED_BUILTIN, toggle0);
        toggle0 = !toggle0;
      }

      if (debounceCountSWPressed >= LONG_PRESS_INTERVAL_MS / TIMER_INTERVAL_MS)
      {
        // Call and flag SWLongPressed
        if (!SWLongPressed)
        {
          SWLongPressed = true;
          // Do something for SWLongPressed here in ISR
          // But it's better to use outside software timer to do your job instead of inside ISR
          //Your_Response_To_Long_Press();
          digitalWrite(LED_BLUE, toggle1);
          toggle1 = !toggle1;
        }
      }
    }
  }
  else
  {
    // Start debouncing counting debounceCountSWReleased and clear debounceCountSWPressed
    if ( SWPressed && (++debounceCountSWReleased >= DEBOUNCING_INTERVAL_MS / TIMER_INTERVAL_MS))
    {
      // Call and flag SWPressed

      SWPressed     = false;
      SWLongPressed = false;

      // Do something for !SWPressed here in ISR
      // But it's better to use outside software timer to do your job instead of inside ISR
      //Your_Response_To_Release();

      // Call and flag SWPressed
      debounceCountSWPressed = 0;
    }
  }
}

void setup()
{
  pinMode(SWPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_BLUE,    OUTPUT);

  Serial.begin(115200);
  while (!Serial);

  delay(100);

  Serial.printf("\nStarting SwitchDebounce on %s\n", BOARD_NAME);
  Serial.printf("Version : v%s\n", NRF52_TIMER_INTERRUPT_VERSION);
  Serial.println("CPU Frequency = " + String(F_CPU / 1000000) + " MHz");
 
  // Interval in microsecs
  if (ITimer.attachInterruptInterval(TIMER_INTERVAL_MS * 1000, TimerHandler))
    Serial.printf("Starting  ITimer OK, millis() = %ld\n", millis());
  else
    Serial.println("Can't set ITimer. Select another freq., duration or timer");
}

void printResult(uint32_t currTime)
{
  Serial.printf("Time = %ld, Switch = %s\n", currTime, SWLongPressed? "LongPressed" : (SWPressed? "Pressed" : "Released") );
}

#define CHECK_INTERVAL_MS     1000L

void loop()
{
  static uint32_t lastTime = 0;
  static uint32_t currTime;

  currTime = millis();

  if (currTime - lastTime > CHECK_INTERVAL_MS)
  {
    printResult(currTime);
    lastTime = currTime;
  }
}
