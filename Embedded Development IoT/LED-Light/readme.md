# Real Device test with an LED and a Light Sensor

In this sample we'll add a LED and a Light Sensor to the Node MCU ESP8266. The device will:

1. Connect to the specified Wi-Fi network
1. Connect to the MQTT Broker (in this case to your Adafruit.IO account)
1. Subscribe to the LED topic and turn the LED on/off according to the messages received
1. Publish the current light value read from the LDR to the light topic.

**Pre-requirement**: Have your free [Adafruit.IO](https://io.adafruit.com) account created.

The illustration below shows the device, the topics and the dashboard blocks needed:

![Toolchain](../Images/led-flow.png)

## Adafruit.IO: Create the Topics/Feeds and Dashboard elements

Visit https://io.adafruit.com log in with your account and click on the top menu Feeds:

1. Create a new feed/topic: led
1. Click on Dashboards and create a new Dashboard: LED Control
1. Add a toggle ON/OFF connected to the led topic
1. Create a new topic: light
1. Add a stream connected to this topic
1. Add a line chart connected to this topic

## Breadboard Setup

For this sample you'll need:

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

On the Arduino IDE go to menu `Sketch/Include Library/Manage Libraries`

Type Adafruit MQTT, wait to see the results, click on `Adafruit MQTT` by **Adafruit**, select the version 2.8.0 in the “Select Version” dropdown list, and then click Install. If it prompts you for additional libraries, please select “Install ALL”.

## Get your credentials

Visit https://io.adafruit.com log in with your account and click on the yellow icon with a key in the top right part of the page.

It will show you your Username and Active Key. You need to copy both since we'll add these credentials to the sample code.

![Toolchain](../Images/credentials.png)

## Get Sample code

Use the [led-light.ino](led-light/led-light.ino) sample code in this directory and click on the "Copy raw Contents" button at the top right of the code window.

Find the definitions for Wi-Fi and Adafruit Credentials and replace them with your own:

```C
#define WLAN_SSID       "SSID"
#define WLAN_PASS       "password"
#define AIO_SERVER      "io.adafruit.com" //stays as it is
#define AIO_USERNAME    "adafruit_username"
#define AIO_KEY         "adafruit_key"
```

1. Save your code.
1. Upload it to the dev kit.
1. Open the serial monitor window to see the connection progress:

```C
...........
WiFi connected
IP address:
10.127.12.7
Connecting to MQTT... MQTT Connected!
Sending light val 129...
```

Once you see this message in the Serial monitor, go to https://io.Adafruit.com, open your `Led Control` dashboard to see the data being published showing up on your stream block.

Also test your LED control by flipping the toggles switch on and off and see if the LED onboard matches the expected behavior.

Your device should be publishing light values and getting led commands now.

**Attention** please note your Adafruit account only allows for 30 data points per minute, which means if you flip your led on and off more than 30 times you'll get your service throttled. 

