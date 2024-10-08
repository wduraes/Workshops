## LCD Display with the Temperature and Humidity Sensor

The DHT11 is a low-cost temperature and humidity sensor that can be used with microcontroller systems like Arduino. It has a simple digital interface, making it easy to get temperature and humidity readings in your projects.

The sensor uses a humidity sensing element and a thermistor to measure the surrounding air, and sends a digital signal to the microcontroller with the data. The DHT11 is a popular choice for projects that need to monitor conditions like temperature and humidity in a room or enclosure.

<img src="../Images/dht11.png" width="70%">


### Installing the DHT11 library

Before we can use the DHT11 sensor we’ll need to get an external library that enables it in the Arduino IDE.

- Open `Sketch/Include Library/Manage Libraries`
- Type `DHT11` (wait to results to load)
- Select `DHT Sensor Library by Adafruit` and hit install
- If you get prompted about adding additional dependency libraries, accept and **install them all**.

**Restriction**: don’t do more than 1 read at every 2 seconds, or the sensor will warm up affecting its reading capabilities.

These sensors are **NOT recommended** for professional use: Use the AHT20, or BME280 instead which are much more precise but more expensive as well.

<img src="../Images/dht11-2.png" width="50%">

The illustration below shows how to wire the LDR to the Arduino:

<img src="../Images/dht11-4.png" width="80%">

### DHT11 code

```c
#include <LiquidCrystal.h>  
#include <DHT.h>
#include <DHT_U.h>
#include "SPI.h"
#define DHTPIN 4     // what pin we're connected to on the temperature sensor
#define DHTTYPE DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);

// initialize the library by associating any needed LCD interface pin
//LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("*** Starting ***");
  lcd.setCursor(0, 1);
  lcd.print("** Thermostat **");
  delay(4000);
  dht.begin();
  lcd.clear();
}

void loop() 
{
  sensors_event_t event;  

  dht.temperature().getEvent(&event); 
  //checking for non-number values BEFORE publishing 
    if(isnan(event.temperature))
    {
      //do nothing
    }
    else
    {
          lcd.setCursor(0, 0);
          lcd.print("Temp:");
          lcd.setCursor(6,0);
          lcd.print(event.temperature);
          lcd.setCursor(12, 0);
          lcd.print((char)223);   //223 is the degree symbol, from the ASCII table
          lcd.setCursor(13, 0);
          lcd.print("C");
    }
    
    dht.humidity().getEvent(&event);
    //checking for non-number values BEFORE publishing
    if(isnan(event.relative_humidity))
    {
      //do nothing
    }
    else
    {
          lcd.setCursor(0, 1);
          lcd.print("Humi:");
          lcd.setCursor(6,1);
          lcd.print(event.relative_humidity);
          lcd.setCursor(12, 1);
          lcd.print("%");
    }
    //can't read more than once a second or the sensor will heat up
    lcd.setCursor(15, 1);
    lcd.print(char(165));
    delay(1000);
    lcd.setCursor(15, 1);
    lcd.print(" ");
    delay(1000);
}
```