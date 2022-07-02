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

unsigned long yellow = 0;
unsigned long red = 0;
unsigned long blinking = 0;
unsigned long green = 0;

bool ped = 0;
bool RED = 0;
bool YELLOW = 0;

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
      if(millis() > green + GREENFORCARS){             
        ped = 1;
      }
    }

  if(YELLOW)
    {
      ped = 0;
      digitalWrite(CARYELLOW,HIGH);
           
      if(millis() > yellow + YELLOWTORED){             
        digitalWrite(CARYELLOW,LOW);
        YELLOW = 0;
        RED = 1;
      }
    }

  if(ped){
    digitalWrite(CARGREEN,LOW);
    yellow = millis();
    YELLOW = 1;
    /*
    digitalWrite(CARYELLOW,LOW);  
    digitalWrite(CARRED,HIGH);
    digitalWrite(PEDGREEN,HIGH);  
    digitalWrite(PEDRED,LOW); 
    delay(2000);
    digitalWrite(CARRED,LOW); 
    digitalWrite(PEDGREEN,LOW);  
    ped = 0; 
    */
    green = millis();
  }
  else
  {
    //digitalWrite(CARGREEN,HIGH);
    //digitalWrite(PEDRED,HIGH);
  }

}


/*
    //control timer for process 1, which will be activated every 40ms
    if(millis() > time_1 + INTERVAL_MESSAGE1){
        time_1 = millis();
          //here is your code 
          state1 = not(state1);
          digitalWrite(13,state1);
    }
*/
