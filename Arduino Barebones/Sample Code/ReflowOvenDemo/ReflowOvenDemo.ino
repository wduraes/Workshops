/*
Sample code I use in my Reflow Demo board
*/
#include <LiquidCrystal.h>
#include <Wire.h>
int contador;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  pinMode(3,0); //btn_abort
  pinMode(2,0); //btn_start
  pinMode(6,1); //buzzer
  pinMode(14,1); //led_vm
  pinMode(15,1); //led_am
  
  lcd.begin(20, 4);
  
  lcd.setCursor(0, 0);
  lcd.print("  SNOCO MAKERSPACE");
  lcd.setCursor(0, 1);
  lcd.print("SMD Reflow Oven V1.3");
  lcd.setCursor(0, 2);
  lcd.print("--------------------");
  lcd.setCursor(0, 3);
  lcd.print(" Counter = 0");
  
  tone(6,1000);
  delay(150);
  noTone(6);
  delay(50);
  tone(6,1000);
  delay(150);
  noTone(6);

  contador =1;
}

void loop() 
{
 if(digitalRead(3)==1)
 {
    digitalWrite(14,0); 
    noTone(6);
 }
 else
 {
    digitalWrite(14,1); 
    tone(6,400);
    lcd.setCursor(11, 3);
    lcd.print(contador);
    contador++;
    delay(200);
 }

 if(digitalRead(2)==1)
 {
    digitalWrite(15,0); 
 }
 else
 {
    digitalWrite(15,1);
    contador = 0; 
    lcd.setCursor(0, 3);
    lcd.print(" Counter = 0    ");
 } 
}
