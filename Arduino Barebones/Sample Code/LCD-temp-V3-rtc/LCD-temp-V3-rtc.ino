//Bare metal LCD sample
//This sketch will show the light reading in the display

#include <LiquidCrystal.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "SPI.h"
#include "RTClib.h"

RTC_DS1307 rtc;

#define DHTPIN 6 // pin connected to the temperature sensor
#define DHTTYPE DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);

bool startstop = true;
volatile int sec = 0, minute = 0, hour = 0;

long debouncing_time = 150; //Debouncing Time in Milliseconds
volatile unsigned long last_micros = 0;
volatile unsigned long last_micros_clock = 0;
volatile unsigned long last_micros_sensor = 0;

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() 
{
  pinMode(A1,INPUT);
  pinMode(5,OUTPUT);
  pinMode(14,OUTPUT);
  digitalWrite(5,1);
  
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  //Power on Beep
  tone(14,1000);
  delay(200);
  noTone(14);
  delay(200);
  tone(14,1000);
  delay(200);
  noTone(14);

  attachInterrupt(digitalPinToInterrupt(2), buttons, FALLING);
  
  dht.begin();        //initialize the ambient sensor
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("--Initializing--");  
  delay(2000);
  lcd.clear();

  if (! rtc.begin()) 
  {
    lcd.print("Couldn't get RTC");  
    delay(2000);
    lcd.clear();
  }

   lcd.setCursor(0, 1);
   lcd.print("Waiting DHT data");
  
  //Uncomment line below to set the RTC with this date: Format - Year, Month, Day, Hour, Minute and Second.
  //rtc.adjust(DateTime(2020, 11, 7, 10, 29, 0));
}

void controlBacklight()
{
  //check the light reading and control the LCD backlight
  if(analogRead(A1)>200)
  {
    digitalWrite(5,1);
  }
  else
  {
    digitalWrite(5,0);
  }
}


void printSensor()
{
  //get temperature and humidity
  sensors_event_t event;
      
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
    
    lcd.setCursor(0, 1);
    lcd.print("T=");
    lcd.setCursor(2, 1);
    dht.temperature().getEvent(&event);
    
    float tempMeasurement = event.temperature;
    // The measurement is in Celsius. If you want it in Fahrenheit,
    // uncomment the following line:
    // tempMeasurement = (event.temperature * 1.8) + 32;
    int t = round(tempMeasurement);
  
    lcd.print(t);
    if (t<10) //prevent garbage for single digit temperature
    {
      lcd.setCursor(4, 1);
      lcd.print(" ");      
    }
    lcd.setCursor(4, 1);
    lcd.print(char(223)); //the Degree symbol 
    lcd.setCursor(5, 1);
    lcd.print("C   ");
      
    lcd.setCursor(9, 1);
    lcd.print("H=");
    lcd.setCursor(11, 1);
    dht.humidity().getEvent(&event);
    int h = event.relative_humidity;
    lcd.print(h);
    lcd.setCursor(13, 1);
    lcd.print("%  ");   

    delay(50);
    
}

//ISR to Start/Stop the clock
void buttons()
{
    if((long)(micros() - last_micros) >= debouncing_time * 1000) 
    {
    Interrupt();
    last_micros = micros();
    }
}
  
void Interrupt()
{
  lcd.clear();
  startstop = !startstop;
}

void Clock()
{
  //Get data from RTC and print on LCD screen
  DateTime time = rtc.now();

  minute = time.minute(); 
  hour = time.hour();
    
  lcd.setCursor(0, 0);
  lcd.print("Clock ");
  if (time.hour() < 10)
  {
    lcd.print("0");
    lcd.print(time.hour());
  }
  else
  {
    lcd.print(time.hour());
  }
  lcd.print(":");
  if (time.minute() < 10)
  {
    lcd.print("0");
    lcd.print(time.minute());
  }
  else
  {
    lcd.print(time.minute());
   } lcd.print(":");
  if (time.second() < 10)
  {
    lcd.print("0");
    lcd.print(time.second());
  }
  else
  {
    lcd.print(time.second());
  }
  lcd.print(" ");
}

void loop() 
{
  //Setting the time will stop the clock
  while (startstop == false)
  {
    lcd.setCursor(0, 1);
    lcd.print("-Clock set MODE- ");
    delay(100);
    lcd.setCursor(0, 0);
    lcd.print("Time: ");
    if(hour<10)
    {
    lcd.print("0");
    lcd.print(hour);
    }
    else
    lcd.print(hour);
    lcd.print(":");
    if(minute<10)
    {
    lcd.print("0");
    lcd.print(minute);
    }
    else
    lcd.print(minute);
    lcd.print(":");
    if(sec<10)
    {
    lcd.print("0");  
    lcd.print(sec);
    }
    else
    lcd.print(sec);
    lcd.print(" ");
    
    if (digitalRead(1) == LOW)
    {
      hour++;
      if (hour > 23)
        hour = 0;
    }
    if (digitalRead(3) == LOW)
    {
      minute++;
      if (minute > 59)
        minute = 0;
    }
    rtc.adjust(DateTime(2020, 11, 7, hour, minute, 0));
  }

  //check if 1 second has passed for clock update
  if((long)(millis() - last_micros_clock) >= 1000) 
  {
    last_micros_clock = millis();
    Clock();
    controlBacklight(); 
  }  

  //check if 10 seconds has passed for clock update
  if((long)(millis() - last_micros_sensor) >= 10000) 
  {
    last_micros_sensor = millis();
    printSensor();  
   }   
}
