/* 
 *  This is the sample for the Water Buddy. It takes an ESP8266 and a soil moisture sensor
 *  to monitor a plant, activating a water pump when needed.
 *  
 */

#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET  -1 // ESP32  4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define WLAN_SSID       "SSID"
#define WLAN_PASS       "password"
#define AIO_SERVER      "io.adafruit.com"
#define AIO_USERNAME    "Username"
#define AIO_KEY         "KEY"
#define AIO_SERVERPORT 1883

#define TELEMETRY_FREQUENCY_MILLISECS 5000 //send telemetry data every 5 seconds
#define DISPENSE_TIME_MILLISECS 1000       //will turn the water pump on for 3 seconds at a time 
#define WATER_FREQUENCY_MILLISECS 30000    //wait for 30 seconds before watering again to allow water to spread
#define MINIMUM_MOISTURE 20    //define the minimum moisture level before start the water pump on. 

#define wet 520 //result of the calibration of your sensor for the lower threshold
#define dry 740 //result of the calibration of your sensor for the upper threshold

#define SOIL_PIN    A0  // pin connected to the soil moisture sensor
#define PUMP_PIN    16   // pin connected to the water pump
#define RED_LED     2  // pin connected to the red LED

bool dispenseNow = false;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
unsigned long lastMsg = 0;
unsigned long lastWater = 0;

WiFiClient espClient;
PubSubClient client(espClient);

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

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *payload, unsigned int length)
{
  String topicStr(topic);  //holds the name of the Topic 
  String contentStr;       //holds the message payload (content)
  for (int i = 0; i < length; i++){
    contentStr = contentStr + (char)payload[i];
  }

  //check if the topic was dispense-command and act upon it
  if (topicStr == AIO_USERNAME "/feeds/dispense-command"){
    if (contentStr.toInt() == 1)
      Serial.println("Got a dispense command!");
      dispenseNow = true;
  }
}

void reconnect(){
  // Loop until we're reconnected
  while (!client.connected()){
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("", AIO_USERNAME, AIO_KEY)){
      Serial.println("connected");
      client.subscribe(AIO_USERNAME "/feeds/dispense-command");
    }
    else{
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

int getSoil(){
  int soil = analogRead(SOIL_PIN);
  //while the Analog Read varies from 0 to 1028, the sensor never gets
  //to extremes. So we need to manually setup the sensor with a complete
  //dry sensor and another read with it under water
  if(soil<wet) soil=wet;
  if(soil>dry) soil=dry;
  int soilMapped = map(soil,wet,dry,100,0);
  return(soilMapped); 
}

void displayWaterOn(){
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  
  display.setCursor(10, 0);
  display.println("WATER");
  display.setCursor(10, 17);
  display.println("  ON");

  display.display();      // Show initial text
}

void displayInitialMsg(){
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  
  display.setCursor(10, 0);
  display.println("Automatic");
  display.setCursor(10, 17);
  display.println("  Garden");

  display.display();      // Show initial text
}

void displaySoilValue(){
  display.clearDisplay();
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  
  display.setCursor(10, 0);
  display.println("Soil :");
  display.setCursor(70, 0);

  display.println(getSoil());
  display.setCursor(100, 0);
  display.println("%");

  display.display();
}

void dispenseWater(){
  Serial.println("Executing a dispense command!");
  displayWaterOn();
  digitalWrite(PUMP_PIN,HIGH);
  delay(DISPENSE_TIME_MILLISECS);
  digitalWrite(PUMP_PIN,LOW);
  //publish when we water the plant
  client.publish(AIO_USERNAME "/feeds/dispense", "1");
}

void pumpLogic(){

  //TODO
  //to be filled with the proper watering schedule and sensor threshold
  digitalWrite(RED_LED,HIGH);
  delay(200);
  digitalWrite(RED_LED,LOW);
  delay(200);

  if(getSoil()<MINIMUM_MOISTURE){ //check if plant needs water: soil moisture < 20%
    unsigned long now = millis();
    if (now - lastWater > WATER_FREQUENCY_MILLISECS){ //check if 30 seconds have passed since the last water dispense
    lastWater = now;
    dispenseNow = true;
    }
  }
}

void sendTelemetry()
{
  //get soil moisture sensor and publish its value
    snprintf(msg, MSG_BUFFER_SIZE, "%d", getSoil());
    if (client.publish(AIO_USERNAME "/feeds/soil-moisture", msg))
    {
      Serial.print("Sending soil moisture val ");
      Serial.print(msg);
      Serial.println(" %...");
    }
}

void setup(){
  Serial.begin(115200);

  pinMode(RED_LED,OUTPUT);
  pinMode(PUMP_PIN,OUTPUT);
  digitalWrite(PUMP_PIN,LOW);
    
  setup_wifi();
  client.setServer(AIO_SERVER, AIO_SERVERPORT);

  client.setCallback(callback);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // If can't find the OLED Screen, don't proceed, loop forever
  }

  displayInitialMsg();
  delay(2000);
}

void loop(){
  
  //takes care of Wi-Fi and MQTT reconnection
  if (!client.connected()){
    reconnect();
  }
  client.loop();

  //check if it is time to do some publishing
  unsigned long now = millis();
    if (now - lastMsg > TELEMETRY_FREQUENCY_MILLISECS){
    lastMsg = now;
    sendTelemetry();    
  }

  //Dispense water mechanism
  if (dispenseNow){
    dispenseWater();
    dispenseNow = false;
    Serial.println("Dispense command complete!");
  }
  
  //show current moisture level in the OLE screen
  displaySoilValue();

  //call water pump function to check if plant needs water
  pumpLogic();       
}
