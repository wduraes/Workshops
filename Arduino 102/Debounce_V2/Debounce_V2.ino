int counter = 0;
bool pressed = 0;

void setup() {
  pinMode(2,INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(2)==LOW && pressed==0)
  {
    pressed = 1;
    counter++;
    Serial.println(counter);
  }
  else if(digitalRead(2)==HIGH && pressed==1)   
  {
    pressed = 0;
    delay(200);
  }
}
