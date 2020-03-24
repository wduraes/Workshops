const int sensorPin = 0;
const int ledPin = 9;

int lightVal;

void setup()
{
  // LED pin to be an output.
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  lightVal = analogRead(sensorPin);

  Serial.print("Sensor: ");
  Serial.println(lightVal);

  if (lightVal < 20)
    {
      digitalWrite(9, HIGH);
    }
  else
    {
      digitalWrite(9, LOW);
    }
  delay(1000);
}
