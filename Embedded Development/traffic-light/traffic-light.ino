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

void loop() {

  if(digitalRead(PEDBUTTON)==HIGH)
  {
    ped = true;
    tone(8,1000,100);
  }

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
  else
  {
    RedForPed();
    GreenToCars();
  }
}
  

void GreenToCars(){
    digitalWrite(CARRED,LOW);
    digitalWrite(CARGREEN,HIGH);
}

void YellowToCars(){
    digitalWrite(CARGREEN,LOW);
    digitalWrite(CARYELLOW,HIGH);
    delay(2000);
}

void RedToCars(){
    digitalWrite(CARRED,HIGH);
    digitalWrite(CARYELLOW,LOW);
}

void GreenForPed(){
    digitalWrite(PEDGREEN,HIGH);
    digitalWrite(PEDRED,LOW);
    for(int i=0;i<6;i++)
    {
      tone(8,400,100);
      delay(400);
    }
}

void RedForPed(){
    digitalWrite(PEDGREEN,LOW);
    digitalWrite(PEDRED,HIGH);
}

void BlinkForPed(){
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
