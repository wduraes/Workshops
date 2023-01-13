# How to build an IoT device from scratch

## Why build a new IoT Dev Kit?

I'm part of the Azure IoT team responsible for Device SDKs to simplify the connection of IoT devices to the Azure cloud. One of the devices, for which we create and maintain samples, is the very popular ESP32. The ideal development kit to test an IoT device capabilities must have several onboard sensors - so we don't need to send fake telemetry - and some actuators like LEDs, an OLED screen, buzzer and so on. I only use fake telemetry if I have no other choice...  

As it turns out, Espressif used to manufacture the amazing [ESP32 Azure IoT kit](https://www.espressif.com/en/products/devkits/esp32-azure-kit/overview), which had all the above and I was very happy with it. However, the ESP32 module part of that dev kit became obsolete and with it the whole dev kit. With no replacement in sight, I decided to design and build one myself. Also, by having my own dev kit, I could share blank PCBs with the parts so that software engineers on the team and other folks could practice building an IoT device themselves.

## Device Features

This IoT device was made to fulfill several requirements:

1. Based on the latest [ESP32 module](https://www.espressif.com/en/products/modules/esp32) (currently the ESP32-WROOM-32E)
2. Simple to assemble and solder even for people with little experience
3. Minimize use of SMD parts whenever possible, preferring larger SMD packages (no smaller than 0805) to allow manual soldering
4. Have onboard sensors: light, temperature, humidity
5. Have a user button connected to a GPIO pin for later use
6. Have onboard: 2 LEDs, neopixel, buzzer, N-channel MOSFET
7. Power input via micro USB connector, since these power adapters are very easy to find
8. Allow for 5 to 12VDC power to be provided via header pins
9. No onboard programming chip to simplify the design and save power later (requires an external UART programmer)
10. Have a reset button
11. Have a programming jumper, instead of a button, to simplify programming
12. Expose as many GPIO as possible via standard header pins
14. Compact size PCB but shouldn't require fine pitch SMD parts
15. Have round corners (just for aesthetics) and mounting holes in the PCB
17. Have hardware debounce on the user button
18. Have simple to solder parts, which requires adjust on thermal relief pads connected to GND

## Creating your device

- [Parts and Tradeoffs](./choosing%20parts.md)
- [Device Design](./device%20design.md)
- [PCB Design](./PCB%20design.md)
- [Assembly Guidance](./assembly%20guidance.md)
- [Testing the final product](./testing.md)

## Adding IoT to the IoT device

Adding Iot capabilities to this device now is only a matter of getting the proper firmware installed, given the native Wi-Fi capabilities of the ESP32.

To test this board with Azure IoT, there are several possibilities:

1. How to connect the ESP32 to IoT Hub using Arduino IDE - [link](https://github.com/Azure/azure-sdk-for-c-arduino/tree/main/examples/Azure_IoT_Hub_ESP32)
1. How to connect the ESP32 to IoT Hub and Azure Device Update (OTA) using Arduino IDE - [link](https://github.com/Azure/azure-sdk-for-c-arduino/tree/main/examples/Azure_IoT_Adu_ESP32)
1. How to connect the ESP32 to IoT Hub using FreeRTOS [link](https://github.com/Azure-Samples/iot-middleware-freertos-samples/blob/main/demos/projects/ESPRESSIF/esp32)
1. How to connect the ESP32 to IoT Hub and Azure Device Update (OTA) using FreeRTOS -[link](https://github.com/Azure-Samples/iot-middleware-freertos-samples/blob/main/demos/projects/ESPRESSIF/adu/README.md)

## Closing thoughts

If you read all of the above, I'm sure you might have found several instances in which you would do things differently, and even some errors and omissions from my part. If you would be so kind as to let me know, I'll be glad to consider them for the next revision. So far this board has been working really well for all scenarios I tried so far and 8 of the devices (I made 10 total in the first batch) are running continuously as some sort of Long Haul testing. So far so good!