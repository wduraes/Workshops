#include <LiquidCrystal.h>  
const int pingPin = 3; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 4; // Echo Pin of Ultrasonic Sensor

// initialize the library by associating any needed LCD interface pin
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

int light = 0;

void setup() {
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.begin(16, 2);
  lcd.print("*** Embedded ***");
  lcd.setCursor(0, 1);
  lcd.print("* Development  *");
  delay(5000);
  lcd.clear();
}

void loop() 
{
   long duration, inches, cm;
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   
   duration = pulseIn(echoPin, HIGH);
   inches = microsecondsToInches(duration);
   cm = microsecondsToCentimeters(duration);
   
    lcd.setCursor(0, 0);
    lcd.print("Dist:      ");
    lcd.setCursor(6,0);
    lcd.print(cm);
    lcd.setCursor(10,0);
    lcd.print("cm");

    lcd.setCursor(0, 1);
    lcd.print("Dist:      ");
    lcd.setCursor(6,1);
    lcd.print(inches);
    lcd.setCursor(10,1);
    lcd.print("in");
     
    //adding a little delay so the readings won't go crazy
    lcd.setCursor(15, 1);
    lcd.print(char(165));
    delay(80);
    lcd.setCursor(15, 1);
    lcd.print(" ");
    delay(80);
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
