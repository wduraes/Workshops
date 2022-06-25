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
              lcd.print("C");
          }
          else
          {
              lcd.print((event.temperature*1.8)+32);
              lcd.setCursor(12, 0);
              lcd.print((char)223);   //223 is the degree symbol, from the ASCII table
              lcd.setCursor(13, 0);
              lcd.print("F");
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
  delay(100);
}
