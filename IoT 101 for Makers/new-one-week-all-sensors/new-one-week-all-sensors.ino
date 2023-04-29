#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include "SparkFunBME280.h"
#include <Adafruit_NeoPixel.h>

#define WLAN_SSID "SSID"
#define WLAN_PASS "password"
#define AIO_SERVER "io.adafruit.com"
#define AIO_USERNAME "wduraes"
#define AIO_KEY "aio_uVc0bl2Qu128ffl7pq81mYoscFhQ"
#define AIO_SERVERPORT 1883
#define TELEMETRY_FREQUENCY_MILLISECS 10000

#define PIN 2       // pin connected to the NeoPixels
#define NUMPIXELS 3 // how many NeoPixels we have
#define BUZZER 14   // pin connected to the buzzer
#define LIGHT A0    // pin connected to the light sensor
#define LED1 12     // pin connected to LED 1
#define LED2 13     // pin connected to LED 2
#define intPin 15   // pin connected to the Button

#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
unsigned long lastMsg = 0;
bool btnPressed = false;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
BME280 mySensor;

// TODO - get this to work with SSL
WiFiClient espClient;
// WiFiClientSecure espClient;
PubSubClient client(espClient);

// io.adafruit.com SHA1 fingerprint
//static const char *fingerprint PROGMEM = "59 3C 48 0A B1 8B 39 4E 0D 58 50 47 9A 13 55 60 CC A0 1D AF";

// function called by the Interrupt: should be as simples and quick as possible
// here, we just flip a boolean variable true and have a short delay to act a a debouncing mechanism
void ICACHE_RAM_ATTR ButtonPress()
{
  btnPressed = true;
  delay(20);
}

void setup_wifi()
{
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WLAN_SSID, WLAN_PASS);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  // TODO: do I need this???  
  //randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *payload, unsigned int length)
{
  //Deal with any incoming message for the topics we're subscribing to

  // Serial.print("Message arrived [");
  // Serial.print(topic);
  // Serial.print("] ");

  // TODO: is there a better way to get the message content without a String object?
  String topicStr(topic);  //holds the name of the Topic 
  String contentStr;       //holds the message payload (content)
  for (int i = 0; i < length; i++)
  {
    // Serial.print((char)payload[i]);
    contentStr = contentStr + (char)payload[i];
  }
  // Serial.println();
  // Serial.print("Message content: ");
  // Serial.println(contentStr);

  //check if the topic was led1 and act upon it
  if (topicStr == "AIO_USERNAME/feeds/led1")
  {
    if (contentStr.toInt() == 1)
    {
      digitalWrite(LED1, HIGH);
    }
    else if (contentStr.toInt() == 0)
    {
      digitalWrite(LED1, LOW);
    }
  }

  //check if the topic was led2 and act upon it
  if (topicStr == AIO_USERNAME "/feeds/led2")
  {
    if (contentStr.toInt() == 1)
    {
      digitalWrite(LED2, HIGH);
    }
    else if (contentStr.toInt() == 0)
    {
      digitalWrite(LED2, LOW);
    }
  }

  //check if the topic was slider and act upon it
  if (topicStr == AIO_USERNAME "/feeds/slider")
  {
    if (contentStr.toInt() > 500)
    {
      digitalWrite(5, 1);
      tone(BUZZER, 1000);
      pixels.setPixelColor(0, 40, 0, 0);
      pixels.setPixelColor(1, 40, 0, 0);
      pixels.setPixelColor(2, 40, 0, 0);
      pixels.show();
    }
    else
    {
      digitalWrite(5, 0);
      noTone(BUZZER);
      pixels.setPixelColor(0, 0, 0, 0); // set the 1st neoPixel off
      pixels.setPixelColor(1, 0, 0, 0); // set the 2nd neoPixel off
      pixels.setPixelColor(2, 0, 0, 0); // set the 3rd neoPixel off
      pixels.show();
    }
  }

  //check if the topic was neopixel and act upon it
  if (topicStr == AIO_USERNAME "/feeds/neopixel")
  {
    Serial.print(F("Got a message down from NeoPixel Topic"));
    // convet Hex to RGB
    // TODO - 2hy won't this work if I pass contentStr instead of &contentStr ?
    // long number = (long) strtol( &hexstring[1], NULL, 16);
    long number = (long)strtol(&contentStr[1], NULL, 16);
    int r = number >> 16;
    int g = number >> 8 & 0xFF;
    int b = number & 0xFF;
    pixels.setPixelColor(0, r, g, b);
    pixels.setPixelColor(1, r, g, b);
    pixels.setPixelColor(2, r, g, b);
    pixels.show();
  }
}

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("", AIO_USERNAME, AIO_KEY))
    {
      Serial.println("connected");
      client.subscribe(AIO_USERNAME "/feeds/slider");
      client.subscribe(AIO_USERNAME "/feeds/neopixel");
      client.subscribe(AIO_USERNAME "/feeds/led1");
      client.subscribe(AIO_USERNAME "/feeds/led2");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  Wire.begin();
  mySensor.setI2CAddress(0x76);
  if (mySensor.beginI2C() == false) // Begin communication over I2C
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    while (1)
      ; // Freeze
  }

  pixels.begin();
  pixels.setPixelColor(0, 0, 0, 0); // set the 1st neoPixel off
  pixels.setPixelColor(1, 0, 0, 0); // set the 2nd neoPixel off
  pixels.setPixelColor(2, 0, 0, 0); // set the 3rd neoPixel off
  pixels.show();
  delay(100);
  pixels.setPixelColor(0, 40, 0, 0);
  pixels.setPixelColor(1, 0, 40, 0);
  pixels.setPixelColor(2, 0, 0, 40);
  pixels.show();
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  delay(1000);
  tone(BUZZER, 1000);
  delay(200);
  noTone(BUZZER);
  pixels.setPixelColor(0, 0, 0, 0); // set the 1st neoPixel off
  pixels.setPixelColor(1, 0, 0, 0); // set the 2nd neoPixel off
  pixels.setPixelColor(2, 0, 0, 0); // set the 3rd neoPixel off
  pixels.show();
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);

  setup_wifi();
  client.setServer(AIO_SERVER, AIO_SERVERPORT);

  // check the fingerprint of io.adafruit.com's SSL cert
  //client.setFingerprint(fingerprint);
  
  client.setCallback(callback);

  // interrupt to be triggered when the button is pressed
  attachInterrupt(digitalPinToInterrupt(intPin), ButtonPress, RISING);
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  //check if it is time to do some publishing
  if (now - lastMsg > TELEMETRY_FREQUENCY_MILLISECS)
  {
    lastMsg = now;
    sendTelemetry();    
  }

  //Handles the interrupt triggered by the button press
  if (btnPressed)
  {
    if (client.publish(AIO_USERNAME "/feeds/slider", "0"))
    {
      Serial.println("Turning Slider down");
    }
    btnPressed = false;
  }
}
