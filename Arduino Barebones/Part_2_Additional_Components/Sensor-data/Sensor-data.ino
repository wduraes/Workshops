#include <LiquidCrystal.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "SPI.h"

DHT_Unified dht(6, DHT11);  //create an instance of the Sensor with the name DHT, connected ot Pin 6 and model DHT11.

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);  //create an instance of an LCD screen with the name "lcd" passing the used pins as required parameters

void setup() 
{
  lcd.begin(20, 4);
  lcd.print("hello, world!");
  delay(2000);
  lcd.clear();

  pinMode(A1, INPUT); //Pin to read light values
  dht.begin();        //initializes the sensor
}

void loop() 
{
  sensors_event_t event;
  
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.setCursor(3, 0);  //set the cursor to the 4th column, first line
  
  dht.temperature().getEvent(&event);

/*
 * Sometimes the sensor will send back garbage data. 
 * To prevent that from going to the screen, we use a double-negative IF. 
 * Boolean function isnan() (is not a number) return TRUE is the value is not a number
 * We added the NOT operator (!) in front of it, turning the whole thing into a double-negative
 * "If not is not a number" becomes "If it is a number" 
 * Easy huh? :-)
 */
  
  if(!isnan(event.temperature))  
  {
    float tempMeasurement = event.temperature;
    
    // The measurement is in Celsius. If you want it in Fahrenheit,
    // uncomment the following line:
    // tempMeasurement = (event.temperature * 1.8) + 32;
    
    lcd.print(tempMeasurement);  
  } 

  lcd.setCursor(10, 0);
  lcd.print("L:");
  lcd.setCursor(13, 0);  //set the cursor to the 4th column, second line
  lcd.print(analogRead(A1));  

  lcd.setCursor(0, 1);
  lcd.print("H:");
  lcd.setCursor(3, 1);  //set the cursor to the 4th column, second line
  
  dht.humidity().getEvent(&event);
  if(!isnan(event.relative_humidity))
  {
    lcd.print(event.relative_humidity);  
  } 
  delay(100); 
}
