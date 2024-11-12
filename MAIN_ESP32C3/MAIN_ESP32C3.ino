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
  Wire.begin(3, 2);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
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
  welcome += "Just Saying I am online.\n";
  welcome += "Main_0.1-Home.Lab";
  bot.sendMessage(CHAT_ID, welcome, "");

  res();
  cle();
}

void loop() {
  //This part will handel incoming request in loop
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    
    lastTimeBotRan = millis();
    String message = getLatestMessage();  // Get the latest message from Telegram
    if (message.length() > 0) {
      if (message.length() > SCREEN_WIDTH) {
        displayScrollingMessage(message);  // Display message with scrolling
      } else {
        displayStaticMessage(message);  // Display static message for 3 seconds
      }
    }

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
  
}

///////////////////////////////////////////////////
// Handle what happens when you receive new messages
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));
  
  for (int i=0; i<numNewMessages; i++) {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    
    // Print the received message
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;
    String IP = WiFi.localIP().toString();

    if (text == "/start" || text == "/help") {
      String welcome = "Welcome, " + from_name + ".\n";
      welcome += "Use the following commands Can Be Execute Via RELOAD.\n\n";
      welcome += "/ip To Show Loacal IP. \n";
      welcome += "/on To Turn On Laptop. \n";
      bot.sendMessage(chat_id, welcome, "");
    }

    if (text == "creator" || text == "Creator") {
      String message = from_name+", Shourav Has Created Me.";
      bot.sendMessage(chat_id, message, "");
    }
    //BOT IP FUNCTION
    if (text == "/ip" || text == "/Ip" || text == "/IP") {
      
      String message= "RELOAD IP: " + IP + "\n";
      bot.sendMessage(chat_id, message, "");
      show_ip();
      cle();
    }
  }
}



////////////////////////////////
//Function that will show ip:
void show_ip(){
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
  res();
  display.setTextSize(2); 
  display.println("LOCAL IP :");
  display.setCursor(0, 20);
  display.println(WiFi.localIP());
  display.display();
  delay(10000);
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
// Function to get the latest message from the bot
String getLatestMessage() {
  String message = "";
  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  
  if (numNewMessages) {
    for (int i = 0; i < numNewMessages; i++) {
      String text = bot.messages[i].text;
      message = text;
      // Update last message received using message_id (not chat_id)
      bot.last_message_received = bot.messages[i].message_id;  // Use message_id instead of chat_id
    }
  }
  return message;
}

// Function to display the message statically for 3 seconds
void displayStaticMessage(String message) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(message);
  display.display();
  
  delay(3000);  // Display for 3 seconds before clearing
}

// Function to scroll the message on the OLED display
void displayScrollingMessage(String message) {
  int messageLength = message.length() * 6;  // Approximate length of the message
  int screenWidth = SCREEN_WIDTH;
  
  // Loop through the message, updating the position for scrolling effect
  for (int i = 0; i < messageLength + screenWidth; i++) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(screenWidth - i, 0);
    display.print(message);  // Print the message on the screen
    display.display();
    delay(50);  // Delay to control scroll speed
  }
}