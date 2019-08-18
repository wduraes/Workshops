//Interrupt Example
bool ledState = 0;

void setup()
{
  // initialize the LED pins as outputs:
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);

  // initialize the pushbutton pin as an input:
  pinMode(2, INPUT_PULLUP);
}

void loop()
{
  digitalWrite(13, LOW);
  delay(1000);
  digitalWrite(13, HIGH);
  delay(1000);

  if (digitalRead(2) == LOW)
  {
    ledState = !ledState;
    digitalWrite(8, ledState);
  }
}
