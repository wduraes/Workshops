//Interrupt Example
#define LED 6
#define BTN 2
volatile int Delay_Time = 1000;

void setup()
{
  // initialize the LED pin as output:
  pinMode(LED, OUTPUT);
  
  // Attach an interrupt to pin 2, on the rising edge, 
  // calling a function named Interrupt_Handling 
  attachInterrupt(digitalPinToInterrupt(0), Interrupt_Handling, RISING);
}

void loop()
{
  digitalWrite(LED, LOW);
  delay(Delay_Time);
  digitalWrite(LED, HIGH);
  delay(Delay_Time);
}

void Interrupt_Handling()
{
  Delay_Time = 100;
}
