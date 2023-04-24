#include <LiquidCrystal.h>
#include <DHT.h>
#include <DHT_U.h>
#include "SPI.h"
#define DHTPIN 4                  // temperature sensor pin
#define DHTTYPE DHT11             // type of DHT sensor
DHT_Unified dht(DHTPIN, DHTTYPE); // setup the temperature sensor

// initialize the library by associating any needed LCD interface pin
// LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void setup()
{
  lcd.begin(16, 2);              // initialize the LCD with 2 rows of 16 characters
  lcd.print("*** Starting ***"); // print this literal starting on line 0 column 0 - since nothing different was specified
  lcd.setCursor(0, 1);           // set the cursor to the first position (column) of the second line
  lcd.print("** Thermostat **");
  delay(4000); // wait for 4 seconds
  dht.begin(); // initialize the temperature sensor
  lcd.clear(); // clear the LCD before proceeding
}

void loop()
{
  sensors_event_t event; // declare an event to capture temperature and humidity data

  dht.temperature().getEvent(&event); // get an event (reading) from the temperature sensor.
  if (isnan(event.temperature))       // check if the value read from sensor is not a number
  {
    // if is not a number, do nothing
  }
  else
  {
    lcd.setCursor(0, 0);          // position the cursor back to column 1, line 1
    lcd.print("Temp:");           // print
    lcd.setCursor(6, 0);          // move the cursor to the 7th column, still line 1
    lcd.print(event.temperature); // print the temperature
    lcd.setCursor(12, 0);         // move the cursor to the 12th column, still line 1
    lcd.print((char)223);         // print the degree symbol, which happens to be 223 from the ASCII table
    lcd.setCursor(13, 0);         // move the cursor again
    lcd.print("C");               // print the "C"
  }

  dht.humidity().getEvent(&event);
  // a different approach with double negative: check if the value read from sensor is not not a number
  if (!isnan(event.relative_humidity))
  {
    lcd.setCursor(0, 1);
    lcd.print("Humi:");
    lcd.setCursor(6, 1);
    lcd.print(event.relative_humidity);
    lcd.setCursor(12, 1);
    lcd.print("%");
  }
  
  // can't read more than once a second or the sensor will heat up
  // so make the Arduino blink a little cursor at the bottom right corner of the screen
  // for 2 seconds before reading again
  lcd.setCursor(15, 1);
  lcd.print(char(165));
  delay(1000);
  lcd.setCursor(15, 1);
  lcd.print(" ");
  delay(1000);
}
