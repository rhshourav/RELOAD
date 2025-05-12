# Voltage Divider Test for ESP32C3

This project provides a simple test sketch for measuring voltage using a voltage divider and displaying the result on an OLED display with the ESP32C3.

## Purpose
- Measure a voltage higher than the ESP32C3's ADC range using a voltage divider.
- Display the measured voltage, ADC value, and calculated input voltage on an SSD1306 OLED display.
- Useful for battery monitoring, power supply testing, and learning about ADCs and voltage dividers.

## Hardware Required
- ESP32C3 development board
- SSD1306 128x64 OLED display (I2C)
- Two resistors for the voltage divider (see below)
- Wires and breadboard
- Voltmeter (for calibration)

## Circuit Diagram
```
(Vin) ----[ R1 ]----+----[ R2 ]---- GND
                   |
                 (ADC pin 0)
```
- **R1**: Connects Vin to the ADC pin
- **R2**: Connects ADC pin to GND
- The junction between R1 and R2 goes to ESP32C3 pin 0 (ADC2)

## Example Resistor Values
- R1 = 9.66 kΩ (measured value)
- R2 = 2.19 kΩ (measured value)
- Use a multimeter to measure your actual resistor values and update the code accordingly.

## OLED Wiring (I2C)
- **SDA**: GPIO 3
- **SCL**: GPIO 2
- **VCC**: 3.3V
- **GND**: GND

## How It Works
1. The ESP32C3 reads the analog voltage at pin 0.
2. The code calculates the voltage at the divider (Vout) and the original input voltage (Vin) using the formula:
   - `Vin = Vout * (R1 + R2) / R2`
3. The OLED displays:
   - ADC value
   - Vout (voltage at ADC pin)
   - Vin (calculated input voltage)

## Usage
1. Connect the circuit as described above.
2. Measure R1 and R2 with a multimeter and update their values in the code.
3. Open `voltage_divider_test.ino` in the Arduino IDE.
4. Select the correct board and port.
5. Upload the sketch to your ESP32C3.
6. The OLED will show live voltage readings.

## Calibration & Accuracy
- The ESP32C3 ADC and reference voltage (VREF) may not be perfectly accurate.
- If the displayed voltage does not match your voltmeter, apply a correction factor in the code:
  ```cpp
  float vIn = vOut * (R1 + R2) / R2;
  vIn = vIn * (ActualVoltage / MeasuredVoltage);
  ```
- Or adjust the `VREF` value in the code.

## Troubleshooting
- **Wrong voltage displayed:**
  - Double-check resistor values in code.
  - Calibrate using a known voltage and correction factor.
  - Ensure good connections and no loose wires.
- **OLED not displaying:**
  - Check I2C wiring and address (default is 0x3C).
  - Make sure the display is powered (3.3V).
- **Compilation errors:**
  - Only keep this `.ino` file in the folder when compiling (Arduino IDE compiles all `.ino` files in a folder together).

## License
MIT License 