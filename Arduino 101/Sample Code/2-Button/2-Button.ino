/*
This code turns an LED on if the button is pressed.
*/
int button=0;
void setup() 
{
  pinMode(A0, INPUT_PULLUP); //connects an internal resistor to VCC
  pinMode(13, OUTPUT);
}
void loop() 
{
button = digitalRead(A0); //Analog input pins also work with Digital inputs
   if(button==LOW)
   {digitalWrite(13, HIGH);}
   else
   {digitalWrite(13, LOW);}
}
