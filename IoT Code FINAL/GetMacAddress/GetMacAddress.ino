/*
 * this code retrieves the MAC Address of your ESP board and  
 * publishes it to the Serial Monitor
 * Load this sketch and open the Serial Monitor
*/

#include <ESP8266WiFi.h>
 
void setup(){ 
   Serial.begin(115200);
   delay(500); 
}
 
void loop(){ 
  Serial.println();
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
  delay(2000);
}


//http://openwifi
//Add your MAC Address to get access to open wifi
