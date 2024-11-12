
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "relogo.h"
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


 
void setup() {
  Serial.begin(115200);
   Wire.begin(3, 2);                
 
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000); // Pause for 2 seconds
 
  // Clear the buffer.
  display.clearDisplay();
  
  // Draw bitmap on the screen
  display.drawBitmap(0, 0, MY_LOGO, 128, 64, 1);
  display.display();
  delay(4000);
  display.clearDisplay();
  display.drawBitmap(0, 0, reloadLogo, 128, 64, 1);
  display.display();
}
 
void loop() {
  
}
