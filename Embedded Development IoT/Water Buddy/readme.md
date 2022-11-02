# Water Buddy

This sample shows the Water Buddy complete with IoT connection.

It uses the kit you received which includes:

1. ESP8266 microcontroller
1. Breadboard
1. 1" OLED Screen
1. Soil Moisture sensor
1. 5V Water Pump

![Toolchain](../Images/waterbuddy.png)

## WaterBuddy Flow

The illustration below shows the device (WaterBuddy) and the needed MQTT Broker topics/feeds, as well as the Dashboard blocks.

![Toolchain](../Images/flow.png)

## Adafruit.IO: Create the Topics/Feeds and Dashboard elements

Visit https://io.adafruit.com log in with your account and click on the top menu Feeds:

1. Create a new feed/topic: dispense
1. Click on Dashboards and create a new Dashboard: WaterBuddy
1. Add a stream connected to the dispense topic
1. Create a new feed/topic: dispense-command
1. Add a momentary button connected to this topic
1. Create a new topic: soil-moisture
1. Add a stream connected to this topic
1. Add a line chart connected to this topic

## Breadboard Setup

For this sample you'll need:

1. Node MCU ESP8266 dev Kit
1. Jumper Wires
1. LED (any color)
1. Resistor 220 Ohms (red, red, brown) or 330 Ohms (orange, orange, brown) to connect the LED
1. Resistor 330 Ohms (orange, orange, brown) connected to the base of the transistor
1. 5V DC Water Pump.
2. 2N3904 NPN transistor
3. OLED Screen.
4. USB **data** cable.

The illustration below shows the connections:

![Toolchain](../Images/waterbuddy-setup.png)

## Libraries needed

On the Arduino IDE go to menu `Sketch/Include Library/Manage Libraries`

Type **PubSubClient**, wait to see the results, click on `PubSubClient` by **Nick O'Leary**, select the version 2.8.0 in the “Select Version” dropdown list, and then click Install.

## Get Sample code

Use the [Water-Buddy.ino](Water-Buddy/Water-Buddy.ino) sample code in this directory.

Find the definitions for Wi-Fi and Adafruit Credentials and replace them with your own.

Following Wi-Fi and Adafruit credentials, there are several `#define` which might need your attention:

1. `TELEMETRY_FREQUENCY_MILLISECS` Initially adjusted for 5000 milliseconds (5 seconds). You can adjust it to any value, but remember that a free Adafruit account only allows for 30 data points per minute.
1. `DISPENSE_TIME_MILLISECS` Initially set for 3 seconds, it defines for how long will the water pump be on every time the sensor detects the soil is under the specified threshold.
1. `MINIMUM_MOISTURE` Initially set for 20%, defines the minimum bar for soil moisture before turning the water pump on. It will vary greatly depending on the type of the plant you have.
1. `WATER_FREQUENCY_MILLISECS` Defined initially to 30 seconds, it defines for how long will the water pump wait for the water to spread, before turning on again.

```C
#define WLAN_SSID       "SSID"
#define WLAN_PASS       "password"
#define AIO_SERVER      "io.adafruit.com"
#define AIO_USERNAME    "Username"
#define AIO_KEY         "KEY"

#define TELEMETRY_FREQUENCY_MILLISECS 5000 //send telemetry data every 5 seconds
#define DISPENSE_TIME_MILLISECS 3000       //will turn the water pump on for 3 seconds at a time 
#define WATER_FREQUENCY_MILLISECS 30000    //wait for 30 seconds before watering again to allow water to spread
#define MINIMUM_MOISTURE 20    //define the minimum moisture level before start the water pump on. 

#define wet 520 //result of the calibration of your sensor for the lower threshold
#define dry 740 //result of the calibration of your sensor for the upper threshold

#define SOIL_PIN    A0  // pin connected to the soil moisture sensor
#define PUMP_PIN    16   // pin connected to the water pump
#define RED_LED     2  // pin connected to the red LED
```

1. Save your code.
1. Upload it to the dev kit.
1. Using the Arduino IDE open the serial monitor window

Your device should be publishing light values and getting led commands now.