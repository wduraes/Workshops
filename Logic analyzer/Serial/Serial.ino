void setup() {
  Serial.begin(9600);
}
void loop() {
  Serial.println("abc");
  delay(10);
  Serial.println("ABC");
  delay(10);
  Serial.println("a b c");
  delay(10);
  Serial.print("a");
  Serial.print("b");
  Serial.println("c");
  delay(100);
}
