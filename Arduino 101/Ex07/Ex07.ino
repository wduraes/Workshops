#include <Servo.h>
Servo myservo; 
int pos = 0;
void setup() {
  myservo.attach(9); 
  pinMode(A0,INPUT);
}
void loop() {
  pos = map(analogRead(A0),0,1023,0,180);
  myservo.write(pos);    
  delay(20);
}

