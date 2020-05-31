#define BTN 2
int counter = 0;
bool pressed = false;

void setup() 
{
  pinMode(BTN,INPUT);
  Serial.begin(9600);
  Serial.println("Started...");
}

void loop() 
{
  if(digitalRead(BTN)==HIGH && pressed==0)
  {
    pressed = 1;
    counter++;
    Serial.print("Millis now: ");
    Serial.println(millis());
  }
  else if(digitalRead(BTN)==LOW && pressed==1)   
  {
    pressed = 0;
    delay(200);
  }
}


/*
int period = 1000;
unsigned long time_now = 0;
 
void setup() {
    Serial.begin(9600);
}
 
void loop() {
    if(millis() > time_now + period){
        time_now = millis();
        Serial.print("Hello, the time is: ");
        Serial.print(millis()/1);
        Serial.println(" sec");
    }
   
    //Run other code
}
*/
