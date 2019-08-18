int period = 1000;
unsigned long time_now = 0;
 
void setup() {
    Serial.begin(9600);
}
 
void loop() {
    if(millis() > time_now + period){
        time_now = millis();
        Serial.print("Hello, the time is: ");
        Serial.print(millis()/1000);
        Serial.println(" sec");
    }
   
    //Run other code
}
