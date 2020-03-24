const int sensorPin = 0;
const int ledPin = 9;

int lightVal;
int i;


void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}


void loop()
{
  lightVal = analogRead(sensorPin);
  Serial.print("Sensor: ");
  Serial.println(lightVal);

  //map(value, fromLow, fromHigh, toLow, toHigh)
  i = map(lightVal, 0, 500, 0, 255); 
  
  Serial.print("Output: ");
  Serial.println(i);
  analogWrite(9, i);

  delay(100);
}
