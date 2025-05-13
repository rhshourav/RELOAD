// MOVE FILE: This file should be moved to 'MAIN_ESP32C3/Project reload/main_controller/voltage_divider_test/voltage_divider_test.ino' for independent compilation.
// Voltage Divider Test for ESP32C3
// Measures voltage using a voltage divider on pin 0
// Adjust R1 and R2 as per your circuit

#define VOLTAGE_PIN 0  // ADC2: Pin 0 (adjust as needed)

// Voltage divider resistor values (in ohms)
const float R1 = 8332.0; // Top resistor (8.332k)
const float R2 = 2190.0; // Bottom resistor (2.19k)

// ESP32 ADC properties
const float ADC_MAX = 4095.0; // 12-bit ADC
const float VREF = 3.3;       // Reference voltage (V)

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Voltage Divider Test");
  Serial.print("R1: "); Serial.print(R1 / 1000.0, 3); Serial.println(" kOhm");
  Serial.print("R2: "); Serial.print(R2 / 1000.0, 3); Serial.println(" kOhm");

  Wire.begin(3, 2); // SDA=3, SCL=2 as in your main_controller.ino
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Voltage Divider Test");
  display.print("R1: "); display.print(R1 / 1000.0, 2); display.println("k");
  display.print("R2: "); display.print(R2 / 1000.0, 2); display.println("k");
  display.display();
  delay(2000);
}

void loop() {
  int adcValue = analogRead(VOLTAGE_PIN);
  float vOut = (adcValue / ADC_MAX) * VREF;
  float vIn = vOut * (R1 + R2) / R2;

  Serial.print("ADC Value: ");
  Serial.print(adcValue);
  Serial.print(" | Vout: ");
  Serial.print(vOut, 3);
  Serial.print(" V | Vin: ");
  Serial.print(vIn, 3);
  Serial.println(" V");

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Voltage Test");
  display.print("ADC: "); display.println(adcValue);
  display.print("Vout: "); display.print(vOut, 2); display.println("V");
  display.print("Vin:  "); display.print(vIn, 2); display.println("V");
  display.display();

  delay(1000);
} 