## Testing the final product

Once the final device has been assembled, I recommend performing a quick visual inspection has been performed for any obvious solder bridges and other issues, and checking for short circuits between VCC/VDD and GND. If you don't find any issues, it is time to power the device.

To power this device you have several options:
1. Use an external 5V power supply or one of those celullar chargers with a micro USB connector
1. Connect a 5 to 12VDC power supply to the pins VCC and GND
1. Connect **exactly** 3.3VDC to the VDD and GND pins

Most programmers can't power the device so there is a need for this external power to get the ESP32 working properly.

With the external power plugged in, it is time to setup the programmer via the header pins. Regardless of your choice of programmer, you'll connect both of them like the table below describes:

| ESP32 Device | Programmer |
|--|--|
| GND | GND |
| TX | RX |
| RX | TX |

There's no need to connect any other pins from the programmer into the ESP32.

<img src="../Images/programming.png" width="100%">

Normally, at this point I would do a very simple test with the Blink sketch, replacing the LED_BUILTIN by the LEDs on pin 26 or 27 (there is a nice cheat sheet with all pins in the back of the board, so it is easy to refer to any of the onboard components).

One example of test code is:

```c
#define LED1_PIN 26 //yellow led
#define LED2_PIN 27 //blue led
#define DHTPIN 14    //temperature sensor
#define BUZZER 32   //buzzer
#define LDR 33      //light sensor

#include <DHT.h>
#include <DHT_U.h>
#include "SPI.h"
#define DHTTYPE DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);

#include <Adafruit_NeoPixel.h>
#define PIN            25
#define NUMPIXELS      1
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  pinMode(LED1_PIN,OUTPUT);
  pinMode(LED2_PIN,OUTPUT);
  
  dht.begin();

  pixels.begin();
  pixels.setBrightness(153);
  pixels.show();
  
  Serial.println("TURNED ON");
  delay(1000);  
}

void loop() {
   
  sensors_event_t event;  
  
  for(int i=0;i<10;i++){
    digitalWrite(LED1_PIN,HIGH);
    digitalWrite(LED2_PIN,LOW); 
    pixels.setPixelColor(0,0,0,85);
    pixels.show();
    delay(200); 
    delay(500);
    digitalWrite(LED1_PIN,LOW);
    digitalWrite(LED2_PIN,HIGH);  
    pixels.setPixelColor(0,0,85,0);
    pixels.show();
    delay(500);
  }
   
  dht.temperature().getEvent(&event); 
  if(!isnan(event.temperature))
    {
          Serial.print("Temp: ");
          Serial.println(event.temperature);
    }

  dht.humidity().getEvent(&event); 
  if(!isnan(event.relative_humidity))
    {
          Serial.print("Humidity: ");
          Serial.println(event.relative_humidity);
    }

  Serial.print("Light Sensor: ");
  Serial.println(analogRead(LDR));
  Serial.print("- - - - - - -");
}
```

Close the PROG header pins with the jumper, and push the RESET button once to get the device into programming mode. Upload your code normally and once this is finished, remove the PROG jumper and hit RESET once again.

This should be enough to get your device working properly.

In my experience I had some failures in programming due to bad / misbehaving programmers, so it was a simple matter of testing with another programmer for things to work. Don't trust blindly the first programmer you test.
