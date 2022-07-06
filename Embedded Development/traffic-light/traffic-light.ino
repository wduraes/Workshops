#define CARGREEN   4 
#define CARRED     2
#define CARYELLOW  3
#define PEDGREEN   6
#define PEDRED     5
#define PEDBUTTON  7
#define BUZZER     8

#define INTERVAL_MESSAGE1 5000
unsigned long time_1 = 0;
bool state1 = 0;

bool ped = false;

void setup() {
  pinMode(CARGREEN,OUTPUT);
  pinMode(CARRED,OUTPUT);
  pinMode(CARYELLOW,OUTPUT);
  pinMode(PEDGREEN,OUTPUT);
  pinMode(PEDRED,OUTPUT);
  pinMode(BUZZER,OUTPUT);
  pinMode(PEDBUTTON,INPUT);
}

void GreenToCars(){
    //turn Red light off and green light on
    digitalWrite(CARRED,LOW);
    digitalWrite(CARGREEN,HIGH);
}

void YellowToCars(){
    //turn green light off and yellow light on. Waits for 2 seconds on that state
    digitalWrite(CARGREEN,LOW);
    digitalWrite(CARYELLOW,HIGH);
    delay(2000);
}

void RedToCars(){
    //turn red light on and yellow light off
    digitalWrite(CARRED,HIGH);
    digitalWrite(CARYELLOW,LOW);
}

void GreenForPed(){
    //turn green light for pedestrians on and the red light off 
    // it also beeps for 3 seconds to let pedestrians know it is safe to cross
    digitalWrite(PEDGREEN,HIGH);
    digitalWrite(PEDRED,LOW);
    for(int i=0;i<6;i++)
    {
      tone(8,400,100);
      delay(400);
    }
}

void RedForPed(){
  //turn red light for pedestrians on and the green light off 
  digitalWrite(PEDGREEN,LOW);
  digitalWrite(PEDRED,HIGH);
}

void BlinkForPed(){
  //turn green light for pedestrians off 
  // and blinks the red light for 2 seconds
  //then waits for additional 1/2 second before opening to cars for safety  
  digitalWrite(PEDGREEN,LOW);    
  for(int i=0;i<6;i++)
  {
    digitalWrite(PEDRED,LOW);
    delay(200);
    digitalWrite(PEDRED,HIGH);
    delay(200);
  }
  delay(500);
}

void loop() {

  //checks for pedestrian button pressed
  if(digitalRead(PEDBUTTON)==HIGH)
  {
    ped = true;
    tone(8,1000,100);
  }

  //if ped button has been pressed, checks to see if the minimum interval for cars has been achieved
  if(ped)
  {  
    if(millis() > time_1 + INTERVAL_MESSAGE1){
      //state machine
      YellowToCars();
      RedToCars();
      GreenForPed();
      BlinkForPed();
      ped = false;
      time_1 = millis();
    }
  }
  //if the button is not pressed, it will be always green for cars and red for peds. 
  else
  {
    RedForPed();
    GreenToCars();
  }
}
  
