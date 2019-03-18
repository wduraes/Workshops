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
 * this piece of code, will publish information to temperature, 
 * humidity, light and email
 * 
 * It will also subscribe only to a feed called email
 * 
 * Every time the feed named email is set to YES, it will change 
 * the Neopixels color to RED and will beep once every 10 seconds
 * 
 * Clicking button 1 will publish a message to the feed named Email
 * a message to set it to NO, and will turn the NeoPixels back to green
 * 
*/
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
  #define WLAN_SSID       "WIFI NAME"
  #define WLAN_PASS       "WIFI PASSWORD"
  #define AIO_SERVER      "io.adafruit.com"
  #define AIO_USERNAME    "YOUR USER NAME"
  #define AIO_KEY         "YOUR ID"
  #define AIO_SERVERPORT  8883     // use 8883 for SSL
  //#define AIO_SERVERPORT  1883                   
  //WiFiClient client;
  WiFiClientSecure client;  // use WiFiFlientSecure for SSL

  Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
  
  Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
  Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature");
  Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");
  Adafruit_MQTT_Publish light= Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/light");
  Adafruit_MQTT_Publish send_email= Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/email");
  Adafruit_MQTT_Subscribe read_email = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/email");

  void MQTT_connect();
  bool unread_email = false;
   
  void setup() {
    
    pinMode(5,INPUT);
    attachInterrupt(digitalPinToInterrupt(5),MyInterruptHandler,RISING);
    
    Serial.begin(115200);
    delay(10); 
    pinMode(A0, INPUT); //LDR
    pinMode(5, INPUT); //Key 2
    pinMode(16, INPUT); //Key 1 
  
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
      tone(14, 1000);
      delay(200);
      tone(14, 800);
      delay(200);
      noTone(14);
  
    // Setup MQTT subscriptions for all feeds.
    mqtt.subscribe(&read_email);
        
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
      
     //inside this while loop we'll check if there is any news to feeds we subscribe to
     //limited to 5 subscriptions by default
      
      if (strcmp((char *)read_email.lastread, "YES") == 0) 
      {
          unread_email = true;
          pixels.setPixelColor(0,255,0,0);
          pixels.setPixelColor(1,255,0,0);
          pixels.setPixelColor(2,255,0,0);
          pixels.show();
      }
      if (strcmp((char *)read_email.lastread, "NO") == 0) 
      {
          unread_email = false;
          pixels.setPixelColor(0,0,255,0);
          pixels.setPixelColor(1,0,255,0);
          pixels.setPixelColor(2,0,255,0);
          pixels.show();          
      }
    }
     
    // Now we can publish stuff!
  
    float Light = analogRead(A0);

    Serial.print(F("\nSending light val "));
    Serial.print(Light);
    Serial.print("...");
    if (! light.publish(Light)) 
    {
        Serial.println(F("Failed"));
    } 
    else 
    {
        Serial.println(F("OK!"));
    }
    
    
    dht.temperature().getEvent(&event);   
    //checking for non-number values BEFORE publishing
    Serial.print(F("\nSending temperature val "));
    Serial.print(event.temperature);
    Serial.print("...");
    if(!isnan(event.temperature))
    {
      if (! temperature.publish(event.temperature)) 
      {
          Serial.println(F("Failed"));
      }
      else 
      {
          Serial.println(F("OK!"));
      }
    }
    
    
    dht.humidity().getEvent(&event);
    //checking for non-number values BEFORE publishing
    Serial.print(F("\nSending humidity val "));
    Serial.print(event.relative_humidity);
    Serial.print("...");
    
    if(!isnan(event.relative_humidity))
    {
        if (! humidity.publish(event.relative_humidity)) 
        {
          Serial.println(F("Failed"));
        }
        else 
        {
          Serial.println(F("OK!"));
        }
    }

      if(unread_email)
      {
          tone(14, 1600);
          delay(300);
          noTone(14);
          delay(150);
          tone(14, 1600);
          delay(300);
          noTone(14);   
      }
      else
      {  
        if (! send_email.publish("NO")) 
          {
             Serial.println(F("Failed"));
          }
        else 
          {
             Serial.println(F("OK!"));
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
      tone(14, 1200);
      delay(200);
      noTone(14);
      delay(50);
      tone(14, 1200);
      delay(200);
      noTone(14);
  }

void self_test(){

  pixels.setPixelColor(0,255,0,0);
  pixels.setPixelColor(1,255,0,0);
  pixels.setPixelColor(2,255,0,0);
  pixels.show();
  delay(400);
  pixels.setPixelColor(0,0,0,255);
  pixels.setPixelColor(1,0,0,255);
  pixels.setPixelColor(2,0,0,255);
  pixels.show();
  delay(400);
  pixels.setPixelColor(0,0,255,0);
  pixels.setPixelColor(1,0,255,0);
  pixels.setPixelColor(2,0,255,0);
  pixels.show();
}

  void MyInterruptHandler()
  {
    unread_email = false;
    pixels.setPixelColor(0,0,255,0);
    pixels.setPixelColor(1,0,255,0);
    pixels.setPixelColor(2,0,255,0);
    pixels.show(); 
  }
