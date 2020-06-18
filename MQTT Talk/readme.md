# MQTT Open talk 

This page was created to support the [MQTT open-talk](https://www.meetup.com/SnoCo-Makers/events/271344616/) at Snoco Makerspace (not a workshop, more like a casual demo + chat) focused on people interested in learning a little more about MQTT and Mosquitto.

What we'll cover:

- Part 1 - Installing the Toolchain:
1. [Installing tools](https://github.com/wduraes/Workshops/tree/master/MQTT%20Talk#step-1---toolchain---download-and-install-various-tools)
2. [Windows Terminal](https://github.com/wduraes/Workshops/tree/master/MQTT%20Talk#step-2---toolchain---windows-terminal)
3. [WSL - Windows Subsystem for Linux](https://github.com/wduraes/Workshops/tree/master/MQTT%20Talk#step-3---toolchain---wsl)
4. [Mosquitto - MQTT Broker](https://github.com/wduraes/Workshops/tree/master/MQTT%20Talk#step-4---toolchain---installing-mosquitto)
5. [Node-Red](https://github.com/wduraes/Workshops/tree/master/MQTT%20Talk#step-5---toolchain---installing-node-red)

- Part 2 - Exploring:

6. [Mosquitto (Subscribe and Publish)](https://github.com/wduraes/Workshops/tree/master/MQTT%20Talk#step-6---exploring-mosquitto)
7. [Visual Interface for MQTT](https://github.com/wduraes/Workshops/tree/master/MQTT%20Talk#step-7---exploring-mosquitto-visual-interface)
8. [Creating Visual Flows](https://github.com/wduraes/Workshops/tree/master/MQTT%20Talk#step-8---exploring-node-red-creating-visual-flows)
9. [External MQTT Brokers](https://github.com/wduraes/Workshops/tree/master/MQTT%20Talk#step-9---exploring-external-mqtt-brokers)
10. [MQTT Mobile App](https://github.com/wduraes/Workshops/tree/master/MQTT%20Talk#step-10---exploring-one-last-thing-mobile-client)

___

## Part I - Installing  the Toolchain

## Step 1 - Toolchain - Download and Install Various Tools

- Install WSL (works only on Windows 10) - [Link to Microsoft Docs](https://docs.microsoft.com/en-us/windows/wsl/install-win10)
  - Use WSL 1 if you have an older version of Windows 10
  - How can I tell? Hit the windows key, type "Winver", hit enter
  - If you have windows 2004 go for WSL 2
- The previous step requires you to restart your computer.
- Install Ubuntu 18.04 from [Windows Store](https://www.microsoft.com/en-us/p/ubuntu-1804-lts/9n9tngvndl3q?activetab=pivot:overviewtab) (it might work with other versions but I didn't try them)
- Install Windows Terminal from [Windows Store](https://www.microsoft.com/en-us/p/windows-terminal/9n0dx20hk701?activetab=pivot:overviewtab)
- Install MQTT Fx client - [Link](https://mqttfx.jensd.de/)

## Step 2 - Toolchain - Windows Terminal

- Setup WSL as the primary option on Windows Terminal

```json
"defaultProfile": "{hash that matches your Ubuntu 18.04 installation}",
```

- Test some of the coolest features on Terminal:
   - Full screen: alt+enter
   - Panels: alt+shift+plus
   - Subpanels: alt+shift+minus
   - Moving between panels: alt+arrow
   - Resize panel: alt+shift+arrow
   - Close panel: ctrl+shift+w

- Miss the old CRT monitor? Try this (add this line before the last line on the Ubuntu definition):

```json
"experimental.retroTerminalEffect":true,
```
- Change to false to disable (or just comment out the line)

## Step 3 - Toolchain - WSL

- Open Windows Terminal (Ubuntu 18.04 should already be the default)
- Update your Ubuntu:

```bash
sudo apt-get update
sudo apt-get upgrade -y
sudo apt-get install sl -y
```
Test your installation (remember: Linux is case sensitive)

```bash
sl
mkdir TEST
cd TEST
touch myFile.txt

```
- We created a directory and a file. What if I need to access this file from Windows? Where that file would be?
- Go to windows Explorer and test \\\wsl$ 
- Windows maps the network path to Ubuntu so you can easily find your Linux files
- In this case the fiel would be in \\\wsl$\Ubuntu-19.04\home\pi\TEST

## Step 4 - Toolchain - Installing Mosquitto

- Open Windows Terminal (Ubuntu 18.04 should already be the default)
- Install [Mosquitto](https://mosquitto.org/) - the MQTT broker
- Install Mosquitto-clients - allow interaction with the broker

```bash
sudo apt-get install mosquitto -y
sudo apt-get install mosquitto-clients -y
```

Test your installation

```bash
mosquitto
```

## Step 5 - Toolchain - Installing Node-Red

- Open Windows Terminal (Ubuntu 18.04 should already be the default)
- Install NodeJS (Node-Red is a NodeJS application)
- Check Node JS Version (should be XXXX or higher)
- Install npm (package manager)
- Install [Node Red](https://nodered.org/)

```bash
sudo apt-get install nodejs
node -v
sudo apt-get install npm
sudo npm install -g --unsafe-perm node-red node-red-admin
```
Test your installation

```bash
node-red
```
___

## Part II - Exploring

## Step 6 - Exploring Mosquitto

- In this topic we'll be exploring the following MQTT concepts:
  -	Publish
  -	Subscribe
  -	Topics
  -	QOS
  -	Debug 
  - Retain
- Open Windows Terminal (Ubuntu 18.04 should already be the default)
- Run Mosquitto

### 6.1 - Mosquitto Subscribe

- Mosquitto Subscribe details [here](https://mosquitto.org/man/mosquitto_sub-1.html).
- Open a new panel (alt+shift+plus)
  
```bash
Mosquitto_sub -d -t /dev/test
```

Where: 
 - mosquitto_sub = subscribe to a topic on the broker
 - -d = debug - will show details of the communication with the broker
 - -t  = topic name
 - /dev/test = name of the topic you wish to subscribe
 - -u = username (not needed when set to anonnymous access)
 - -P = password (not needed when set to anonnymous access)
 - -h = host IP (if not provided, defautl to LOCALHOST, which is our case)

Note all the debug information provided!!
  
### 6.2 - Mosquitto Publish

- Mosquitto Publish details [here](https://mosquitto.org/man/mosquitto_pub-1.html).
- Open a new panel (alt+shift+plus)
  
```bash
Mosquitto_pub -d -t /dev/test -m "message test"
```

Where: 
 - mosquitto_pub = publish a message to a topic on the broker
 - -d = debug - will show details of the communication with the broker
 - -t  = topic name
 - /dev/test = name of the topic you wish to subscribe
 - -u = username (not needed when set to anonnymous access)
 - -P = password (not needed when set to anonnymous access)
 - -h = host IP (if not provided, defautl to LOCALHOST, which is our case)
 - -q = QOS (defaults to zero if not provided)
 - -r = retain (if provided will retain the last message on this topic)

Once again, note all the debug information provided!!

## Step 7 - Exploring Mosquitto Visual Interface

- Not a fan of command line interfaces?
- Let's try MQTT.fx
- Allow for easy Publish and Subscribe

## Step 8 - Exploring Node Red: Creating Visual Flows

- Open a new panel (alt+shift+plus)
  
```bash
node-red
```
- Note the IP and port on the panel information once you start node red
- Go to your browser and navigate to that IP/Port
- Create your first flow!
- We'll cover just the surface of what Node-red can do, if you want to learn more, check the amazing videos from [Opto](https://www.youtube.com/user/OptoVideo/videos) on YouTube.

## Step 9 - Exploring External MQTT Brokers

- [Adafruit IO](https://io.adafruit.com) - Requires account (free)
- Note that your topic name starts with...

```bash
Mosquitto_pub -d -t WD/dev/test -m "message test" -u "WD" -P "WD" -h "io.adafruit.com"
```

- [Paho](https://mqtt.eclipse.org) - Test server

```bash
Mosquitto_pub -d -t /dev/test -m "message test" -h "eclipse"
```

- [Mosquitto](https://test.mosquitto.org) - Test Server

```bash
Mosquitto_pub -d -t /dev/test -m "message test" -h "mosquitto"
```

- Raspberry Pi
  - If you have a Raspberry Pi, you can reuse all the steps to setup Mosquitto and Node-Red on your Pi and have a small server in your own network.
  - Normally Node-red is already installed with Raspbian (Now Raspberry Pi OS)
  - Simply check your Pi IP address and use it on the sample code below

```bash
Mosquitto_pub -d -t /dev/test -m "message test" -h "192.168.0.1"
```

## Step 10 - Exploring one last thing: Mobile Client

- MQTT Explorer (from XXXXXX)
- Client for Android