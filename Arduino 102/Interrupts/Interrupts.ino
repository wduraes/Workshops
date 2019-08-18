//Interrupt Example
bool ledState = 0;

void setup()
{
  // initialize the LED pins as outputs:
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);

  // initialize the pushbutton pin as an input:
  pinMode(2, INPUT_PULLUP);

  // Attach an interrupt to the ISR vector
  attachInterrupt(0, pin_ISR, FALLING);
}

void loop()
{
  digitalWrite(13, LOW);
  delay(1000);
  digitalWrite(13, HIGH);
  delay(1000);
}

void pin_ISR()
{
  //buttonState = digitalRead(buttonPin);
  ledState = !ledState;
  digitalWrite(8, ledState);
}
