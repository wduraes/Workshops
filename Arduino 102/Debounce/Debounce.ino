int counter = 0;

void setup() {
  pinMode(2,INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(2)==LOW)
  {
    counter++;
    Serial.println(counter);
  }
}
