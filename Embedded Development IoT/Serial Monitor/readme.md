## Serial Monitor and the Arduino IDE

Serial communication is one of the most common ways to check what is happening with your microcontorller (Arduino UNO, ESP8266 and pretty much any other MCU).

It comes handy specially when you don't have a screen attached to your project.

Use the modified version of Blink to see it in action:

```c
void setup(){
    pinMode(2,OUTPUT);
    Serial.begin(9600);
}
void loop(){
    digitalWrite(2,HIGH);
    Serial.println("Turned LED ON");
    delay(1000);
    digitalWrite(2,LOW);
    Serial.println("Turned LED OFF");
    delay(1000);
}
```

Load this sample to your ESP8266, then click `Tools\Serial Monitor`

The speed of 9600 BPS (baud per second) is one of the most common for the Arduino UNO, but for the ESP8266 and other faster MCUs the speed of 115200 is far more common.

You can select the serial communication speed in the Serial Monitor window in the dropdown at bottom right.

![Toolchain](../Images/serialmonitor.png)

If all you see in the Serial Monitor is some sort of gibberish data like in the screen above, it is **very likely** you have th wrong speed settings. Note in this case the Serial Monitor is set to `115200 baud` but the code is set to 9600, in the `Serial.begin(9600);` line.