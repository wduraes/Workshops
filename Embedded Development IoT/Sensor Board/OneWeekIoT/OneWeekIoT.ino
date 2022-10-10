#include <Wire.h>
#include "SparkFunBME280.h"
BME280 mySensor;
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

//#define WLAN_SSID       "PUSD-Guests"
//#define WLAN_PASS       "Safe&Secure22"
#define AIO_SERVER      "io.adafruit.com"
#define AIO_USERNAME  "wduraes"
#define AIO_KEY       "aio_ShSn6884cp8nEqUCyuUFVtbCgEfM"

#define AIO_SERVERPORT  1883                   
WiFiClient client;
//#define AIO_SERVERPORT  8883     // use 8883 for SSL
//WiFiClientSecure client;  // use WiFiFlientSecure for SSL

#define PIN 2        //pin connected to the NeoPixels
#define NUMPIXELS 3  //how many NeoPixels we have

#define BUZZER 14    //pin connected to the buzzer
#define LIGHT A0     //pin connected to the light sensor
#define LED1 12      //pin connected to LED 1
#define LED2 13      //pin connected to LED 2
#define intPin 15    //pin connected to the Button

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature");
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");
Adafruit_MQTT_Publish light= Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/light");
Adafruit_MQTT_Publish altitude= Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/altitude");
Adafruit_MQTT_Publish pressure= Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/pressure");
Adafruit_MQTT_Publish dispense= Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/dispense");
Adafruit_MQTT_Subscribe neopixel = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/neopixel");
Adafruit_MQTT_Subscribe slider = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/slider");
Adafruit_MQTT_Subscribe led1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/led1");
Adafruit_MQTT_Subscribe led2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/led2");

void ICACHE_RAM_ATTR ButtonPress()
{
  //DO something;
  dispense.publish("1");
}

void setup() 
{
  Serial.begin(115200);
  WiFiManager wm;
  bool res;

    res = wm.autoConnect("IoT-Door-Lock","password"); // password protected ap

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


  /*/ Connect to WiFi access point.
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
  */


    
    //beep indicating Wi-fi is connected successfuly 
      tone(14, 1000);
      delay(200);
      tone(14, 800);
      delay(200);
      noTone(14);
  
    // Setup MQTT subscriptions for all feeds.
    mqtt.subscribe(&neopixel);
    mqtt.subscribe(&slider);
    mqtt.subscribe(&led1);
    mqtt.subscribe(&led2);
  
  pixels.begin(); 

  pixels.setPixelColor(0, 0, 0, 0); //set the 1st neoPixel off
  pixels.setPixelColor(1, 0, 0, 0); //set the 2nd neoPixel off
  pixels.setPixelColor(2, 0, 0, 0); //set the 3rd neoPixel off
  pixels.show(); 

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  
  Wire.begin();
  mySensor.setI2CAddress(0x76);
  if (mySensor.beginI2C() == false) //Begin communication over I2C
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    while(1); //Freeze
  }

    //interrupt to be triggered when the button is pressed
  attachInterrupt(digitalPinToInterrupt(intPin),ButtonPress,RISING);  
}

void loop() {
  
    MQTT_connect();
   
    Adafruit_MQTT_Subscribe *subscription;
    while ((subscription = mqtt.readSubscription(15000))) 
    {
     //inside this loop we'll check if there is any news to feeds we subscribe to
     //limited to 5 subscriptions by default

    if (subscription == &led1) 
       {
          Serial.print(F("Led: "));
          Serial.println((char *)led1.lastread);
          uint16_t led1_read = atoi((char *)led1.lastread);  // convert to a number
          if(led1_read == 1)
            {
              digitalWrite(LED1, 1); 
            }
          else
            {
              digitalWrite(LED1, 0); 
            }
       }

    if (subscription == &led2) 
       {
          Serial.print(F("Led2: "));
          Serial.println((char *)led2.lastread);
          uint16_t led2_read = atoi((char *)led2.lastread);  // convert to a number
          if(led2_read == 1)
            {
              digitalWrite(LED2, 1); 
            }
          else
            {
              digitalWrite(LED2, 0); 
            }
       }

               
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
    
    if (temperature.publish(mySensor.readTempC())) 
      {
          Serial.print("Sending temperature val ");
          Serial.print(mySensor.readTempC(), 2);
          Serial.println("...");
      }
    
    if (humidity.publish(mySensor.readFloatHumidity())) 
        {
          Serial.print("Sending humidity val ");
          Serial.print(mySensor.readFloatHumidity(),2);
          Serial.println("...");
        }  


    if (pressure.publish(mySensor.readFloatPressure())) 
      {
          Serial.print("Sending pressure val ");
          Serial.print(mySensor.readFloatPressure(), 0);
          Serial.println("...");
      }
    
    if (altitude.publish(mySensor.readFloatAltitudeMeters())) 
        {
          Serial.print("Sending altitude val ");
          Serial.print(mySensor.readFloatAltitudeMeters(), 1);
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
    //tone indicating MQTT connection happened
      tone(14, 1200);
      delay(200);
      noTone(14);
      delay(50);
      tone(14, 1200);
      delay(200);
      noTone(14);
  }
