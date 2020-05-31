//Interrupt Example
#define LED 6
#define BTN 2
int Delay_Time = 1000;

void setup()
{
  // initialize the LED pin as output:
  pinMode(LED, OUTPUT);
  
  // initialize the pushbutton pin as an input:
  pinMode(BTN, INPUT);
}

void loop()
{
  digitalWrite(LED, LOW);
  delay(Delay_Time);
  digitalWrite(LED, HIGH);
  delay(Delay_Time);

  if (digitalRead(BTN) == HIGH)
  {
    Delay_Time = 100;
  } 
}
