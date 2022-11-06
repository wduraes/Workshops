# Securing your device connection

All the samples we used previously used the following arrangement:

```c
#define AIO_SERVERPORT  1883                   
WiFiClient client;
```
The first line defines which port in the MQTT broker the device will connect to. In this case `1883` is a non-secure MQTT port.

Same with the second line which creates a client for Wi-Fi that uses non-secure connection.

In this case, non-secure means that traffic between device and the MQTT broker are open, and could be intercepted and read, including all of data.

The only reasons to use this kind of connection is for test, learning and non-production scenarios, since it is faster and simpler.

## Moving towards security

Changing all code from this class to make them secure is not very hard, but requires some attention:

1. Change MQTT port from 1883 to 8883
1. Change the Wi-Fi client to WiFiClientSecure
1. Add the server footprint to the WiFi connection so that device and MQTT Broker can negotiate a TLS session

The previous code snippet would look like this:

```c
#define AIO_SERVERPORT  8883                   
WiFiClientSecure client;
static const char *fingerprint PROGMEM = "18 C0 C2 3D BE DD 81 37 73 40 E7 E4 36 61 CB 0A DF 96 AD 25";
```
As you can see we added a new variable `fingerprint`, which is a pointer to a character array which contains the MQTT Broker Server Fingerprint.

The secure connection would also require the server certificate fingerprint to be added right after the WiFi connection;
```c
    client.setFingerprint(fingerprint);
```

## TLS handshake

Image below shows at a high level the TLS Handshake, to read more please refer to the [SSL Store](https://www.thesslstore.com/blog/explaining-ssl-handshake/) website.

![SSL](https://www.thesslstore.com/blog/wp-content/uploads/2017/01/SSL_Handshake_10-Steps-1.png)

## Secure forever?

The only constant about security is the need for constant updates. Sometimes the update is needed because the server certificate expired, some other times the private key might be exposed and the service provider will need to rotate (change) the certificate for a new one.

Regardless of the scenario, the certificate **will change** in the future, so you need to be aware of that.

In this case, whenever Adafruit needs to change the certificate, the fingerprint will also change, and devices with the old fingerprint won't be able to connect at all.

If you're reading this anytime after November 2022, please check Adafruit's libraries for their new certificate. [HERE](https://github.com/adafruit/Adafruit_MQTT_Library/blob/master/examples/adafruitio_secure_esp8266/adafruitio_secure_esp8266.ino#L52) is where you would find it as per this page's writing. 

## Testing with your ESP8266 device

Use the [led-light-secure.ino](led-light-secure/led-light-secure.ino) sample code in this directory and click on the "Copy raw Contents" button at the top right of the code window.

Find the definitions for Wi-Fi and Adafruit Credentials and replace them with your own:

```C
#define WLAN_SSID       "SSID"
#define WLAN_PASS       "password"
#define AIO_SERVER      "io.adafruit.com" //stays as it is
#define AIO_USERNAME    "adafruit_username"
#define AIO_KEY         "adafruit_key"
```

Load the sample and check if it connects to MQTT. If it does, your device is secured! (for now)