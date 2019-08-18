int counter = 0;
bool pressed = 0;

void setup() {
  pinMode(2,INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(2)==LOW && pressed==0)
  {
    counter++;
    Serial.println(counter);
    pressed = 1;
  }
  else if(pressed==1)   
  {
    pressed = 0;
    delay(200);
  }
}
