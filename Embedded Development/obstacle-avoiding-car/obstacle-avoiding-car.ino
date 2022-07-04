const int pingPin1 = A4; // Trigger Pin of Ultrasonic Sensor 1
const int echoPin1 = A5; // Echo Pin of Ultrasonic Sensor 1
const int pingPin2 = 4; // Trigger Pin of Ultrasonic Sensor 2
const int echoPin2 = 2; // Echo Pin of Ultrasonic Sensor 2

bool starting = 1;
int maxSpeed = 160;  //160 is the minimum to get the car to move on solid surfaces. Carpet will require more.

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

void ahead()
{
    if(starting)
    {
      for(int i=140;i<maxSpeed;i++) //smooth acceleration
      {
        analogWrite(5,i);
        analogWrite(9,i);
        delay(10);  //determine how long will take until full speed, then maintain speed
      }
      analogWrite(5,maxSpeed);
      analogWrite(9,maxSpeed); 
      starting = false; 
    }
    else{
      analogWrite(5,maxSpeed);
      analogWrite(9,maxSpeed);  
    }
    
}
void obstacle()
{
    analogWrite(5,0); //full stop
    analogWrite(9,0);
    starting = true;
    delay(3000);
}

void back()
{
    for(int i=140;i<257;i++) //smooth acceleration
    {
      analogWrite(3,i);
      analogWrite(6,i);
      delay(10); //determine how much will back up
    } 
    analogWrite(3,0); //full stop
    analogWrite(6,0);  
    delay(500); 
}
void steer()
{
    for(int i=140;i<200;i++) //smooth acceleration
    {
      analogWrite(6,i);
      delay(20);  //determine how much will go turning
    }
    analogWrite(6,0); //full stop
    delay(2000);
}

void setup() {
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(pingPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(pingPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

}

void loop() {

  long duration1, inches1, cm1;
  digitalWrite(pingPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin1, LOW);
   
  duration1 = pulseIn(echoPin1, HIGH);
  //inches1 = microsecondsToInches(duration1);
  cm1 = microsecondsToCentimeters(duration1);

  long duration2, inches2, cm2;
  digitalWrite(pingPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin2, LOW);
   
  duration2 = pulseIn(echoPin2, HIGH);
  //inches2 = microsecondsToInches(duration2);
  cm2 = microsecondsToCentimeters(duration2);

  if(cm1>20 && cm2<5)
  {
    Serial.println("ahead");
    ahead();
  }
  else if(cm1<20 && cm2<5)
  {
    Serial.println("obstacle ahead");
    obstacle();
    Serial.println("steering");
    steer();
  }
  
  if(cm2>5)
  {
    Serial.println("border below");
    obstacle();
    Serial.println("backing");
    back();
    Serial.println("steering");
    steer();
  }

}

void test()
{

  long duration1, inches1, cm1;
  digitalWrite(pingPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin1, LOW);
   
  duration1 = pulseIn(echoPin1, HIGH);
  //inches1 = microsecondsToInches(duration1);
  cm1 = microsecondsToCentimeters(duration1);

  long duration2, inches2, cm2;
  digitalWrite(pingPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin2, LOW);
   
  duration2 = pulseIn(echoPin2, HIGH);
  //inches2 = microsecondsToInches(duration2);
  cm2 = microsecondsToCentimeters(duration2);

  if(cm1>20 && cm2<5)
  {
    Serial.println("ahead");
    ahead();
  }
  else if(cm1<20 && cm2<5)
  {
    Serial.println("obstacle ahead");
    obstacle();
    Serial.println("steering");
    steer();
  }
  
  if(cm2>5)
  {
    Serial.println("border below");
    obstacle();
    Serial.println("backing");
    back();
    Serial.println("steering");
    steer();
  }



   
}

void distanceTest()
{


  long duration1, inches1, cm1;
  digitalWrite(pingPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin1, LOW);
   
  duration1 = pulseIn(echoPin1, HIGH);
  //inches1 = microsecondsToInches(duration1);
  cm1 = microsecondsToCentimeters(duration1);

  long duration2, inches2, cm2;
  digitalWrite(pingPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin2, LOW);
   
  duration2 = pulseIn(echoPin2, HIGH);
  //inches2 = microsecondsToInches(duration2);
  cm2 = microsecondsToCentimeters(duration2);

  Serial.print("Front: ");
  Serial.print(cm1);
  Serial.print("  Down: ");
  Serial.println(cm2);



  
}
