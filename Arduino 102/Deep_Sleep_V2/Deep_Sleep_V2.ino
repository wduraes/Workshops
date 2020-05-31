/*
   Low Power SLEEP modes for Arduino UNO/Nano using Atmel328P microcontroller chip.
   All details can be found at https://github.com/ralphbacon
*/
#include "Arduino.h"
#include <avr/sleep.h>

#define sleepPin 4 // When low, makes 328P go to sleep
#define wakePin 2  // when low, makes 328P wake up, must be an interrupt pin (2 or 3 on ATMEGA328P)
#define ledPin 6  // output pin for the LED (to show it is awake)

void setup()
{
  Serial.begin(9600);

  // Keep pins high until we ground them
  pinMode(sleepPin, INPUT);
  pinMode(wakePin, INPUT);

  // Flashing LED just to show the �Controller is running
  digitalWrite(ledPin, LOW);
  pinMode(ledPin, OUTPUT);

  Serial.println("Setup completed.");
}

// The loop just blinks an LED when not in sleep mode
void loop()
{

  // Just blink LED twice to show we're running
  doBlink();

  // Is the "go to sleep" pin now LOW?
  if (digitalRead(sleepPin) == HIGH)
  {

    // Disable the ADC (Analog to digital converter, pins A0 [14] to A5 [19])
    static byte prevADCSRA = ADCSRA;
    ADCSRA = 0;

    // Set the sleep mode
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();

    // Turn of Brown Out Detection (low voltage)
    MCUCR = bit(BODS) | bit(BODSE);
    MCUCR = bit(BODS);

    // Ensure we can wake up again by first disabling interupts (temporarily) so
    // the wakeISR does not run before we are asleep and then prevent interrupts,
    // and then defining the ISR (Interrupt Service Routine) to run when poked awake
    noInterrupts();
    attachInterrupt(digitalPinToInterrupt(wakePin), sleepISR, HIGH);

    // Send a message just to show we are about to sleep
    Serial.println("Good night!");
    Serial.flush();

    // Allow interrupts now
    interrupts();

    // And enter sleep mode as set above
    sleep_cpu();

    // --------------------------------------------------------
    // �Controller is now asleep until woken up by an interrupt
    // --------------------------------------------------------

    // Wakes up at this point when wakePin is brought LOW - interrupt routine is run first
    Serial.println("I'm awake!");

    // Re-enable ADC if it was previously running
    ADCSRA = prevADCSRA;
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

// Double blink just to show we are running. Note that we do NOT
// use the delay for final delay here, this is done by checking
// millis instead (non-blocking)
void doBlink()
{
  static unsigned long lastMillis = 0;

  if (millis() > lastMillis + 10)
  {
    digitalWrite(ledPin, HIGH);
    delay(10);
    digitalWrite(ledPin, LOW);
    delay(200);
    digitalWrite(ledPin, HIGH);
    delay(10);
    digitalWrite(ledPin, LOW);
    lastMillis = millis();
  }
}
