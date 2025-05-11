// --- Includes ---
#include <WiFi.h>
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoJson.h>
#include "relogo.h"

// --- Pin Assignments ---
#define RELAY_PIN         10   // Relay to boost converter
#define ADAPTER_SENSE_PIN 1    // ADC1: 12V adapter sense
#define BATTERY_SENSE_PIN 0    // ADC2: 12V battery sense
#define STATUS_LED_PIN    9    // Digital in: Laptop status LED
#define PWR_BTN_PIN       8    // Digital out: Simulate power button
#define OLED_SDA          3    // I2C SDA
#define OLED_SCL          2    // I2C SCL

// --- OLED Setup ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- WiFi & Telegram ---
const char* ssid = "IT";
const char* password = "TazinSayeed!@#";
#define BOTtoken "6593502902:AAGsV9AvosqFBzgwKxPCRg5e3LJEUvowzmk"
#define CHAT_ID "6348432516"
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

// --- System State ---
bool laptopPowered = false;
bool adapterPresent = false;
bool batteryPresent = false;
bool laptopOn = false;
String lastEvent = "";

// --- Helper Functions ---
void showLogo() {
  display.clearDisplay();
  display.drawBitmap(0, 0, reloadLogo, 128, 64, 1);
  display.display();
  delay(3000);
}

void showStatus() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Adapter: "); display.println(adapterPresent ? "ON" : "OFF");
  display.print("Battery: "); display.println(batteryPresent ? "ON" : "OFF");
  display.print("Laptop:  "); display.println(laptopOn ? "ON" : "OFF");
  display.print("Event: "); display.println(lastEvent);
  display.display();
}

void sendLog(String msg) {
  bot.sendMessage(CHAT_ID, msg, "");
  lastEvent = msg;
  showStatus();
}

// --- Sensing Functions ---
bool readAdapter() {
  int val = analogRead(ADAPTER_SENSE_PIN);
  return val > 1000; // Adjust threshold as needed
}
bool readBattery() {
  int val = analogRead(BATTERY_SENSE_PIN);
  return val > 1000; // Adjust threshold as needed
}
bool readLaptopOn() {
  return digitalRead(STATUS_LED_PIN) == HIGH;
}

// --- Power Button Simulation ---
void pressPowerButton() {
  digitalWrite(PWR_BTN_PIN, LOW);
  delay(500);
  digitalWrite(PWR_BTN_PIN, HIGH);
  delay(500);
}

// --- Relay Control ---
void setRelay(bool on) {
  digitalWrite(RELAY_PIN, on ? HIGH : LOW);
  laptopPowered = on;
}

// --- Telegram Command Handling ---
void handleTelegram() {
  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  for (int i = 0; i < numNewMessages; i++) {
    String text = bot.messages[i].text;
    if (text == "/on") {
      sendLog("Turning laptop ON...");
      setRelay(true);
      delay(1000);
      pressPowerButton();
      unsigned long t0 = millis();
      while (!readLaptopOn() && millis() - t0 < 20000) {
        delay(500);
      }
      laptopOn = readLaptopOn();
      sendLog(laptopOn ? "Laptop is ON." : "Failed to turn ON laptop.");
    } else if (text == "/off") {
      sendLog("Shutting down laptop...");
      pressPowerButton();
      unsigned long t0 = millis();
      while (readLaptopOn() && millis() - t0 < 60000) {
        delay(500);
      }
      laptopOn = readLaptopOn();
      if (!laptopOn) {
        setRelay(false);
        sendLog("Laptop is OFF. Power disconnected.");
      } else {
        sendLog("Failed to shut down laptop.");
      }
    } else if (text == "/status") {
      String msg = "Adapter: "; msg += adapterPresent ? "ON" : "OFF";
      msg += "\nBattery: "; msg += batteryPresent ? "ON" : "OFF";
      msg += "\nLaptop: "; msg += laptopOn ? "ON" : "OFF";
      msg += "\nEvent: "; msg += lastEvent;
      sendLog(msg);
    }
  }
}

// --- Power Outage Handling ---
void checkPowerEvents() {
  bool newAdapter = readAdapter();
  bool newBattery = readBattery();
  bool newLaptop = readLaptopOn();
  if (adapterPresent && !newAdapter) {
    sendLog("Power outage detected! Initiating shutdown...");
    pressPowerButton();
    unsigned long t0 = millis();
    while (readLaptopOn() && millis() - t0 < 60000) {
      delay(500);
    }
    setRelay(false);
    sendLog("Laptop safely powered down after outage.");
  }
  if (!adapterPresent && newAdapter) {
    sendLog("Power restored! Adapter is back.");
  }
  adapterPresent = newAdapter;
  batteryPresent = newBattery;
  laptopOn = newLaptop;
}

// --- Setup ---
void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(PWR_BTN_PIN, OUTPUT);
  pinMode(STATUS_LED_PIN, INPUT);
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(PWR_BTN_PIN, HIGH);
  Wire.begin(OLED_SDA, OLED_SCL);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  showLogo();
  display.clearDisplay();
  display.display();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Connecting WiFi...");
    display.display();
  }
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("WiFi OK: ");
  display.println(WiFi.localIP());
  display.display();
  delay(1000);
  client.setInsecure(); // For testing, use root cert in production
  sendLog("RELOAD Controller Online.");
  adapterPresent = readAdapter();
  batteryPresent = readBattery();
  laptopOn = readLaptopOn();
  showStatus();
}

// --- Main Loop ---
void loop() {
  if (millis() > lastTimeBotRan + botRequestDelay) {
    handleTelegram();
    lastTimeBotRan = millis();
  }
  checkPowerEvents();
  showStatus();
  delay(1000);
}
// --- End of File --- 