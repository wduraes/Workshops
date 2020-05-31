/*
  Low Power SLEEP modes for Arduino UNO/Nano using Atmel328P microcontroller chip.
  Based on the great work of Ralph Bacon. 
  All details can be found at https://github.com/ralphbacon
*/

#include "Arduino.h"
#include <avr/sleep.h>

#define INTERVAL_MESSAGE 100
unsigned long time_1 = 0;
bool state1 = 0;

#define sleepPin 4 // When low, makes 328P go to sleep
#define wakePin 2  // when low, makes 328P wake up, must be an interrupt pin (2 or 3 on ATMEGA328P)
#define ledPin 6  // output pin for the LED (to show it is awake)

void setup()
{
  Serial.begin(9600);
  pinMode(sleepPin, INPUT);
  pinMode(wakePin, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.println("Setup completed.");
}

// The loop just blinks an LED when not in sleep mode
void loop()
{
  doBlink();

  // Is the "go to sleep" pin now LOW?
  if (digitalRead(sleepPin) == HIGH)
  {

    // Set the sleep mode
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();

    attachInterrupt(digitalPinToInterrupt(wakePin), sleepISR, HIGH);

    // Send a message just to show we are about to sleep
    Serial.println("Good night!");
    Serial.flush();

    // And enter sleep mode as set above
    sleep_cpu();

    // --------------------------------------------------------
    // Controller is now asleep until woken up by an interrupt
    // --------------------------------------------------------

    // Wakes up at this point when wakePin is brought LOW - interrupt routine is run first
    Serial.println("I'm awake!");

  }
}

// When wakePin is brought LOW this interrupt is triggered FIRST (even in PWR_DOWN sleep)
void sleepISR()
{
  // Prevent sleep mode, so we don't enter it again, except deliberately, by code
  sleep_disable();

  // Detach the interrupt that brought us out of sleep
  detachInterrupt(digitalPinToInterrupt(wakePin));

  // Now we continue running the main Loop() just after we went to sleep
}

void doBlink()
{
  if(millis() > time_1 + INTERVAL_MESSAGE)
  {
    time_1 = millis();
    state1 = not(state1);
    digitalWrite(ledPin,state1);
  }
}
