#include <EEPROM.h>

#define BTN 2
#define LED 6
bool pressed = 0;
bool ledState = 0;

void setup() 
{
  pinMode(BTN,INPUT_PULLUP);
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
  checkLedState();
}

void loop() 
{
  if(digitalRead(BTN)==LOW && pressed==0)
  {
    ledState = !ledState;
    digitalWrite(LED,ledState);
    Serial.print("Led State: ");
    Serial.println(ledState);
    pressed = 1;
    EEPROM.update(0, ledState);
  }
  else if(pressed==1)   
  {
    pressed = 0;
    delay(200);
  }
}

// Prints and upates the LED state
// when the Arduino board restarts or powers up
void checkLedState() 
{
   Serial.println("LED status after restart: ");
   ledState = EEPROM.read(0);
   if(ledState == 1) {
    Serial.println ("ON");
    digitalWrite(LED, HIGH);
   } 
   else 
   {
    Serial.println ("OFF");
    digitalWrite(LED, LOW);
   } 
}
