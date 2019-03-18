void setup() {
  pinMode(9,OUTPUT);
  digitalWrite(9,HIGH);
  //Turn the led on for 3 seconds for RESET testing
  delay(3000);
  digitalWrite(9,LOW);
  //Turn Serial on so we can see the TX led blinking as well
  Serial.begin(9600);
}

void loop() {
  digitalWrite(9,HIGH);
  delay(80);
  digitalWrite(9,LOW);
  delay(80);
  Serial.println("jambo123")
}
