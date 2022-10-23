#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

#define AIO_SERVER      "io.adafruit.com"
#define AIO_USERNAME    "Username"
#define AIO_KEY         "KEY"
#define AIO_SERVERPORT  1883                   
WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Subscribe relay = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/relay");
  
void MQTT_connect();

#define relayPin 4
#define ledPin 5
   
void setup() {
    
  Serial.begin(115200);
  WiFiManager wm;
  bool res;

    res = wm.autoConnect("ESP8266 SSID","password"); // password protected ap

    if(!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("WiFi connected");
        Serial.println("IP address: "); 
        Serial.println(WiFi.localIP());
    }

    pinMode(relayPin,OUTPUT);
    pinMode(ledPin,OUTPUT);
     
    // Setup MQTT subscriptions for all feeds.
    mqtt.subscribe(&relay);
  }
     
  void loop() {
  
    MQTT_connect();

    digitalWrite(ledPin,HIGH);
    delay(200);
    digitalWrite(ledPin,LOW);
    delay(200);
   
    Adafruit_MQTT_Subscribe *subscription;
    while ((subscription = mqtt.readSubscription(20000))) 
    {  
     //inside this while loop we'll check if there is any news to feeds we subscribe to
     //limited to 5 subscriptions by default
      
      if (subscription == &relay) 
      {
        Serial.print(F("Got: "));
        Serial.println((char *)relay.lastread);
      }
  
      if (strcmp((char *)relay.lastread, "ON") == 0) 
      {
          digitalWrite(relayPin, 1); 
      }
        
       if (strcmp((char *)relay.lastread, "OFF") == 0) 
       {
          digitalWrite(relayPin, 0); 
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
