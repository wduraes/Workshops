/*
 * this code retrieves the MAC Address of your ESP board and  
 * publishes it to the Serial Monitor
 * Load this sketch and open the Serial Monitor
*/

#include <ESP8266WiFi.h>

uint8_t MAC_array[6];
char MAC_char[18];

void setup() {
    Serial.begin(115200);
    Serial.println();

    WiFi.macAddress(MAC_array);
    for (int i = 0; i < sizeof(MAC_array); ++i){
      sprintf(MAC_char,"%s%02x:",MAC_char,MAC_array[i]);
    }
  
    Serial.println(MAC_char);
}

void loop() {
  
}


//http://openwifi
//Add your MAC Address to get access to open wifi @ Microsoft
