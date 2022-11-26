# How to build an IoT device from scratch

## Why build a new IoT Dev Kit?

I'm part of the Azure IoT team responsible for Device SDKs to simplify the connection of IoT devices to the Azure cloud. One of the devices, for which we create and maintain samples, is the very popular ESP32. The ideal development kit to test an IoT device capabilities must have several onboard sensors - so we don't need to send fake telemetry - and some actuators like LEDs, an OLED screen, buzzer and so on.

As it turns out, Espressif used to manufacture the amazing ESP32 Azure IoT kit, which had all the above and we were very happy with it. However, the ESP32 module part of that dev kit became obsolete and with it the dev kit. With no replacement in sight, I decided to build one myself.

Also, by having my own dev kit, I could share blank PCBs with the parts so that software engineers on the team could practice building a device themselves.

## Device Features

This IoT device was made to fulfill several purposes:

1. Based on the latest ESP32 module (currently the ESP32-WROOM-32E)
2. Simple to assemble and solder even for people with little experience
3. Minimize use of SMD part whenever possible, prefer larger SMD packages (at least 0805) to allow manual soldering
4. Have onboard sensors: light, temperature, humidity
5. Have a user button
6. Have onboard actuators: 2 LEDs, neopixel, buzzer, N-channel MOSFET
7. Power via micro USB connector
8. Allow for 5 to 12VDC power to be provided via header pins
9. No onboard programming (requires external UART programmer)
10. Have a reset button
11. Have a programming jumper
12. Have a power jumper to cutoff all sensors if desired, to minimize power consumption
13. Expose as many GPIO as possible via standard header pins
14. Small size PCB but should'nt require fine pitch SMD parts
15. Have round corners (just for aesthetic) and mount holes in the PCB
16. Be used for learning and testing purposes, so a generic device
17. Have hardware debounce on the user button
18. Have simple to solder parts, which requires adjust on thermal relief pads connected to GND

## Parts and tradeoffs

The choices I made when selecting the parts for this device were based on the features above but, above all, it should be simple to understand, simple to assemble, low cost and have readily available libraries.

### Choosing the ESP32 module

### Choosing the Neopixel

### Choosing the Light Sensor

The choice for light sensor was a simple LDR (light dependant resistor), a through hole component which is very cheap and simple to solder by hand.

I love the TEMT7000 series of photo transistors which tend to be much faster in reacting to light transitions, but this 3 pin SMD part can be a bit tricky to solder by hand. Also, is can cost several timer more than a simple LDR.

The LDR choice also makes it easier to remove the part from the PCB, and have it placed elsewhere connecting it back to the PCB with wires. I tested, and even with 10 meters long wires the sensor still works as expected.

### Choosing the Temperature Sensor

The choice in this case was the impossible-to-beat-cheap DHT11 (the blue one), a through hole component which is simple to solder by hand and which provides not only temperature but also humidity readings. This component is not recommended to any scenarios in which precision is key, but for generic tests and sending telemetry to the cloud, this was enough. Should we needed a little more precision but still wanted the through hole aspect, a simple upgrade would be to use the DHT22.

Both DHT11 and DHT22 sensors use an ordinary digital pin on the ESP32 and a timing pattern to communicate back and forth. Several libraries help building solutions but you should not attempt to read temperature and humidity often, since this will increase the sensor temperature thus affecting significantly its results. A good ballpark is to read the DHT data once per second at most.

Should we want to use an SMD part, there are several alternatives most of them using an I2C bus like the BME280.

### Choosing the Power Circuitry

According to the ESP32E datasheet it requires 3.3VDC to operate, so we need a voltage regulator, be that an LDO (Low Drop Output), a DC-DC converter, or an equivalent circuit. In this case, for simplicity and cost I chose the AMS117 3.3V. While this is an SMD component, the SOT223 package chosen makes it really simple to solder by hand.

There is also a shottky diode to prevent any current to make its way back to the USB port.

The header pin has power inputs of both 5-12VDC which goes to the LDO, but also a 3.3VDC rail that goes straight into the ESP32, so beware that any extra voltages there will damage your ESP32.

### Choosing the Programming Method

A programmer chip (USB to Serial) makes the programming and reprogramming simpler, but it also be in the dev kit forever, taking up space and - most importantly - consuming battery, which can be really bad depending on the scenario.

This device was built with simplicity in mind it does not have an USB to Serial chip, requiring one of the following:

1. CH340G: cheap and esy to use, it might require installing additional drivers to work properly on your PC.
2. CP2102: same, but in this case the correct drivers are installed along with Arduino IDE.
3. FT232RL: a bit better thant the previous, it costs a little more but it has its advantages.
4. OTA: Regardless of the above methods, the plan is to do it only once. Program the ESP32 with a firmware which will allow it to get updates over the air (OTA) so the an USB to Serial chip won't be missed.

### Choosing the MOSFET

### Choosing the Buzzer

## Getting started with the design

Reading ESP32 datasheet, hardware design guidelines and ESP32 Azure Kit docs

## Designing the Device (schematics)

## Validating the design (prototype)

## Designing the PCB

## Testing the final product

adding libraries with Arduino IDE to test

## Power consumption tests

## Adding IoT to the IoT device (finally!!)

## Closing thoughts

If you read all of the above, I'm sure you might have found several instances in which you would do things differently, and even some errors and omissions from my part. If you would be so kind as to let me know, I'll be glad to consider them for the next revision. So far this board has been working really well for all scenarios I tried so far and 8 of the devices (I made 10 total in the first batch) are running continuously as some sort of Long Haul testing. So far so good!