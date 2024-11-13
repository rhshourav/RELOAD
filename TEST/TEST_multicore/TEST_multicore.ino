#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <Adafruit_SSD1306.h>
#include "freertos/FreeRTOS.h" // For ESP32 FreeRTOS task management


// WIFI Credentials
const char* ssid = "IT";
const char* password = "TazinSayeed!@#";

// Initialize Telegram BOT
#define BOTtoken "6593502902:AAGsV9AvosqFBzgwKxPCRg5e3LJEUvowzmk"
#define CHAT_ID "6348432516"

// Display constants
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Telegram bot setup
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
QueueHandle_t messageQueue;

// Function prototypes
void listenForMessages(void *parameter);
void displayMessages(void *parameter);
void displayStaticMessage(String message);
void displayScrollingMessage(String message);

void setup() {
  Serial.begin(115200);
  Wire.begin(3, 2);

  // Initialize display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }
  display.clearDisplay();

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  // Telegram secure connection
  #ifdef ESP32
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  #endif

  // Create message queue
  messageQueue = xQueueCreate(10, sizeof(String));

  // Create tasks for each core
  xTaskCreatePinnedToCore(listenForMessages, "TelegramListener", 4096, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(displayMessages, "DisplayManager", 4096, NULL, 1, NULL, 1);
}

// Task: Listen for incoming Telegram messages (runs on Core 0)
void listenForMessages(void *parameter) {
  unsigned long lastTimeBotRan = 0;
  const int botRequestDelay = 1000;

  while (true) {
    if (millis() - lastTimeBotRan > botRequestDelay) {
      int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
      lastTimeBotRan = millis();

      for (int i = 0; i < numNewMessages; i++) {
        String chat_id = String(bot.messages[i].chat_id);
        String text = bot.messages[i].text;

        // Only process messages from the authorized chat ID
        if (chat_id == CHAT_ID) {
          if (xQueueSend(messageQueue, &text, portMAX_DELAY) != pdPASS) {
            Serial.println("Message queue is full!");
          }
        } else {
          bot.sendMessage(chat_id, "Unauthorized user", "");
        }
      }
    }
    delay(10);  // Yield to other tasks
  }
}

// Task: Display messages on the OLED (runs on Core 1)
void displayMessages(void *parameter) {
  String message;
  while (true) {
    // Wait until a message is available in the queue
    if (xQueueReceive(messageQueue, &message, portMAX_DELAY) == pdPASS) {
      if (message.length() * 6 > SCREEN_WIDTH) {  // Approximate width check for scrolling
        displayScrollingMessage(message);
      } else {
        displayStaticMessage(message);
      }
    }
    delay(10);  // Yield to other tasks
  }
}

// Display message statically for 3 seconds if it fits within the display
void displayStaticMessage(String message) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(message);
  display.display();
  delay(3000);  // Display for 3 seconds
}

// Display message with scrolling effect if it's too long for the screen
void displayScrollingMessage(String message) {
  int messageLength = message.length() * 6;  // Approximate length of the message
  int screenWidth = SCREEN_WIDTH;

  for (int i = 0; i < messageLength + screenWidth; i++) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(screenWidth - i, 0);
    display.print(message);
    display.display();
    delay(50);  // Adjust scrolling speed
  }
}

void loop() {
  // No code in loop as tasks are managed by FreeRTOS
}
