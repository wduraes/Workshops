## Using the Moisture sensor with the OLED Screen

Before we move to the full WaterBuddy sample, which include the IoT commands, we need to build and validate usage of the OLED screen and the moisture sensor. 

We also need to calibrate the sensor readings for Dry x Wet as we show below. 

## Breadboard Setup

For this sample you'll need:

1. Node MCU ESP8266 dev Kit
1. Jumper Wires
1. Moisture sensor
1. OLED Screen
1. USB **data** cable.

The illustration below shows the connections:

![Toolchain](../Images/moisturesensor.png)

## Libraries needed

On the Arduino IDE go to menu `Sketch/Include Library/Manage Libraries`

Type SSD1306, wait to see the results, click on `Adafruit SSD31306` by **Adafruit**, select the version 2.5.7 in the “Select Version” dropdown list, and then click Install. If it prompts you for additional libraries, please select “Install ALL” - see picture below.

![Toolchain](../Images/libraries.png)

## Get sample code

Use the [soilmoisture.ino](soilmoisture/soilmoisture.ino) sample code in this directory and click on the "Copy raw Contents" button at the top right of the code window.

This sample will be used to validate if your OLED screen and your Soil Moisture are working properly.

It will display the reading from the moisture sensor once every 800ms.

## Testing

Once you get the code into your ESP8266, with the Moisture Sensor still dry, make a note of the lowest and highest readings in the screen.

Dip the sensor into water carefully until the water hits the white horizontal line. You're not supposed to get the sensor components wet. Once again, make a note of the lowest and highest readings in the screen.

The table below show the results of my test:

![Toolchain](../Images/sensor-range.png)

These readings will vary according to your ESP8266 sensitivity, the sensor quality, and even the air humidity, reason why we need to do this calibration.

After that we'll setup a function to transform the sensor reading into a number between 0 and 100% moisture scale.

We'll consider any reading below 520 as 100% moisture and any reading above 740 as 0%.

The activation of the water pump is not part of this sample, and it will vary according to the type of soil, climate, and plant you're monitoring. (I know close to zero with regards to gardening...)

Go back to your code, and replace the values at lines 11 and 12 for the values you got.

Uncomment lines 52 and 59 by removing the comments opening `/*`and the comments closing `*/` then test your code again to see the values in a percentile scale.