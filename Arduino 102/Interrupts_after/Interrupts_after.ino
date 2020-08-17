//Interrupt Example
#define LED 6
#define BTN 2

//why volatile? any variable that can be changed 
//outside of the scope of the main program (loop)
//has to be declared as volatile to avoid compilation
//oprtimization. 

volatile int Delay_Time = 1000;

void setup()
{
  // initialize the LED pin as output:
  pinMode(LED, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);
  
  // Attach an interrupt to pin 2, on the rising edge, 
  // calling a function named Interrupt_Handling 
  attachInterrupt(0, Interrupt_Handling, FALLING);
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
