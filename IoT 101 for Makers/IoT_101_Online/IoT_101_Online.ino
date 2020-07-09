  #include <ESP8266WiFi.h>
  #include "Adafruit_MQTT.h"
  #include "Adafruit_MQTT_Client.h"
  #include <Adafruit_Sensor.h>
  #include <DHT.h>
  #include <DHT_U.h>
  #include "SPI.h"
  #define DHTPIN 10     // what pin we're connected to on the temperature sensor
    #define DHTTYPE DHT11
  DHT_Unified dht(DHTPIN, DHTTYPE);
  #define WLAN_SSID       "Your_Wifi_name"
  #define WLAN_PASS       "Your_wifi_password"
  #define AIO_SERVER      "io.adafruit.com"
  #define AIO_USERNAME    "Your_Adafruit_account_name"
  #define AIO_KEY         "Your_Adafruit_key"
  #define AIO_SERVERPORT  1883                   
  WiFiClient client;
  //#define AIO_SERVERPORT  8883     // use 8883 for SSL
  //WiFiClientSecure client;  // use WiFiFlientSecure for SSL

  Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
  Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature");
  Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");
  Adafruit_MQTT_Subscribe led = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/led");
  
  void MQTT_connect();
   
  void setup() 
  {       
    Serial.begin(115200);
    pinMode(16,OUTPUT);
  
    // Connect to WiFi access point.
    Serial.println(); Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WLAN_SSID);
  
    WiFi.begin(WLAN_SSID, WLAN_PASS);
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
    Serial.println();
    Serial.println("WiFi connected");
    Serial.println("IP address: "); Serial.println(WiFi.localIP());
    
    // Setup MQTT subscriptions for all feeds.
    mqtt.subscribe(&led);
            
    dht.begin();
  }
     
  void loop() 
  {
    MQTT_connect();
    sensors_event_t event;  
   
    Adafruit_MQTT_Subscribe *subscription;
    while ((subscription = mqtt.readSubscription(5000))) 
    {
     //inside this loop we'll check if there is any news to feeds we subscribe to
     //limited to 5 subscriptions by default
      if (subscription == &led) 
      {
        Serial.print(F("Got: "));
        Serial.println((char *)led.lastread);
      }
      if (strcmp((char *)led.lastread, "ON") == 0) 
      {
        digitalWrite(16, 1); 
      } 
      if (strcmp((char *)led.lastread, "OFF") == 0) 
      {
        digitalWrite(16, 0); 
      }        
    }           
   
    dht.temperature().getEvent(&event); 
    //checking for non-number values BEFORE publishing 
    if(isnan(event.temperature))
    {
      Serial.print("Last temperature value is not a number and it won't be published.");
    }
    else
    {
      if (temperature.publish(event.temperature)) 
      {
        Serial.print("Sending temperature val ");
        Serial.print(event.temperature);  
      }
    }
    
    dht.humidity().getEvent(&event);
    //checking for non-number values BEFORE publishing
    if(isnan(event.relative_humidity))
    {
      Serial.print("Last humidity value is not a number and it won't be published.");
    }
    else
    {
      if (humidity.publish(event.relative_humidity)) 
      {
        Serial.print("Sending humidity val ");
        Serial.print(event.relative_humidity);
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