#include <LiquidCrystal.h>  

// initialize the library by associating any needed LCD interface pin
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

int light = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.print("*** Embedded ***");
  lcd.setCursor(0, 1);
  lcd.print("* Development  *");
  delay(5000);
  lcd.clear();
}

void loop() 
{
    light = analogRead(A0);
    
    lcd.setCursor(0, 0);
    lcd.print("Light Value:");
    lcd.setCursor(12,0);
    lcd.print(light);
     
    //adding a little delay so the readings won't go crazy
    lcd.setCursor(15, 1);
    lcd.print(char(165));
    delay(800);
    lcd.setCursor(15, 1);
    lcd.print(" ");
    delay(800);
}
