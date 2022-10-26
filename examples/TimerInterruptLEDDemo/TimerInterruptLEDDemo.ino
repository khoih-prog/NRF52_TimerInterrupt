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

// These define's must be placed at the beginning before #include "NRF52TimerInterrupt.h"
// _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
// Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
// Don't define TIMER_INTERRUPT_DEBUG > 2. Only for special ISR debugging only. Can hang the system.
#define TIMER_INTERRUPT_DEBUG         0
#define _TIMERINTERRUPT_LOGLEVEL_     0

//#ifndef LED_BUILTIN
//  #define LED_BUILTIN         3
//#endif

#ifndef LED_BLUE_PIN
  #if defined(LED_BLUE)
    #define LED_BLUE_PIN          LED_BLUE
  #else
    #define LED_BLUE_PIN          7
  #endif
#endif

#ifndef LED_GREEN_PIN
  #if defined(LED_GREEN)
    #define LED_GREEN_PIN           LED_GREEN
  #else
    #define LED_GREEN_PIN           8
  #endif
#endif

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "NRF52TimerInterrupt.h"

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
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

void TimerHandler()
{
  ISR_Timer.run();
}

// In NRF52, avoid doing something fancy in ISR, for example complex Serial.print with String() argument
// The pure simple Serial.prints here are just for demonstration and testing. Must be eliminate in working environment
// Or you can get this run-time error / crash
void doingSomething1()
{
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

#if (TIMER_INTERRUPT_DEBUG > 0)
  Serial.println("G");
#endif
}

void doingSomething2()
{
  digitalWrite(LED_BLUE_PIN, !digitalRead(LED_BLUE_PIN));

#if (TIMER_INTERRUPT_DEBUG > 0)
  Serial.println("B");
#endif
}
void doingSomething3()
{
  digitalWrite(LED_GREEN_PIN, !digitalRead(LED_GREEN_PIN));

#if (TIMER_INTERRUPT_DEBUG > 0)
  Serial.println("R");
#endif
}

void setup()
{
  Serial.begin(115200);

  while (!Serial && millis() < 5000);

  delay(100);

  Serial.print(F("\nStarting TimerInterruptLEDDemo on "));
  Serial.println(BOARD_NAME);
  Serial.println(NRF52_TIMER_INTERRUPT_VERSION);
  Serial.print(F("CPU Frequency = "));
  Serial.print(F_CPU / 1000000);
  Serial.println(F(" MHz"));

  // configure pin in output mode
  pinMode(LED_BUILTIN,    OUTPUT);
  pinMode(LED_BLUE_PIN,   OUTPUT);
  pinMode(LED_GREEN_PIN,  OUTPUT);

  // Interval in microsecs
  if (ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_MS * 1000, TimerHandler))
  {
    Serial.print(F("Starting ITimer OK, millis() = "));
    Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer. Select another freq. or timer"));

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
