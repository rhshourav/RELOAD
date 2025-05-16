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
#define BATTERY_SENSE_PIN 0     // ADC2: 12V battery sense
#define STATUS_LED_PIN    9    // Digital in: Laptop status LED
#define PWR_BTN_PIN       8    // Digital out: Simulate power button
#define OLED_SDA          3    // I2C SDA
#define OLED_SCL          2    // I2C SCL

// --- Voltage Divider resistor values (in Ohms)
const float R1 = 8332.0; //Top Resistor (8.332k Measured)
const float R2 = 2190.0; // Bootom resistor (2.19k)

// --- ESP32 ADC properties 
const float ADC_MAX = 4095.0; // 12-bit ADC
const float VREF = 3.3;       // Reference Voltage (v)


// --- OLED Setup ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- WiFi & Telegram ---
const char* ssid = "IT";
const char* password = "TazinSayeed!@#";
const char* ssid1 = "Subzero";
const char* password1 = "Subzero123";
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
unsigned long lastEventTime = 0;
bool showEventLog = false;
unsigned long lastEventDisplay = 0;

// --- Helper Functions ---
void showLogo() {
  display.clearDisplay();
  display.drawBitmap(0, 0, reloadLogo, 128, 64, 1);
  display.display();
  delay(3000);
}

void showStatus(bool showEvent = false) {
  int adcValue = analogRead(BATTERY_SENSE_PIN);
  float vOut = (adcValue / ADC_MAX) * VREF;
  float vIn = vOut * (R1 + R2) / R2;
  int batteryLevel=(vIn - 11.4) * 100;

  display.clearDisplay();

  // Title - Centered, Bold
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds("RELOAD", 0, 0, &x1, &y1, &w, &h);
  display.setCursor((SCREEN_WIDTH - w) / 2, 0);
  display.print("RELOAD");

  // Icons row (spaced evenly)
  display.setTextSize(1);
  int y = 22;
  int iconSpacing = 32;
  int x = 0;

  // Battery Icon + %
  //int batteryLevel = batteryPresent ? (adapterPresent ? 100 : 40) : 0; // Example logic
  x = 0;
  display.drawRect(x, y, 18, 8, SSD1306_WHITE); // battery body
  display.fillRect(x + 18, y + 2, 2, 4, SSD1306_WHITE); // battery tip
  int fill = map(batteryLevel, 0, 100, 0, 14);
  if (batteryLevel > 0) display.fillRect(x + 2, y + 2, fill, 4, SSD1306_WHITE);
  display.setCursor(x, y + 12);
  display.print("BAT");
  display.setCursor(x, y + 22);
  if (batteryLevel > 0) {
    display.print(batteryLevel); display.print("%");
  } else {
    display.print("--");
  }

  // Adapter Icon
  x += iconSpacing;
  if (adapterPresent) {
    display.drawCircle(x + 8, y + 4, 4, SSD1306_WHITE); // plug circle
    display.drawLine(x + 8, y + 8, x + 8, y + 12, SSD1306_WHITE); // plug prong
    display.drawLine(x + 6, y + 12, x + 10, y + 12, SSD1306_WHITE); // plug base
  } else {
    display.drawCircle(x + 8, y + 4, 4, SSD1306_WHITE);
  }
  display.setCursor(x, y + 12);
  display.print("ADP");

  // Laptop Icon
  x += iconSpacing;
  display.drawRect(x, y, 16, 8, SSD1306_WHITE); // screen
  display.drawLine(x, y + 8, x + 16, y + 8, SSD1306_WHITE); // base
  if (laptopOn) {
    display.fillRect(x + 2, y + 2, 12, 4, SSD1306_WHITE); // filled screen
  }
  display.setCursor(x, y + 12);
  display.print("LAP");
  display.setCursor(x, y + 22);
  display.print(laptopOn ? "ON" : "OFF");

  // WiFi Icon + Signal
  x += iconSpacing;
  int wifiStrength = WiFi.status() == WL_CONNECTED ? 3 : 0; // 0-3 bars
  if (WiFi.status() == WL_CONNECTED) {
    for (int i = 0; i < wifiStrength; i++) {
      display.fillRect(x + 2 + i * 3, y + 8 - i * 2, 2, 2 + i * 2, SSD1306_WHITE);
    }
  } else {
    display.drawRect(x + 2, y + 8, 8, 2, SSD1306_WHITE);
  }
  display.setCursor(x, y + 12);
  display.print("WiFi");
  display.setCursor(x, y + 22);
  display.print(WiFi.status() == WL_CONNECTED ? "OK" : "--");

  // Section separator
  //display.drawLine(0, 38, SCREEN_WIDTH, 38, SSD1306_WHITE);

  // Last event/message (multi-line if needed)
  if (showEvent) {
    display.setTextSize(1);
    display.setCursor(2, 41);
    int maxLen = 21;
    String msg = lastEvent;
    if (msg.length() > maxLen) {
      display.print(msg.substring(0, maxLen));
      display.setCursor(2, 51);
      display.print(msg.substring(maxLen));
    } else {
      display.print(msg);
    }
  }

  display.display();
}

void sendLog(String msg) {
  bot.sendMessage(CHAT_ID, msg, "");
  lastEvent = msg;
  lastEventTime = millis();
  showEventLog = true;
  lastEventDisplay = millis();
  showStatus(true);
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
      sendLog("Checking Adpater and Battery......");
      if( )
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
      int adcValue = analogRead(BATTERY_SENSE_PIN);
      float vOut = (adcValue / ADC_MAX) * VREF;
      float vIn = vOut * (R1 + R2) / R2;
      String msg = "Adapter: "; msg += adapterPresent ? "ON" : "OFF";
      msg += "\nBattery: "; msg += batteryPresent ? "ON" : "OFF"; msg +=" Battery Voltage= "; msg += vIn;
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

// --- Voltage Detection
/*
void readVoltage(){
  int adcValue = analogRead(BATTERY_SENSE_PIN);
  float vOut = (adcValue / ADC_MAX) * VREF;
  float vIn = vOut * (R1 + R2) / R2;

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Voltage Test");
  display.print("ADC: "); display.println(adcValue);
  display.print("Vout: "); display.print(vOut, 2); display.println("V");
  display.print("Vin:  "); display.print(vIn, 2); display.println("V");
  display.display();
}
*/

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

  
  while (WiFi.status() != WL_CONNECTED ) {
      
      delay(500);
      display.clearDisplay();
      display.setCursor(0, 0);
      display.print("Connecting IT...");
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

  // Show event log for 5 seconds after update, and every 10 seconds for 5 seconds
  unsigned long now = millis();
  bool showEvent = false;
  if (showEventLog && (now - lastEventDisplay < 5000)) {
    showEvent = true;
  } else if ((now - lastEventTime > 10000) && (now - lastEventTime < 15000)) {
    showEvent = true;
  } else {
    showEventLog = false;
  }
  showStatus(showEvent);
  delay(1000);
  //readVoltage();
}
// --- End of File --- 