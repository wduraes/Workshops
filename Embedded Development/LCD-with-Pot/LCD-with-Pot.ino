#include <LiquidCrystal.h>  

// initialize the library by associating any needed LCD interface pin
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

int light = 0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("*** Starting ***");
  lcd.setCursor(0, 1);
  lcd.print("  Potentiometer ");
  delay(4000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Value:");
}

void loop() 
{

    light = analogRead(A0);

    //need to check the number of digits to correctly display values
    if(light>1000)
    {
      lcd.setCursor(8,0);
      lcd.print(light);
    }
    else if(light<100)
    {
      lcd.setCursor(9,0);
      lcd.print(light);
      lcd.setCursor(11,0);
      lcd.print(" ");
    }    
    else
    {
      lcd.setCursor(8,0);
      lcd.print(" ");
      lcd.setCursor(9,0);
      lcd.print(light);
    }   
     
    //adding a little delay so the readings won't go crazy
    lcd.setCursor(15, 1);
    lcd.print(char(165));
    delay(200);
    lcd.setCursor(15, 1);
    lcd.print(" ");
    delay(200);
}
