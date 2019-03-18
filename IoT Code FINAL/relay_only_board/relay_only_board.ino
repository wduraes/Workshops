/***************************************************
 Based in the great Adafruit MQTT Library ESP8266 Example

  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino

  Works great with Adafruit's Huzzah ESP board & Feather
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/products/2821

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
/*
  This sample code connects to 1 feed, subscbribed to Relay1: 
      Turns pin 12 ON/OFF - where we have a relay connected
  There is no publishing in this code
*/  
  #include <ESP8266WiFi.h>
  #include "Adafruit_MQTT.h"
  #include "Adafruit_MQTT_Client.h"
  #include "SPI.h"
  #define WLAN_SSID       "WIFI NAME"
  #define WLAN_PASS       "WIFI PASSWORD"
  #define AIO_SERVER      "io.adafruit.com"
  #define AIO_USERNAME    "YOUR USER NAME"
  #define AIO_KEY         "YOUR ID"
  #define AIO_SERVERPORT  8883     // use 8883 for SSL
  WiFiClientSecure client;  // use WiFiFlientSecure for SSL
  //#define AIO_SERVERPORT  1883                   
  //WiFiClient client;
    
  
  Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
  Adafruit_MQTT_Subscribe relay4 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/relay_natal");
  
  void MQTT_connect();
   
  void setup() {
    Serial.begin(115200);
    delay(10); 
    pinMode(12,OUTPUT);
     
    // Connect to WiFi access point.
    Serial.println(); Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WLAN_SSID);
  
    WiFi.begin(WLAN_SSID, WLAN_PASS);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
      }
    Serial.println();
    Serial.println("WiFi connected");
    Serial.println("IP address: "); Serial.println(WiFi.localIP());
  
    // Setup MQTT subscriptions for all feeds.
    mqtt.subscribe(&relay4);
  }
     
  void loop() {
  
    MQTT_connect();
   
    Adafruit_MQTT_Subscribe *subscription;
    while ((subscription = mqtt.readSubscription(20000))) 
    {  
     //inside this while loop we'll check if there is any news to feeds we subscribe to
     //limited to 5 subscriptions by default
      
      if (subscription == &relay4) 
      {
        Serial.print(F("Got: "));
        Serial.println((char *)relay4.lastread);
      }
  
      if (strcmp((char *)relay4.lastread, "ON") == 0) 
      {
          digitalWrite(12, 1); 
      }
        
       if (strcmp((char *)relay4.lastread, "OFF") == 0) 
       {
          digitalWrite(12, 0); 
       }        
    }
}

  // Function to connect and reconnect as necessary to the MQTT server.
  // Should be called in the loop function and it will take care if connecting.
  void MQTT_connect() {
    
    int8_t ret;
    if (mqtt.connected()) {      // Stop if already connected.
      return;
      }
    Serial.print("Connecting to MQTT... ");
    uint8_t retries = 3;
    while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
         Serial.println(mqtt.connectErrorString(ret));
         Serial.println("Retrying MQTT connection in 5 seconds...");
         mqtt.disconnect();
         delay(5000);  // wait 5 seconds
         retries--;
         if (retries == 0) {
           // basically die and wait for WDT to reset me
           while (1);
         }
    }
    Serial.println("MQTT Connected!");
  }
