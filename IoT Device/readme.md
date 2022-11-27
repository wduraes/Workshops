# How to build an IoT device from scratch

## Why build a new IoT Dev Kit?

I'm part of the Azure IoT team responsible for Device SDKs to simplify the connection of IoT devices to the Azure cloud. One of the devices, for which we create and maintain samples, is the very popular ESP32. The ideal development kit to test an IoT device capabilities must have several onboard sensors - so we don't need to send fake telemetry - and some actuators like LEDs, an OLED screen, buzzer and so on. I only use fake telemetry if I have no other choice...  

As it turns out, Espressif used to manufacture the amazing [ESP32 Azure IoT kit](https://www.espressif.com/en/products/devkits/esp32-azure-kit/overview), which had all the above and I was very happy with it. However, the ESP32 module part of that dev kit became obsolete and with it the whole dev kit. With no replacement in sight, I decided to build one myself. Also, by having my own dev kit, I could share blank PCBs with the parts so that software engineers on the team could practice building a device themselves.

## Device Features

This IoT device was made to fulfill several requirements:

1. Based on the latest ESP32 module (currently the ESP32-WROOM-32E)
2. Simple to assemble and solder even for people with little experience
3. Minimize use of SMD part whenever possible, prefer larger SMD packages (no smaller than 0805) to allow manual soldering
4. Have onboard sensors: light, temperature, humidity
5. Have a user button
6. Have onboard: 2 LEDs, neopixel, buzzer, N-channel MOSFET
7. Power input via micro USB connector, since these power adapters are very easy to find
8. Allow for 5 to 12VDC power to be provided via header pins
9. No onboard programming (should require an external UART programmer)
10. Have a reset button
11. Have a programming jumper (simpler and better than a button)
12. Expose as many GPIO as possible via standard header pins
14. Small size PCB but shouldn't require fine pitch SMD parts
15. Have round corners (just for aesthetic) and mount holes in the PCB
17. Have hardware debounce on the user button
18. Have simple to solder parts, which requires adjust on thermal relief pads connected to GND

## Parts and tradeoffs

The choices I made when selecting the parts for this device were based on the features above but, above all, it should be simple to understand, simple to assemble, low cost and have readily available libraries.

### Choosing the ESP32 module

First step is to define which of the currently available ESP32 modules I would use. [Espressif website](https://www.espressif.com/en/products/modules/esp32) has plenty information to help you decide. Notice that I'm mentioning ESP32 module and not SoC (System on a Chip) the reason is that I'd rather have the complete module with all parts needed to make the SoC work and certifications regariding RF. Also, because using the SoC is not as simple, and I wanted this device to be simple.

Espressif has the ESP32S and C series but I'm sticking to the very popupar ESP32 for now, since I'm not interested in onboard USB or dealing with a RISC-V MCU.

The basic [ESP32](https://www.espressif.com/en/products/modules/esp32) has 3 base devices: WROOM, WROVER (which has SPIRAM as well as flash) and Mini (which has less flash memory, but it is integrated with the SoC so it makes a smaller footprint). 

Even narrowing it down to the ESP32 WROOM, we still face 3 choices: 32E, 32UE and DA.

* **32E** is the traditional module with an integrated PCB antenna we see on Node-MCU types of development kits
* **32UE** has a smaller form factor and has an U.FL antenna connector
* **DA** is the dual-antenna version and it looks like a tiny t-shirt

![Toolchain](../Images/esp32.png)

I got all my ESP32 from [Digi-key](https://www.digikey.com/), but **obviously** there are more choices after the ESP32-WROOM-32E, so I went with the [ESP32-WROOM-32E-N4](https://www.digikey.com/en/products/detail/espressif-systems/ESP32-WROOM-32E-N4/11613125) which has 4MB of Flash (there are 8 and 16MB options as well, but they were out of stock).

With that in mind, and the order created, all I had to do was to save the link for two very important documents:

1. [ESP32 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32e_esp32-wroom-32ue_datasheet_en.pdf)
2. [ESP32 Hardware Design Guidelines](https://www.espressif.com/sites/default/files/documentation/esp32_hardware_design_guidelines_en.pdf)

### Choosing the Neopixel

I like neopixels better than RGB LEDs because I can control them using only one digital pin, instead of 3 for the RGB LED. The tradeoff here is the complexity, since driving the RGB LED with 3 PWM pins is very simple, no additional library needed, but I wanted to save my digital pins, and went with the [WS2812B](https://www.digikey.com/en/datasheets/parallaxinc/parallax-inc-28085-ws2812b-rgb-led-datasheet) NeoPixel. 

This makes an excellent visual indicator, so I can use it to show different states like "blinking red" not connected to Wi-Fi, "blinking yellow" connected to wi-fi but not to Azure, "solid blue" connected to Azure, "blinking blue" downloading an update, and so forth. 

**Additional LEDs** note that I also added 2 regular LEDs because I wanted aditional visual indicators on board.  

### Choosing the Light Sensor

The choice for light sensor was a simple [LDR (light dependent resistor)](https://en.wikipedia.org/wiki/Photoresistor), a through hole component which is very cheap and simple to solder by hand.

I love the [TEMT7000](https://www.vishay.com/docs/81961/temt7000x01.pdf) series of photo transistors which tend to be much faster in reacting to light transitions, but this SMD part can be a bit tricky to solder by hand. Also, is can cost several timer more than a simple LDR.

The LDR choice also makes it easier to remove the part from the PCB, and have it placed elsewhere connecting it back to the PCB with wires. I tested and, even with 10 meters long wires, the sensor still works as expected.

### Choosing the Temperature Sensor

The choice in this case was the impossible-to-beat-cheap [DHT11](https://www.circuitbasics.com/wp-content/uploads/2015/11/DHT11-Datasheet.pdf) (the blue one), a through hole component which is simple to solder by hand and which provides not only temperature but also humidity readings. This component is not recommended to any scenarios in which precision is key, but for generic tests and sending telemetry to the cloud, this was enough. Should we needed a little more precision but still wanted the through hole aspect, a simple upgrade would be to use the [DHT22](https://www.sparkfun.com/datasheets/Sensors/Temperature/DHT22.pdf).

![Toolchain](../Images/dht.jpg)

Both DHT11 and DHT22 sensors use an ordinary digital pin on the ESP32 and a timing pattern to communicate back and forth. Several libraries help building solutions but you should not attempt to read temperature and humidity often, since this will increase the sensor temperature thus affecting significantly its results. A good ballpark is to read the DHT data once per second at most.

Also, there are the **always present** bad data readings, in which we read for the sensor and get only garbage. This requires your code to always check for the data coming from the DHT to ensure it is usable before sending it as telemetry (the `isNaN` should do the trick most of the time).

Should we want to use an SMD part, there are several alternatives most of them using an I2C bus like the [BME280](https://www.bosch-sensortec.com/media/boschsensortec/downloads/product_flyer/bst-bme280-fl000.pdf) from Bosch.

Adafruit created [this awesome reference](https://learn.adafruit.com/modern-replacements-for-dht11-dht22-sensors) explaining the advantages of using more modern sensors instead of the DHT11/22, which obviously I decided to ignore for my device. 

### Choosing the Power Circuitry

According to the ESP32E datasheet it requires a voltage range of 1.8 V ~ 3.6 VDC to operate, so we need a voltage regulator, be that an LDO (Low Drop Output), a DC-DC converter, or an equivalent circuit. In this case, for simplicity and cost I chose the [AMS117 3.3V](http://www.advanced-monolithic.com/pdf/ds1117.pdf). While this is an SMD component, the SOT223 package chosen makes it really simple to solder by hand.

I also added a shottky diode to prevent any current to make its way back to the USB port.

The header pin has power inputs of both 5-12VDC which goes to the LDO, but also a 3.3VDC rail that goes straight into the ESP32, so beware that any extra voltages there will damage your ESP32.

### Choosing the Programming Method

A programmer chip (USB to Serial) makes the programming and reprogramming simpler, but it will also be in the dev kit forever, taking up space and - most importantly - consuming battery, which can be really bad depending on the scenario.

This device does not have an USB to Serial chip, requiring one of the following:

1. [CH340G](https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all): cheap and esy to use, it might require installing additional drivers to work properly on your PC.
2. [CP2102](https://www.adafruit.com/product/5335): same, but in this case the correct drivers are installed along with Arduino IDE.
3. [FT232](https://www.adafruit.com/product/2264): a bit better thant the previous, it costs a little more but it has its advantages.
4. OTA: Regardless of the above methods, the plan is to do it only once. Program the ESP32 with a firmware which will allow it to get updates over the air (OTA) so the an USB to Serial chip won't be missed.

### Choosing the MOSFET

[2N7000](https://www.digikey.com/en/products/detail/onsemi/2N7000BU/976604)

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