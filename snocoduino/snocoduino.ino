#include <Adafruit_NeoPixel.h>
#define PIN            9
#define NUMPIXELS      1
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(13,OUTPUT);
  pixels.begin();
  pixels.setBrightness(153);
  pixels.show();

  pixels.setPixelColor(0,75,0,0);
  pixels.show();
  delay(500);
  pixels.setPixelColor(0,0,0,0);
  pixels.show();
  delay(500);
  pixels.setPixelColor(0,75,75,0);
  pixels.show();
  delay(500);
  pixels.setPixelColor(0,0,0,0);
  pixels.show();
  delay(500);
  pixels.setPixelColor(0,0,75,0);
  pixels.show();
  delay(500);
  pixels.setPixelColor(0,0,0,0);
  pixels.show();
  delay(500);
  pixels.setPixelColor(0,0,75,75);
  pixels.show();
  delay(500);
  pixels.setPixelColor(0,0,0,0);
  pixels.show();
  delay(500);
  pixels.setPixelColor(0,75,0,75);
  pixels.show();
  delay(500);  
  pixels.setPixelColor(0,0,0,0);
  pixels.show();
  delay(500);
  pixels.setPixelColor(0,75,75,75);
  pixels.show();
  delay(500);
}

void loop() {
  digitalWrite(13,HIGH);
  pixels.setPixelColor(0,0,0,0);
  pixels.show();
  delay(700);
  digitalWrite(13,LOW);
  pixels.setPixelColor(0,55,0,0);
  pixels.show();
  delay(700);
}
