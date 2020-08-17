#define INTERVAL_MESSAGE1 1000
 
unsigned long time_1 = 0;
bool state1 = 0;

void setup() 
{
    pinMode(6,OUTPUT);
}
 
void loop() 
{
    //control timer for process 1, which will be activated every second
    if(millis() > time_1 + INTERVAL_MESSAGE1)
    {
        time_1 = millis();
          //here is your code 
          state1 = not(state1);
          digitalWrite(6,state1);
    }
}
   
