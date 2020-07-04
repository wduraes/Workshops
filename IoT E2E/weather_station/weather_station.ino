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

#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <SPI.h>

#define DHTPIN 10     // Pin connected to the temperature sensor
#define DHTTYPE DHT11 // Sensor Type
DHT_Unified dht(DHTPIN, DHTTYPE);

#define WLAN_SSID "Wonders"
#define WLAN_PASS "Jacare24"
#define AIO_SERVER "13.66.201.126"
#define AIO_USERNAME ""
#define AIO_KEY ""
#define AIO_SERVERPORT  1883

WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish WEATHER = Adafruit_MQTT_Publish(&mqtt,"WEATHER");

int ChipID = ESP.getChipId(); 

//variables to hold data 
char hum[5];
char temp[5];
char payload[51];

void setup()
{
  Serial.begin(115200);
  delay(10);

  pinMode(16,OUTPUT);
  
  // Connect to WiFi access point.
  Serial.println();
  Serial.println();
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
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  dht.begin();
}

void loop()
{
  MQTT_connect();
  sensors_event_t event;

  //create the Payload by combining all sensor data
  String Payload = "ID=";

  dht.temperature().getEvent(&event);
  float nn = event.temperature;
  dtostrf(nn, 2, 2, temp);

    Payload = Payload + ChipID + ";LOC=1;TEMP=" + temp + ";HUM=";

    dht.humidity().getEvent(&event);
    float no = event.relative_humidity;
    dtostrf(no, 2, 2, hum);

    Payload = Payload + hum;
    
    //convert Strin Payload to a char array
    int str_len = Payload.length() + 1;
    char char_array[str_len];
    Payload.toCharArray(char_array, str_len);

    Serial.println("");
    Serial.print("Payload: ");
    Serial.println(char_array);

    //Publish all value into a single Topic and wait 10 secondes 

    Serial.println("Sending Payload data... ");
    WEATHER.publish(char_array);       

    digitalWrite(16, 1);
    delay(1000);
    digitalWrite(16, 0);
    delay(9000);
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect()
{
  int8_t ret;
  if (mqtt.connected()) // Stop if already connected
  {
    return;
  }
  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) // connect will return 0 for connected
  {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000); // wait 5 seconds
    retries--;
    if (retries == 0)
    {
      while (1)
        ;
    }
  }
  Serial.println("MQTT Connected!");
}
