#define CARGREEN   4 
#define CARRED     2
#define CARYELLOW  3
#define PEDGREEN   6
#define PEDRED     5
#define PEDBUTTON  7
#define BUZZER      8
#define YELLOWTORED   1000
#define REDTOBLINK    2000
#define BLINKTOGREEN  2000
#define GREENFORCARS  3000

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
    //state machine
    YellowToCars();
    delay(2000);
    RedToCars();
    GreenForPed();
    //delay(3000);
    BlinkForPed();
    delay(500);
    ped = false;
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
}
