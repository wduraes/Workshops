#include <LiquidCrystal.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "SPI.h"

DHT_Unified dht(6, DHT11);  //cria uma instancia do sensor com o nome de dht

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() 
{
  lcd.begin(20, 4);
  lcd.print("hello, world!");
  delay(2000);
  lcd.clear();

  pinMode(A1, INPUT);
  dht.begin();  //inicializando o sensor
}

void loop() 
{
  sensors_event_t event;
  
  lcd.setCursor(0, 0);
  dht.temperature().getEvent(&event);
  if(!isnan(event.temperature))
  {
    lcd.print(event.temperature);  
  } 

  lcd.setCursor(7, 0);
  lcd.print(analogRead(A1));  

  lcd.setCursor(0, 1);
  dht.humidity().getEvent(&event);
  if(!isnan(event.relative_humidity))
  {
    lcd.print(event.relative_humidity);  
  } 
  delay(100); 
}