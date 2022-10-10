#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

#define AIO_SERVER      "io.adafruit.com"
#define AIO_USERNAME    "USENRAME"
#define AIO_KEY         "KEY"
#define AIO_SERVERPORT  1883                   
WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish door = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/door");
Adafruit_MQTT_Publish lockPub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/lock");
Adafruit_MQTT_Subscribe lockSub = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/lock");
  
void MQTT_connect();

#define doorPin 16
#define servoPin 5
#define buttonPin 10
#define delayValue 500

#include <Servo.h>
Servo myservo; 

bool doorClosed;
bool doorOpened;
bool abrirPorta = false;
bool doorLocked;
bool sendDoorLocked = true;
bool sendDoorOpened = true;
bool sendDoorClosed = true;

ICACHE_RAM_ATTR void abrePorta(){
  //code to open door
  abrirPorta = true;
}

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
  
  pinMode(doorPin,INPUT);
  pinMode(servoPin,OUTPUT);
  pinMode(buttonPin,INPUT);
  myservo.attach(servoPin);

  attachInterrupt(digitalPinToInterrupt(buttonPin), abrePorta, RISING);

  // Setup MQTT subscriptions for all feeds.
  mqtt.subscribe(&lockSub);

  if(digitalRead(doorPin)==LOW){ //if the door is closed, and since the servo can't say its position, ensure by locking it
    Serial.println("INITIALIZE: Closing door");
    myservo.write(120);
    delay(delayValue);
    doorClosed = true;
    doorLocked = true;
  }
  else{
    Serial.println("INITIALIZE: Can't close or lock door");
    myservo.write(120);
  }
}

void loop() {
  
    MQTT_connect();
           
    Adafruit_MQTT_Subscribe *subscription;
    while ((subscription = mqtt.readSubscription(1000))){
     //inside this loop we'll check if there is any news to feeds we subscribe to
     //limited to 5 subscriptions by default
        if (subscription == &lockSub){
          Serial.print(F("Locker: "));
          Serial.println((char *)lockSub.lastread);
          uint16_t lock_desired_state = atoi((char *)lockSub.lastread);  // convert to a number
          if(lock_desired_state == 0)
              abrirPorta = true;
          else
              abrirPorta = false;
       }
    }   
  
  if(abrirPorta){   
    if(!doorOpened){
      Serial.println("Button Pressed: Opening door");
      myservo.write(0);
      delay(2000);
      doorLocked = false;
      abrirPorta = false;
      sendDoorLocked = true;
      if (lockPub.publish("0")) 
        Serial.println("Sending Door Unlocked");
      }
  }

  if(digitalRead(doorPin)==HIGH){
    doorOpened = true;
    if (sendDoorOpened){
      if (door.publish("1")){
        Serial.println("Sending Door Opened");
        sendDoorOpened = false;
      }  
    }
    Serial.println("Open door detected!!");
    doorClosed = false;
    delay(delayValue);
  }
  else{
    delay(delayValue);
    doorOpened = false;
    Serial.println("Closed door detected!!");
    doorClosed = true;
    //Publish MQTT door is closed
  }

  //if door is closed but not locked, lock it
  if(doorClosed && !(doorLocked)){
    if (sendDoorLocked){
      if (door.publish("0"))
        Serial.println("Sending Door Closed");
      if (lockPub.publish("1")){ 
        Serial.println("Sending Door Locked");
        sendDoorLocked = false;
        sendDoorOpened = true;
      }
    }
    Serial.println("Locking closed door");
    myservo.write(120);
    delay(delayValue);
    doorLocked = true;
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
