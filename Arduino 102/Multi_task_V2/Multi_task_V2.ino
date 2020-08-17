#define INTERVAL_MESSAGE1 40
#define INTERVAL_MESSAGE2 70
#define INTERVAL_MESSAGE3 310
#define INTERVAL_MESSAGE4 500
#define INTERVAL_MESSAGE5 1350
#define INTERVAL_MESSAGE6 1000
 
unsigned long time_1 = 0;
unsigned long time_2 = 0;
unsigned long time_3 = 0;
unsigned long time_4 = 0;
unsigned long time_5 = 0;
unsigned long time_6 = 0;

bool state1 = 0;
bool state2 = 0;
bool state3 = 0;
bool state4 = 0;
bool state5 = 0;
bool state6 = 0;
 
void setup() 
{
    pinMode(13,OUTPUT);
    pinMode(12,OUTPUT);
    pinMode(11,OUTPUT);
    pinMode(10,OUTPUT);
    pinMode(9,OUTPUT);
    pinMode(8,OUTPUT);
}
 
void loop() 
{
    //control timer for process 1, which will be activated every 40ms
    if(millis() > time_1 + INTERVAL_MESSAGE1){
        time_1 = millis();
          //here is your code 
          state1 = not(state1);
          digitalWrite(13,state1);
    }
   
    //control timer for process 2, which will be activated every 70ms
    if(millis() > time_2 + INTERVAL_MESSAGE2){
        time_2 = millis();
          //here is your code 
          state2 = not(state2);
          digitalWrite(12,state2);
    }
   
    if(millis() > time_3 + INTERVAL_MESSAGE3){
        time_3 = millis();
          //here is your code 
          state3 = not(state3);
          digitalWrite(11,state3);
    }
   
    if(millis() > time_4 + INTERVAL_MESSAGE4){
        time_4 = millis();
          //here is your code 
          state4 = not(state4);
          digitalWrite(10,state4);
    }
        if(millis() > time_5 + INTERVAL_MESSAGE5){
        time_5 = millis();
          //here is your code 
          state5 = not(state5);
          digitalWrite(9,state5);
    }
   
    if(millis() > time_6 + INTERVAL_MESSAGE6){
        time_6 = millis();
          //here is your code 
          state6 = not(state6);
          digitalWrite(8,state6);
    }
}
