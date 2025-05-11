#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 /*OLED screen width in pixels*/
#define SCREEN_HEIGHT 64 /*OLED screen height in pixels*/
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
void setup() {
  Serial.begin(115200);  /*Baud rate for Serial Communication*/

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // I2C Address 0x3C for 128x64 OLED screen
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);  /*delay of 2 sec*/
  display.clearDisplay();  /*clears the display*/

  display.setTextSize(1);  /*text size 1*/
  display.setTextColor(WHITE); /*text color WHITE*/
  display.setCursor(0, 10);  /*X and Y coordinates on OLED display screen*/
  display.println("Linuxhint.com");  /*Prints text with size 1*/
  display.display(); /*display on OLED screen*/
  display.setTextSize(2);  /*Text size 2 defined*/
  display.setTextColor(WHITE); /*Text color white*/
  display.setCursor(0, 20);  /*Position of text on OLED screen*/
  display.println("OLED");   /*Display text with size 2*/
  display.display();  /*Function to display text on OLED*/

  display.setTextSize(3);  /*Text size 3*/
  display.setTextColor(WHITE); /*Text color white*/
  display.setCursor(0, 40); /*Text position on OLED screen*/

  display.println("ESP32");  /*Display text on OLED*/
  display.display();  /*Function to Display text*/
  delay(500);  /*Delay of 0.5 sec*/
}
void loop() {
}
