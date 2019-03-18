int button=0;
void setup() 
{
  pinMode(A0, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}
void loop() 
{
button = digitalRead(A0);
Serial.print("Button value: ");
Serial.println(button);
delay(50);
   if(button==LOW)
   {digitalWrite(13, HIGH);}
   else
   {digitalWrite(13, LOW);}
}

