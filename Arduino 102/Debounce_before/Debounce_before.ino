#define BTN 2
#define LED 6
int counter = 0;
bool state = false;

void setup() 
{
  pinMode(BTN,INPUT_PULLUP);
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
  Serial.println("Started...");
}

void loop() 
{
  if(digitalRead(BTN)==LOW)
  {
    state = !state;
    digitalWrite(LED,state);
    counter++;
    Serial.print("The Led is: ");
    if(state)
    {
      Serial.print("ON -  ");
      Serial.println(counter);  
    }
    else
    {
      Serial.print("OFF - ");  
      Serial.println(counter);
    }        
  }
}
