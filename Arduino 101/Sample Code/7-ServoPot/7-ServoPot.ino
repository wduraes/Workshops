/*
This code allow controlling the movement of a servo motor
by varying the position of a potentiometer connected to pin A0
*/
#include <Servo.h>
Servo myservo;
int pos = 0;
void setup()
{
  myservo.attach(9);
  pinMode(A0, INPUT);
  Serial.begin(9600);
}
void loop()
{
  pos = map(analogRead(A0), 0, 1023, 0, 180);
  Serial.println(pos);
  myservo.write(pos);
  delay(230);
}
