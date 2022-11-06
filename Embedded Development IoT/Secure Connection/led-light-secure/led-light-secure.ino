#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define WLAN_SSID       "Wonders"
#define WLAN_PASS       "Jacare24"
#define AIO_SERVER      "io.adafruit.com"
#define AIO_USERNAME    "wduraes"
#define AIO_KEY         "aio_GsRC26WNIkcTxgBTAsmlcjYVDVOw"
#define AIO_SERVERPORT  8883                   
WiFiClientSecure client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Subscribe led = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/led");
Adafruit_MQTT_Publish light= Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/light");

static const char *fingerprint PROGMEM = "18 C0 C2 3D BE DD 81 37 73 40 E7 E4 36 61 CB 0A DF 96 AD 25";
  
void MQTT_connect();

#define ledPin 2
#define ldrPin A0
   
void setup() {
    
  Serial.begin(115200);
    pinMode(ledPin,OUTPUT);
    pinMode(ldrPin,INPUT);
     
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
    client.setFingerprint(fingerprint);
  
    // Setup MQTT subscriptions for all feeds.
    mqtt.subscribe(&led);
  }
     
  void loop() {
  
    MQTT_connect();
   
    Adafruit_MQTT_Subscribe *subscription;
    while ((subscription = mqtt.readSubscription(20000))) 
    {  
     //inside this while loop we'll check if there is any news to feeds we subscribe to
     //limited to 5 subscriptions by default
      
      if (subscription == &led) 
      {
        Serial.print(F("Got: "));
        Serial.println((char *)led.lastread);
      }
  
      if (strcmp((char *)led.lastread, "ON") == 0) 
      {
          digitalWrite(ledPin, 1); 
      }
        
       if (strcmp((char *)led.lastread, "OFF") == 0) 
       {
          digitalWrite(ledPin, 0); 
       }        
    }

    float Light = analogRead(ldrPin);
    if (light.publish(Light)) 
    {
        Serial.print("Sending light val ");
        Serial.print(Light);
        Serial.println("...");
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
