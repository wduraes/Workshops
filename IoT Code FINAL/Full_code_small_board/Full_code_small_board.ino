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
  #include <Adafruit_NeoPixel.h>
  #define PIN            2
  #define NUMPIXELS      3
  #define WLAN_SSID       "xxxx"
  #define WLAN_PASS       "xxxx"
  #define AIO_SERVER      "io.adafruit.com"
  #define AIO_USERNAME    "xxxxx"
  #define AIO_KEY         "xxxx"
  //#define AIO_SERVERPORT  8883     // use 8883 for SSL
  #define AIO_SERVERPORT  1883                   
  WiFiClient client;
  //WiFiClientSecure client;  // use WiFiFlientSecure for SSL

  Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
  
  Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
  Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature");
  Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");
  Adafruit_MQTT_Publish light= Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/light");
  Adafruit_MQTT_Publish relay1 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/relay1");
  Adafruit_MQTT_Subscribe neopixel = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/neopixel");
  Adafruit_MQTT_Subscribe slider = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/slider");

  void MQTT_connect();
   
  void setup() {     
     
    Serial.begin(115200);
    pinMode(A0, INPUT); //LDR
  
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
    //beep indicating Wi-fi is connected successfuly 
      tone(14, 1000);
      delay(200);
      tone(14, 800);
      delay(200);
      noTone(14);
  
    // Setup MQTT subscriptions for all feeds.
    mqtt.subscribe(&neopixel);
    mqtt.subscribe(&slider);
        
    dht.begin();

    pixels.begin();
    pixels.setBrightness(153);
    pixels.show();

    self_test();
  }
     
  void loop() {
  
    MQTT_connect();
    sensors_event_t event;  
   
    Adafruit_MQTT_Subscribe *subscription;
    while ((subscription = mqtt.readSubscription(10000))) 
    {
     //inside this loop we'll check if there is any news to feeds we subscribe to
     //limited to 5 subscriptions by default
               
       if (subscription == &slider) 
       {
          Serial.print(F("Slider: "));
          Serial.println((char *)slider.lastread);
          uint16_t sliderval = atoi((char *)slider.lastread);  // convert to a number
          if(sliderval > 500)
            {
              digitalWrite(5, 1); 
              tone(14, 1000);
            }
          else
            {
              digitalWrite(5, 0); 
              noTone(14);
            }
       }
            
            if (subscription == &neopixel) 
            {
                Serial.print(F("Slider: "));
                Serial.println((char *)neopixel.lastread);
          
                //convet Hex to RGB
                String hexstring = ((char *)neopixel.lastread);
                long number = (long) strtol( &hexstring[1], NULL, 16);
                int r = number >> 16;
                int g = number >> 8 & 0xFF;
                int b = number & 0xFF;
          
                Serial.print("R: ");
                Serial.print(r);
                Serial.print(" G: ");
                Serial.print(g);
                Serial.print(" B: ");
                Serial.println(b);
          
                pixels.setPixelColor(0,r,g,b);
                pixels.setPixelColor(1,r,g,b);
                pixels.setPixelColor(2,r,g,b);
                pixels.show();
            }
    }    
  
    float Light = analogRead(A0);
    if (light.publish(Light)) 
    {
        Serial.print("Sending light val ");
        Serial.print(Light);
        Serial.println("...");
    }
    
    dht.temperature().getEvent(&event); 
    //checking for non-number values BEFORE publishing 
    if(!isnan(event.temperature))
    {
      if (temperature.publish(event.temperature)) 
      {
          Serial.print("Sending temperature val ");
          Serial.print(event.temperature);
          Serial.println("...");
      }
    }
    
    dht.humidity().getEvent(&event);
    //checking for non-number values BEFORE publishing
    if(!isnan(event.relative_humidity))
    {
        if (humidity.publish(event.relative_humidity)) 
        {
          Serial.print("Sending humidity val ");
          Serial.print(event.relative_humidity);
          Serial.println("...");
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
    //tone indicating MQTT connection happened
      tone(14, 1200);
      delay(200);
      noTone(14);
      delay(50);
      tone(14, 1200);
      delay(200);
      noTone(14);
  }

void self_test(){

  //blinking Neopixels as partof the board initialization
  pixels.setPixelColor(0,255,0,0);
  pixels.setPixelColor(1,255,0,0);
  pixels.setPixelColor(2,255,0,0);
  pixels.show();
  delay(400);
  pixels.setPixelColor(0,0,255,0);
  pixels.setPixelColor(1,0,255,0);
  pixels.setPixelColor(2,0,255,0);
  pixels.show();
  delay(400);
  pixels.setPixelColor(0,0,0,255);
  pixels.setPixelColor(1,0,0,255);
  pixels.setPixelColor(2,0,0,255);
  pixels.show();
  delay(400);
  pixels.setPixelColor(0,0,0,0);
  pixels.setPixelColor(1,0,0,0);
  pixels.setPixelColor(2,0,0,0);
  pixels.show();
}