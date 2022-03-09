const int sensorPin = 0;
const int ledPin = 9;

int lightVal;
int mappedLight;

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

  //Function Map transforms the input range to another range specified in the function call
  //map(value, fromLow, fromHigh, toLow, toHigh)
  mappedLight = map(lightVal, 0, 500, 0, 255); 
  
  Serial.print("Output: ");
  Serial.println(mappedLight);
  analogWrite(9, mappedLight);

  delay(100);
}
