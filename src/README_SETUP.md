# BagBee Firmware Setup (ESP32 + Arduino)

This folder contains the BagBee firmware sketch:

- `bagbee.ino`

## 1) Arduino IDE / Board Package

1. Install **Arduino IDE 2.x**.
2. Open **Preferences** and add this additional board manager URL:
   - `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
3. Go to **Tools → Board → Boards Manager**.
4. Install **esp32 by Espressif Systems**.
5. Select your board (for example, **ESP32 Dev Module**).

## 2) Required Libraries

Install the following libraries from **Library Manager**:

- `Adafruit APDS9960 Library`
- `MPU6050` (Electronic Cats or equivalent MPU6050 Arduino library)
- `Adafruit BMP085 Library`
- `Adafruit SSD1306`
- `Adafruit GFX Library`

The following are included with the ESP32 core and Arduino framework:

- `Wire`
- `BLEDevice` / `BLEServer` / `BLEUtils`

## 3) Wiring Assumptions

The default sketch assumes:

- I2C sensors (APDS9960, MPU6050, BMP085, SSD1306) are on the ESP32 I2C bus
- Buzzer pin is connected to **GPIO 25**

Adjust pin mapping in `bagbee.ino` if your hardware wiring differs.

## 4) Build & Upload

1. Connect the ESP32 board over USB.
2. Open `src/bagbee.ino` in Arduino IDE.
3. Select the correct port from **Tools → Port**.
4. Click **Verify** to compile.
5. Click **Upload** to flash firmware.

## 5) Runtime Flow

- Enter the configured gesture PIN to arm the device.
- System monitors motion/altitude and filters noise.
- Suspicious movement triggers BLE pre-alert and verification window.
- No owner verification escalates to buzzer alarm.
- Enter gesture PIN again to disarm.
