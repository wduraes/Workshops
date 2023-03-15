#include <ESP8266WiFi.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET  -1 // ESP32  4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define WET 520
#define DRY 740

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define SOIL_PIN    A0  // pin connected to the soil moisture sensor


int getSoil(){
  int soil = analogRead(SOIL_PIN);
  //while the Analog Read varies from 0 to 1028, the sensor never gets
  //to extremes. So we need to manually setup the sensor with a complete
  //DRY sensor and another read with it under water
  if(soil<WET) soil=WET;
  if(soil>DRY) soil=DRY;
  int soilMapped = map(soil,WET,DRY,100,0);
  return(soilMapped); 
}

int getSoilRaw(){
  return(analogRead(SOIL_PIN));
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
  
  /*
  display.setCursor(10, 0); //set the cursor at column 10, line 0
  display.println("Soil :");
  display.setCursor(70, 0);
  display.println(getSoil());
  display.setCursor(100, 0);
  display.println("%");
  */

  display.setCursor(10, 17);
  display.println("Sensor:");
  display.setCursor(70, 17);
  display.println(getSoilRaw());

  display.display();
}

void setup(){
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  displayInitialMsg();
  delay(2000);
}

void loop(){

  displaySoilValue();
  delay(800);
     
}
