## WiFi Manager

Samples created for this class need Wi-Fi credentials so the device can get online and connected to the cloud service. a simple way to do that is to add the Wi-Fi credentials to the source code, which works fine if you only want the device to ever be connected to that same Wi-Fi access point.

If that's not the case, this method is not good, and a Wi-Fi manager library should be used instead. A very good and well documented library os [this one](https://github.com/tzapu/WiFiManager) from tzapu.

### Direct connection

The code snippet below shows the connection using credentials baked into the source code:

```c
#include <ESP8266WiFi.h>

#define WLAN_SSID       "SSID"
#define WLAN_PASS       "password"
                
void setup() {
Serial.begin(115200); 
  
// Connect to WiFi access point.
Serial.println(); 
Serial.print("Connecting to ");
Serial.println(WLAN_SSID);
  
WiFi.begin(WLAN_SSID, WLAN_PASS);
    while (WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print(".");
}
Serial.println();
Serial.println("WiFi connected");
Serial.println("IP address: "); 
Serial.println(WiFi.localIP());
}

void loop() {  
    //nothing to do here    
  }
```

### Wi-Fi manager connection

A better alternative, **if you can spare the space needed for it**, is to use the Wi-Fi manager library. For comparison, the simple connection requires 274,229 bytes (267kB) of Flash memory, while the Wi-Fi manager requires 350,573 bytes (342kB), so a total of **75kB of additional space**.

It will look for known WiFi access points and if it can't find one, it will create an access point as defined in the code (in our case it will be named `ESP8266 SSID` and it will require a password, in our case `password`). You'll be able to connect to this network using any device and select the correct WiFi access point to use.

The credential will be saved into the device for use as long as the SSID is available.

#### Library Setup

On the Arduino IDE go to menu `Sketch/Include Library/Manage Libraries`

Type **Wifimanager**, wait to see the results, click on `WiFiManager` by **tablatronix**, select the version 2.0.13-beta in the “Select Version” dropdown list, and then click Install.

#### Library usage

The code snippet below shows the connection using the WiFi manager instead.

```c
#include <ESP8266WiFi.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
          
//WiFiClient client;

void setup() {
Serial.begin(115200);
WiFiManager wm;
bool res;

res = wm.autoConnect("ESP8266 SSID","password"); // password protected ap

    if(!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("WiFi connected");
        Serial.println("IP address: "); 
        Serial.println(WiFi.localIP());
    } 
}

void loop() {
  //nothing to do here
}
```