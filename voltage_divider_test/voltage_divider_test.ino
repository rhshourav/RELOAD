// MOVE FILE: This file should be moved to 'MAIN_ESP32C3/Project reload/main_controller/voltage_divider_test/voltage_divider_test.ino' for independent compilation.
// Voltage Divider Test for ESP32C3
// Measures voltage using a voltage divider on pin 0
// Adjust R1 and R2 as per your circuit

#define VOLTAGE_PIN 0  // ADC2: Pin 0 (adjust as needed)
#define VOLTAGE_PIN2 1 // ADC1
#define VOlTAGE_PIN3 4 //ADC3

// Voltage divider resistor values (in ohms)
const float R1 = 8342.0; // Top resistor (8.342k measured)
const float R2 = 2190.0; // Bottom resistor (2.19k)
const float R3 = 8640.0; // Top resistor (8.640k)
const float R4 = 2190.0; // Bottom resistor (2.19k)
const float R5 = 7060.0; // Top resistor (7.060k)
const float R6 = 787.0;  // Bottom resistor (787 ohm)

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
  display.print("R3: "); display.print(R3 / 1000.0, 2); display.println("k");
  display.print("R4: "); display.print(R4 / 1000.0, 2); display.println("k");
  display.print("R5: "); display.print(R5 / 1000.0, 2); display.println("k");
  display.print("R6: "); display.print(R6 / 1000.0, 2); display.println("k");
  display.display();
  delay(6000);
}

void loop() {
  int adcValue = analogRead(VOLTAGE_PIN);
  float vOut = (adcValue / ADC_MAX) * VREF;
  float vIn = vOut * (R1 + R2) / R2;

  int  adcValue1 = analogRead(VOLTAGE_PIN2);
  float vOut1 = (adcValue1 / ADC_MAX) * VREF;
  float vIn1 = vOut1 * (R3 + R4) / R4;

  int  adcValue2 = analogRead(VOlTAGE_PIN3);
  float vOut2 = (adcValue2 / ADC_MAX) * VREF;
  float vIn2 = vOut2 * (R5 + R6) / R6;


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
  display.print("ADC1: "); display.print(adcValue);display.print("Vout1: "); display.print(vOut, 2); display.println("V");
  display.print("ADC2: "); display.print(adcValue1);display.print("Vout2: "); display.print(vOut1, 2); display.println("V");
  display.print("ADC3: "); display.print(adcValue2);display.print("Vout3: "); display.print(vOut2, 2); display.println("V");
  display.print("Vin1:  "); display.print(vIn, 2); display.println("V");
  display.print("Vin2:  "); display.print(vIn1, 2); display.println("V");
  display.print("Vin2:  "); display.print(vIn2, 2); display.println("V");

  display.display();

  delay(1000);
} 