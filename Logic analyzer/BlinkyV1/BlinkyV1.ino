void setup() {
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
}

void loop() {
  digitalWrite(8,1);
  digitalWrite(9,1);
  digitalWrite(10,1);

  digitalWrite(8,0);
  digitalWrite(9,0);
  digitalWrite(10,0);
}
