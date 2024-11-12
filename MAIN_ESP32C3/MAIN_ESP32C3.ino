#include <WiFi.h>
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "relogo.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// WIFI Credentials
const char* ssid = "IT";
const char* password = "TazinSayeed!@#";

// Initialize Telegram BOT
#define BOTtoken "6593502902:AAGsV9AvosqFBzgwKxPCRg5e3LJEUvowzmk"
#define CHAT_ID "6348432516"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// Checks for new messages every 1 second
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

void setup() {
  Serial.begin(115200);
  Wire.begin(3, 2);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(2000);  // Pause for 2 seconds

  display.clearDisplay();
  display.drawBitmap(0, 0, MY_LOGO, 128, 64, 1);
  display.display();
  delay(4000);
  display.clearDisplay();
  display.drawBitmap(0, 0, reloadLogo, 128, 64, 1);
  display.display();
  delay(5000);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
   // Clear display and initialize
  display.clearDisplay();
  display.setTextSize(2);  // Set text size
  display.setTextColor(SSD1306_WHITE);  // Set text color
  display.setCursor(0, 0);  // Set the starting position of text
  display.display();
  display.clearDisplay();  // Clear the display
  display.setCursor(0, 0);  // Set text cursor position to top-left
  display.print("Connecting..");  // Print the label
  //display.print(count);  // Display the counter value
  display.display();  // Update the display
  delay(500);


  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print(WiFi.localIP());
  display.display();
  delay(5000);
  #ifdef ESP32
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT);  // Use the built-in root certificate from the library
    configTime(0, 0, "pool.ntp.org");             // Set time from NTP server
  #endif

  


  // Sending Online Message
  String welcome = "Hey, Shourav.\n";
  welcome += "Just Saying I am online.\n\n";
  welcome += "Main_0.1-Home.Lab"
  bot.sendMessage(CHAT_ID, welcome, "");

  res();
  cle();
}

void loop() {
  cle();
  res();
}

/////////////////////////////
// Function to clear display
void cle() {
  display.clearDisplay();
  display.display();
}

/////////////////////////////////////
// Function to reset display settings
void res() {
  display.setTextSize(1);
  display.setCursor(0, 0);
}
