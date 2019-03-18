int button=0;
void setup() 
{
  pinMode(A0, INPUT_PULLUP);
  pinMode(13, OUTPUT);
}
void loop() 
{
button = digitalRead(A0);
   if(button==LOW)
   {digitalWrite(13, HIGH);}
   else
   {digitalWrite(13, LOW);}
}

