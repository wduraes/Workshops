# DHT11 with a button

This sample shows how to add a button to pin 3 which will control if the LCD display will show the temperature in Celsius or Fahrenheit.

It is a more advanced sample which uses an interrupt triggered by the button.

**Important**: You'll need a 10K pull down resistor connected to Pin 3 to give it a reference, otherwise the button won't work. 

```c
#include <LiquidCrystal.h>  
#include <DHT.h>
#include <DHT_U.h>
#include "SPI.h"
#define DHTPIN 4     // what pin we're connected to on the temperature sensor
#define DHTTYPE DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);
bool show_Celsius = false;

// initialize the library by associating any needed LCD interface pin
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void setup() 
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("*** Starting ***");
  lcd.setCursor(0, 1);
  lcd.print("** Thermostat **");
  delay(4000);
  dht.begin();
  lcd.clear();

  // Connect a button to Pin 2
  // Attach an interrupt to pin 2, on the rising edge, 
  // calling a function named Interrupt_Handling 
  attachInterrupt(digitalPinToInterrupt(2), Interrupt_Handling, RISING);
}

void loop() 
{
  sensors_event_t event;  

  dht.temperature().getEvent(&event); 
  //checking for non-number values BEFORE publishing 
    if(!isnan(event.temperature))
    {
          lcd.setCursor(0, 0);
          lcd.print("Temp:");
          lcd.setCursor(6,0);
          if(show_Celsius)
          {
              lcd.print(event.temperature);
              lcd.setCursor(12, 0);
              lcd.print((char)223);   //223 is the degree symbol, from the ASCII table
              lcd.setCursor(13, 0);
              lcd.print("C  ");
          }
          else
          {
              lcd.print((event.temperature*1.8)+32);
              lcd.setCursor(12, 0);
              lcd.print((char)223);   //223 is the degree symbol, from the ASCII table
              lcd.setCursor(13, 0);
              lcd.print("F  ");
          }
    }
    
    dht.humidity().getEvent(&event);
    //checking for non-number values BEFORE publishing
    if(!isnan(event.relative_humidity))
    {
          lcd.setCursor(0, 1);
          lcd.print("Humi:");
          lcd.setCursor(6,1);
          lcd.print(event.relative_humidity);
          lcd.setCursor(12, 1);
          lcd.print("%");
    }
    //can't try to read more than once a second or the sensor will heat up
    lcd.setCursor(15, 1);
    lcd.print(char(165));
    delay(800);
    lcd.setCursor(15, 1);
    lcd.print(" ");
    delay(800);
}

void Interrupt_Handling()
{
  show_Celsius = !(show_Celsius);
  resetDisplay();
}

void  resetDisplay(){
  lcd.setCursor(0, 0);
  lcd.print("Temp:           ");
  delay(500);
}

```

### Code explained

This code uses a temperature sensor and an LCD display to create a thermostat. The code includes the necessary libraries for using the LiquidCrystal library for the LCD display and the DHT library for the temperature sensor. The temperature sensor is of the DHT11 type, and is connected to digital pin 4 on the Arduino board.

In the setup() function, the LCD display is initialized, and a message is displayed on the screen. The temperature sensor is also initialized. An interrupt is also set up on digital pin 2, so that when a rising edge is detected on that pin, the Interrupt_Handling function is called.

The loop() function continuously reads the temperature and humidity from the sensor, and displays the values on the LCD display. The values are displayed in either Celsius or Fahrenheit, depending on the state of the show_Celsius boolean variable. This variable is toggled each time the interrupt on digital pin 2 is triggered. The loop() function also includes some code to blink a symbol on the LCD display every 800 milliseconds.

The Interrupt_Handling() function simply toggles the value of the show_Celsius boolean variable. This function is called each time a rising edge is detected on digital pin 2.
