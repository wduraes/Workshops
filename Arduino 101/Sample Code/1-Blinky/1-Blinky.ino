/*
This sample code blinks an LED connected to pin 13  
*/

////code within setup will be executed once at powering or resetting the board
void setup() 
{
pinMode(13, OUTPUT); //set 13 as an output pin
}

//code that runs on an infinite loop
void loop() 
{
digitalWrite(13, HIGH); //set pin 13 at a high logic level
delay(1000);            //add a 1 second delay
digitalWrite(13, LOW);  //set pin 13 at a low logic level
delay(1000);            //add a 1 second delay
}
