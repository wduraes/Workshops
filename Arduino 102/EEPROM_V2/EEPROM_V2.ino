#include <EEPROM.h>

bool pressed = 0;
bool ledState = 0;

void setup() {
  pinMode(2,INPUT_PULLUP);
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  checkLedState();
}

void loop() {
  if(digitalRead(2)==LOW && pressed==0)
  {
    ledState = !ledState;
    digitalWrite(13,ledState);
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
void checkLedState() {
   Serial.println("LED status after restart: ");
   ledState = EEPROM.read(0);
   if(ledState == 1) {
    Serial.println ("ON");
    digitalWrite(13, HIGH);
   } 
   if(ledState == 0) {
    Serial.println ("OFF");
    digitalWrite(13, LOW);
   }
}
