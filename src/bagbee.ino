#include <Wire.h>
#include <Adafruit_APDS9960.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <MPU6050.h>
#include <math.h>

constexpr uint8_t BUZZER_PIN = 25;
constexpr uint8_t SCREEN_WIDTH = 128;
constexpr uint8_t SCREEN_HEIGHT = 64;
constexpr uint8_t OLED_RESET = 255;

constexpr uint32_t OWNER_VERIFICATION_MS = 15000;
constexpr float MOTION_THRESHOLD = 0.45f;
constexpr float TAMPER_THRESHOLD = 1.20f;
constexpr float ALTITUDE_SPIKE_THRESHOLD = 1.50f;
constexpr float FILTER_ALPHA = 0.18f;

constexpr char BLE_SERVICE_UUID[] = "2bc6d896-0394-4689-bf7a-57fdf9e9da5c";
constexpr char BLE_CHARACTERISTIC_UUID[] = "f0f9a89a-2495-4cfe-8835-a77013f54768";

enum class AlarmState : uint8_t {
  Idle,
  Arming,
  Armed,
  VerificationWindow,
  Alarmed,
};

Adafruit_APDS9960 gesture;
Adafruit_BMP085 bmp;
MPU6050 mpu;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

BLECharacteristic *alertCharacteristic = nullptr;

AlarmState state = AlarmState::Idle;
float baselineAltitude = 0.0f;
float filteredMotion = 0.0f;
float baselineMagnitude = 0.0f;
uint32_t verificationStart = 0;

int16_t ax = 0, ay = 0, az = 0;
int16_t gx = 0, gy = 0, gz = 0;

const uint8_t kGesturePin[] = {
  APDS9960_DOWN,
  APDS9960_UP,
  APDS9960_LEFT,
  APDS9960_RIGHT,
};
constexpr size_t kGesturePinLength = sizeof(kGesturePin) / sizeof(kGesturePin[0]);
size_t gestureIndex = 0;

void updateDisplay(const String &line1, const String &line2 = "") {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.println(line1);
  if (!line2.isEmpty()) {
    display.println();
    display.println(line2);
  }
  display.display();
}

void startBLE() {
  BLEDevice::init("BagBee");
  BLEServer *server = BLEDevice::createServer();
  BLEService *service = server->createService(BLE_SERVICE_UUID);
  alertCharacteristic = service->createCharacteristic(BLE_CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ);
  alertCharacteristic->setValue("BAGBEE_IDLE");
  service->start();
  BLEAdvertising *advertising = BLEDevice::getAdvertising();
  advertising->addServiceUUID(BLE_SERVICE_UUID);
  advertising->start();
}

void notifyOwner(const char *message) {
  if (!alertCharacteristic) {
    return;
  }
  alertCharacteristic->setValue(message);
  alertCharacteristic->notify();
}

float vectorMagnitude(float x, float y, float z) {
  return sqrtf((x * x) + (y * y) + (z * z));
}

float readMotionMagnitude() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  const float normX = static_cast<float>(ax) / 16384.0f;
  const float normY = static_cast<float>(ay) / 16384.0f;
  const float normZ = static_cast<float>(az) / 16384.0f;
  return vectorMagnitude(normX, normY, normZ);
}

bool isSuspiciousMovement() {
  const float rawMagnitude = readMotionMagnitude();
  filteredMotion = (FILTER_ALPHA * rawMagnitude) + ((1.0f - FILTER_ALPHA) * filteredMotion);

  const float delta = fabsf(filteredMotion - baselineMagnitude);
  const float altitudeDelta = fabsf(bmp.readAltitude() - baselineAltitude);

  return (delta > MOTION_THRESHOLD) || (altitudeDelta > ALTITUDE_SPIKE_THRESHOLD);
}

bool isTampered() {
  const float rawMagnitude = readMotionMagnitude();
  return fabsf(rawMagnitude - baselineMagnitude) > TAMPER_THRESHOLD;
}

bool checkGesturePin() {
  if (!gesture.gestureAvailable()) {
    return false;
  }

  const uint8_t reading = gesture.readGesture();
  if (reading == 0) {
    return false;
  }

  if (reading == kGesturePin[gestureIndex]) {
    gestureIndex++;
    if (gestureIndex == kGesturePinLength) {
      gestureIndex = 0;
      return true;
    }
  } else {
    gestureIndex = 0;
  }

  return false;
}

void armSystem() {
  state = AlarmState::Armed;
  baselineAltitude = bmp.readAltitude();
  baselineMagnitude = readMotionMagnitude();
  filteredMotion = baselineMagnitude;
  notifyOwner("BAGBEE_ARMED");
  updateDisplay("System armed", "Monitoring");
}

void enterVerification() {
  state = AlarmState::VerificationWindow;
  verificationStart = millis();
  notifyOwner("BAGBEE_VERIFY");
  updateDisplay("Suspicious move", "Check phone now");
}

void triggerAlarm(const char *reason) {
  state = AlarmState::Alarmed;
  notifyOwner(reason);
  updateDisplay("ALARM ACTIVE", reason);
}

void clearAlarm() {
  noTone(BUZZER_PIN);
  state = AlarmState::Idle;
  notifyOwner("BAGBEE_IDLE");
  updateDisplay("Disarmed");
}

void setup() {
  Serial.begin(115200);
  Wire.begin();

  pinMode(BUZZER_PIN, OUTPUT);
  noTone(BUZZER_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true) {
      delay(1000);
    }
  }

  if (!gesture.begin()) {
    updateDisplay("APDS9960 fail");
    while (true) {
      delay(1000);
    }
  }
  gesture.enableGesture(true);

  if (!bmp.begin()) {
    updateDisplay("BMP085 fail");
    while (true) {
      delay(1000);
    }
  }

  mpu.initialize();
  startBLE();

  updateDisplay("BagBee ready", "Enter gesture PIN");
}

void loop() {
  switch (state) {
    case AlarmState::Idle:
      if (checkGesturePin()) {
        state = AlarmState::Arming;
        updateDisplay("Gesture accepted", "Arming...");
        delay(1200);
        armSystem();
      }
      break;

    case AlarmState::Arming:
      armSystem();
      break;

    case AlarmState::Armed:
      if (checkGesturePin()) {
        clearAlarm();
        break;
      }
      if (isTampered()) {
        triggerAlarm("BAGBEE_TAMPER");
        break;
      }
      if (isSuspiciousMovement()) {
        enterVerification();
      }
      break;

    case AlarmState::VerificationWindow:
      if (checkGesturePin()) {
        clearAlarm();
        break;
      }
      if (millis() - verificationStart >= OWNER_VERIFICATION_MS) {
        triggerAlarm("BAGBEE_ESCALATE");
      }
      break;

    case AlarmState::Alarmed:
      tone(BUZZER_PIN, 2400, 200);
      delay(200);
      tone(BUZZER_PIN, 1600, 200);
      delay(200);
      if (checkGesturePin()) {
        clearAlarm();
      }
      break;
  }

  delay(60);
}
