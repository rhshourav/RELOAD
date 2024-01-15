# RELOAD

This is a smart grid system of ESP32 and ESP8266 devices that communicate with each other using WiFi.

## Features

- The devices can communicate with each other using both wired and wireless connections.
- The devices can exchange data such as temperature, humidity, light, etc.
- The devices can control actuators such as LEDs, motors, relays, etc.
- The devices can be configured and monitored using a web interface or a mobile app.

## Hardware

- ESP32 and ESP8266 boards
- DHT11 or DHT22 sensors for temperature and humidity
- LDR sensors for light intensity
- LEDs, motors, relays, etc. for actuators
- Jumper wires, breadboards, resistors, etc. for connections

## Software

- Arduino IDE for programming the devices
- SmartConfig for configuring the WiFi credentials of the devices
- Esptouch for discovering the devices on the network
- MQTT for sending and receiving data between the devices
- Node-RED for creating the web interface and the mobile app

## How it works

- The devices are programmed using the Arduino IDE and flashed with the firmware that contains the logic and the libraries for the communication and the sensors.
- The devices are configured using the SmartConfig app on a smartphone that sends the WiFi credentials to the devices via UDP packets.
- The devices are discovered using the Esptouch app on a smartphone that scans the network for the devices and displays their IP addresses and MAC addresses.
- The devices are connected to a MQTT broker that acts as a central hub for the data exchange between the devices.
- The devices publish and subscribe to topics on the MQTT broker that correspond to the data or the commands they want to send or receive.
- The web interface and the mobile app are created using Node-RED that connects to the MQTT broker and displays the data or the controls for the devices.

## Images

![ESP32 and ESP8266 boards](^1^)
![SmartConfig app](^2^)
![Esptouch app](^4^)
![Node-RED web interface](^5^)
!Node-RED mobile app

