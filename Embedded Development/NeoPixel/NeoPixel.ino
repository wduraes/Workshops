#include <Adafruit_NeoPixel.h>
#define LED_PIN    6
#define LED_COUNT 30
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop() {

      strip.setPixelColor(0,50,0,0);         //  Set pixel's color (in RAM)
      strip.setPixelColor(1,50,0,0); 
      strip.setPixelColor(2,50,0,0); 
      strip.show(); 
}
