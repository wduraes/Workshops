/*
  This sample code connects to 1 feed.
    Publishing to IoT_Button: 
      Button publishes a message "1" we don't really care about the message published. IFTTT service catches new pubishing regadless of the value
    This code does nothing but publishing stuff, so it can do that REAL fast.
    We have a limitation in the MQTT Broker, so we NEED to debounce the buttons.
      2 variables help maintaing a good debouncing so only one message is sent per button press. 
*/
  #include <ESP8266WiFi.h>
  #include "Adafruit_MQTT.h"
  #include "Adafruit_MQTT_Client.h"
  #include "SPI.h"
  #define WLAN_SSID       "Your Wifi name"
  #define WLAN_PASS       "Your wifi password"
  #define AIO_SERVER      "io.adafruit.com"
  #define AIO_USERNAME    "Your Adafruit account name"
  #define AIO_KEY         "Your Adafruit key"
  #define AIO_SERVERPORT  1883                   
  WiFiClient client;
  
  Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
  Adafruit_MQTT_Publish relay1 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/IoT_Button");
  
  void MQTT_connect();
  
  bool btn1Pressed = 0;
   
  void setup() {
    Serial.begin(115200);
    delay(10); 
    pinMode(5, INPUT_PULLUP); // Button 1
  
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
  }
     
  void loop() {
    
    MQTT_connect();
    
    if(digitalRead(5)==LOW && btn1Pressed ==0) {
          Serial.println(Button-pressed");
          if (relay1.publish("ON")) {
              Serial.println(F("OK!"));
            }
          btn1Pressed=1; 
    }
    else if(digitalRead(5)==HIGH && btn1Pressed==1) {
        btn1Pressed=0; 
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
