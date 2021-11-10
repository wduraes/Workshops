## SnocoDuino

Simply put, Snocoduino is the Snoco Makerspace implementation of the famous Arduino Uno board. 
As a matter of fact, it was modeled after the Arduino Nano Schematics with a twist.
Arduino and all its different boards are open hardware meaning that it’s schematics are available for free and there are no “special” components making it hard / impossible to recreate. 

  ![SnocoDuino Picture](Images/Snocoduino_Picture.PNG)

## Sconoduino Characteristics:
- Microcontroller: ATmega328
- Operating Voltage: 5Vcc
- Input Voltage (recommended): 7-12V
- Input Voltage (limits): 6-20V
- Digital I/O Pins: 14 (of which 6 provide PWM output)
- Analog Input Pins: 6
- DC Current per I/O Pin: 40 mA
- DC Current for 3.3V Pin: 50 mA
- Flash Memory: 32 KB of which 0.5 KB used by bootloader
- SRAM: 2 KB (ATmega328)
- EEPROM: 1 KB (ATmega328)
- Clock Speed: 16 MHz

## What is different in a Snocoduino?
- NeoPixel connected to Pin 8
- Jumper to disconnect NeoPixel, and use pin 8 for any other purpose if desired
- FT232RL FTDI chip to perform USB to Serial conversion (which doesn't require additional drivers as Arduino IDE already support it) 
- Micro USB port
- Screw power terminals

## Snocoduino schematics

This file is publicly available at [EasyEDA](https://easyeda.com/wduraes/SnocoDuino). It includes both the Schematics and the PCB design.

  ![SnocoDuino schema](Images/Snocoduino_Schema.PNG)


## Test Code
The test code for the SnocoDuino involves blinking the Neopixel and pin 13 where an LED should be added along with a 330R resistor.
Add the Adafruit NeoPixel library before running the code. 

```   
#include <Adafruit_NeoPixel.h>
#define PIN            9
#define NUMPIXELS      1
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() 
{
  pinMode(13,OUTPUT);
  pixels.begin();
  pixels.show();
}

void loop() 
{
  digitalWrite(13,HIGH);
  pixels.setPixelColor(0,0,0,0);
  pixels.show();
  delay(700);
  digitalWrite(13,LOW);
  pixels.setPixelColor(0,55,0,0);
  pixels.show();
  delay(700);
}
```  
  



