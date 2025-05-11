#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin not used

// WiFi and Telegram configurations
const char* ssid = "IT";
const char* password = "TazinSayeed!@#";

// Initialize Telegram BOT
#define botToken "6593502902:AAGsV9AvosqFBzgwKxPCRg5e3LJEUvowzmk"
#define CHAT_ID "6348432516"

WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// FreeRTOS components
QueueHandle_t messageQueue;
SemaphoreHandle_t displaySemaphore;
TaskHandle_t messageListenerTask;
TaskHandle_t displayTask;

// Function to initialize OLED
void initializeDisplay() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
}

// Display a message on the OLED
void showMessage(String message) {
    if (xSemaphoreTake(displaySemaphore, portMAX_DELAY)) {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println(message);
        display.display();
        xSemaphoreGive(displaySemaphore);
        delay(3000); // Display each message for 3 seconds
    }
}

// Connect to WiFi and display connection status
void connectToWiFi() {
    WiFi.begin(ssid, password);
    showMessage("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    showMessage("Connected to WiFi.");
    client.setInsecure(); // Skip SSL verification for Telegram
}

// Fetch new messages from Telegram
void fetchTelegramMessages() {
    int messageCount = bot.getUpdates(bot.last_message_received + 1);
    showMessage("Checking Telegram...");

    if (messageCount > 0) {
        for (int i = 0; i < messageCount; i++) {
            String messageText = bot.messages[i].text;
            showMessage("Message found!");
            delay(1000); // Briefly display message found

            if (messageText.length() > 0) {
                xQueueSend(messageQueue, &messageText, portMAX_DELAY); // Queue message
                showMessage("Queued: " + messageText);
                delay(2000); // Display queued message
            }
        }
    } else {
        showMessage("No new messages.");
    }
}

// Task for listening to messages on Core 1
void messageListenerTaskCode(void * parameter) {
    for (;;) {
        fetchTelegramMessages();
        delay(5000); // Check for new messages every 5 seconds
    }
}

// Task for displaying messages on Core 0
void displayTaskCode(void * parameter) {
    String currentMessage;
    for (;;) {
        if (xQueueReceive(messageQueue, &currentMessage, portMAX_DELAY) == pdTRUE) {
            showMessage("Displaying Msg:");
            delay(1000); // Brief display before actual message
            showMessage(currentMessage);
        }
    }
}

void setup() {
  Wire.begin(3, 2);
    // Initialize OLED and connect to WiFi
    initializeDisplay();
    connectToWiFi();

    // Create FreeRTOS queue and semaphore
    messageQueue = xQueueCreate(10, sizeof(String));
    displaySemaphore = xSemaphoreCreateMutex();

    // Create tasks on specific cores
    xTaskCreatePinnedToCore(
        messageListenerTaskCode, /* Task function */
        "Message Listener",      /* Name */
        10000,                   /* Stack size */
        NULL,                    /* Parameters */
        1,                       /* Priority */
        &messageListenerTask,    /* Task handle */
        1                        /* Core 1 */
    );

    xTaskCreatePinnedToCore(
        displayTaskCode,         /* Task function */
        "Display Task",          /* Name */
        10000,                   /* Stack size */
        NULL,                    /* Parameters */
        1,                       /* Priority */
        &displayTask,            /* Task handle */
        0                        /* Core 0 */
    );
}

void loop() {
    // Nothing needed in the main loop
}
