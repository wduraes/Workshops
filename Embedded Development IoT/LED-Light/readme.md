# Real Device test with an LED and a Light Sensor

In this sample we'll add a LED to the Light Sensor example.The device will:

1. Connect to the specified Wi-Fi network
1. Connect to the MQTT Broker (in this case to your Adafruit.IO account)
1. Subscribe to the LED topic and turn the LED on/off according to the messages received
1. Publish the current light value read from the LDR to the light topic.

**Pre-requirement**: Have your free [Adafruit.IO](https://io.adafruit.com) account created.

The illustration below shows the device, the topics and the dashboard blocks needed:

![Toolchain](../Images/led-flow.png)

## Adafruit.IO: Create the Topics/Feeds and Dashboard elements

Visit https://io.adafruit.com log in with your account.

Click on the top menu `Feeds`:

1. Create a new feed/topic: `led`

Click on the top menu `Dashboards`:

1. Click on `LED Control` to access this dashboard
1. Click on the top right cogwheel icon, then `create a new block` to:
   1. Add a toggle ON/OFF connected to the `led` topic

## Breadboard Setup

For this sample you'll need the same setup as the light sensor example:

1. Node MCU ESP8266 dev Kit
1. Jumper Wires
1. LDR (Light sensor)
1. LED (any color)
1. Resistor 220 Ohms (red, red, brown) or 330 Ohms (orange, orange, brown) to connect the LED
1. Resistor 1K Ohms (brown, black, red) or 2K2 (red, red, red) to connect the LDR
1. USB **data** cable.

The illustration below shows the connections:

![Toolchain](../Images/led-setup.png)

## Libraries needed

**[If you already installed this library, please skip this step]**

On the Arduino IDE go to menu `Sketch/Include Library/Manage Libraries`

Type Adafruit MQTT, wait to see the results, click on `Adafruit MQTT` by **Adafruit**, select the version 2.8.0 in the “Select Version” dropdown list, and then click Install. If it prompts you for additional libraries, please select “Install ALL”.

## Get your credentials

Visit https://io.adafruit.com log in with your account and click on the yellow icon with a key in the top right part of the page.

It will show you your Username and Active Key. You need to copy both since we'll add these credentials to the sample code.

![Toolchain](../Images/credentials.png)

## Get Light Sensor sample code

Use the [light-sensor.ino](light-sensor/light-sensor.ino) sample code below.

```c
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define WLAN_SSID       "SSID"
#define WLAN_PASS       "password"
#define AIO_SERVER      "io.adafruit.com"
#define AIO_USERNAME    "adafruit_username"
#define AIO_KEY         "adafruit_key"
#define AIO_SERVERPORT  1883                   
WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Subscribe led = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/led");
Adafruit_MQTT_Publish light= Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/light");
  
void MQTT_connect();

#define ledPin 2
#define ldrPin A0
   
void setup() {
    
  Serial.begin(115200);
    pinMode(ledPin,OUTPUT);
    pinMode(ldrPin,INPUT);
     
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
  
    // Setup MQTT subscriptions for all feeds.
    mqtt.subscribe(&led);
  }
     
  void loop() {
  
    MQTT_connect();
   
    Adafruit_MQTT_Subscribe *subscription;
    while ((subscription = mqtt.readSubscription(5000))) 
    {  
     //inside this while loop we'll check if there is any news to feeds we subscribe to
     //limited to 5 subscriptions by default
      
      if (subscription == &led) 
      {
        Serial.print(F("Got: "));
        Serial.println((char *)led.lastread);
      }
  
      if (strcmp((char *)led.lastread, "ON") == 0) 
      {
          digitalWrite(ledPin, 1); 
      }
        
       if (strcmp((char *)led.lastread, "OFF") == 0) 
       {
          digitalWrite(ledPin, 0); 
       }        
    }

    float Light = analogRead(ldrPin);
    if (light.publish(Light)) 
    {
        Serial.print("Sending light val ");
        Serial.print(Light);
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
  }

```

Find the definitions for Wi-Fi and Adafruit Credentials and replace them with your own:

```C
#define WLAN_SSID       "SSID"
#define WLAN_PASS       "password"
#define AIO_SERVER      "io.adafruit.com" //stays as it is
#define AIO_USERNAME    "adafruit_username"
#define AIO_KEY         "adafruit_key"
```

1. Save your code.
1. Plug your ESP8266 using an USB **DATA cable**
1. Select the correct COM port under `Tools/Port`.
1. Select the `NODE MCU 1.0` under EP8266 `Tools/Board/ESP8266 Boards/Node MCU 1.0 (ESP-12E module)`
1. Under `Tools/Upload Speed` select `256000` for faster uploads.
1. Upload your code to the board.
1. Open the serial monitor window to see the connection progress. You should see something like this:

```C
...........
WiFi connected
IP address:
10.127.12.7
Connecting to MQTT... MQTT Connected!
Sending light val 129...
```

Once you see this message in the Serial monitor, go to https://io.Adafruit.com, open your `Led Control` dashboard to see the data being published showing up on your stream block.

Your device should be publishing light values **and getting led commands** now.

Also test your LED control by flipping the toggles switch on and off and see if the LED onboard matches the expected behavior.