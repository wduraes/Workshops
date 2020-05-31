#define BTN 2
#define LED 6
int counter = 0;
bool pressed = false;
bool state = false;

void setup() 
{
  pinMode(BTN,INPUT);
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
  Serial.println("Started...");
}

void loop() 
{
  if(digitalRead(BTN)==HIGH && pressed==0)
  {
    pressed = 1;
    state = !state;
    counter++;
    Serial.println(counter);
    digitalWrite(LED,state);
  }
  else if(digitalRead(BTN)==LOW && pressed==1)   
  {
    pressed = 0;
    delay(200);
  }
}
