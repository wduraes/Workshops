void setup() {
  pinMode(9,OUTPUT);
  digitalWrite(9,HIGH);
  //delay(3000);
  digitalWrite(9,LOW);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(9,HIGH);
  delay(80);
  digitalWrite(9,LOW);
  delay(80);
  Serial.println("jambo123")
}
