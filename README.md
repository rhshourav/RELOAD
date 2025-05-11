# RELOAD

This repository contains smart grid and automation projects using ESP32 and ESP8266 devices.

## New: ESP32-C3 Laptop Power Controller (Project reload)

A smart controller for remotely managing a laptop motherboard (Lenovo) powered by a 12V battery pack (boosted to 20V), with:
- Telegram bot control (turn ON/OFF, status, logs)
- Power outage detection and safe shutdown
- OLED display for status and logs
- Real-time event notifications

### Hardware Required
- ESP32-C3
- SSD1306 OLED (I2C)
- Relay or MOSFET (for switching 20V to laptop)
- Optocoupler/relay (for simulating laptop power button)
- Voltage dividers for 12V adapter and battery sensing
- Wire from laptop status LED to ESP32 (for ON/OFF detection)
- 12V battery pack, 12V adapter, 20V boost converter

### Wiring (Pin Assignments)
| ESP32 Pin | Function                        |
|-----------|---------------------------------|
| GPIO 10   | Relay Control                   |
| GPIO 1    | 12V Adapter Sense (ADC1)        |
| GPIO 0    | 12V Battery Sense (ADC2)        |
| GPIO 9    | Laptop Status LED Sense         |
| GPIO 8    | Power Button Simulation         |
| IO2       | OLED SDA                        |
| IO3       | OLED SCL                        |

### Features
- **/on**: Connects power and simulates power button to turn laptop ON
- **/off**: Simulates power button for shutdown, waits for full shutdown, then disconnects power
- **/status**: Reports adapter, battery, and laptop state
- **Real-time logs**: All events sent to Telegram bot
- **Power outage handling**: Detects loss/return of adapter, safely shuts down laptop, and notifies via Telegram
- **OLED display**: Shows RELOAD logo on boot, then live status and last event

### Usage
1. Wire the system as described above.
2. Flash `Project reload/main_controller.ino` to your ESP32-C3.
3. Configure your WiFi and Telegram bot credentials in the code.
4. Use the Telegram bot to control and monitor your laptop remotely.

---

## Legacy: Smart Grid System

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

