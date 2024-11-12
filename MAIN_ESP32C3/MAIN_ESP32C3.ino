#include <Wire.h>          // Include the Wire library for I2C communication
#include <U8g2lib.h>       // Include the U8g2 library for OLED display control

// Initialize the display with U8g2 using custom I2C pins (2 for SCL, 3 for SDA)
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  Serial.begin(115200);              // Start serial communication at 9600 baud
  Serial.println("Starting I2C with custom pins SDA=3, SCL=2");

  Wire.begin(3, 2);                // Initialize I2C with SDA on pin 3 and SCL on pin 2
  u8g2.begin();                    // Initialize the display with U8g2
  
  Serial.println("Display initialized successfully.");
  // Display each byte in hex format on the OLED
  int x = 0; // Starting x position
  int y = 20; // Starting y position

  for (int i = 0; i < sizeof(myByteArray); i++) {
    // Format each byte as "0x" followed by two hex digits
    char hexBuffer[5];
    snprintf(hexBuffer, sizeof(hexBuffer), "0x%02X", myByteArray[i]);

    // Display the formatted byte on the OLED screen
    u8g2.drawStr(x, y, hexBuffer);

    // Update x position for next byte (adjust for spacing)
    x += 40;
    if (x >= 120) {  // Move to the next line if out of horizontal space
      x = 0;
      y += 12; // Move down by font height to the next row
    }
  }

  u8g2.sendBuffer();                // Render the buffer contents to the display

  delay(2000); // Display for 2 seconds before updating
}

void loop() {
  u8g2.clearBuffer();               // Clear the display buffer
  u8g2.setFont(u8g2_font_ncenB08_tr); // Optional: Set font if adding text

  // Draw a circle at coordinates (64, 32) with a radius of 20 pixels
  u8g2.drawCircle(64, 32, 20, U8G2_DRAW_ALL);
  u8g2.sendBuffer();                // Send the buffer to the display to render

  Serial.println("Circle drawn at (64, 32) with radius 20");

  delay(1000);                      // Delay to hold the circle on screen
}
