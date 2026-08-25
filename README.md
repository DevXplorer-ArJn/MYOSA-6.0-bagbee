---
publishDate: 2026-08-25
title: BagBee - The Luggage Sentinel
excerpt: BagBee is a touchless, verified-alert luggage security node that detects suspicious movement, silently notifies the owner, and escalates only when the alert goes unverified.
image: bagbee-cover.jpg
tags:
  - iot
  - esp32
  - ble
  - luggage-security
  - motion-detection
  - embedded-systems
---

> Turning ordinary motion sensing into intelligent luggage protection.

---

## Acknowledgements

BagBee was developed as part of **MYOSA Event 6.0 — IEEE SENSORS 2026**, built using the **MYOSA Mini IoT Kit**.

We gratefully acknowledge the MYOSA platform for making practical, hands-on embedded sensing development possible, and we thank our faculty mentors for their guidance and encouragement throughout the project.

---

## Overview

### The Problem

On long-distance train journeys, passengers routinely leave their luggage unattended — while sleeping, resting, or stepping away from their seat. Existing protection options fall short in a few key ways:

* Mechanical locks and chains can only delay unauthorized access; they can't prevent or report it.
* Simple motion alarms trigger constantly from ordinary train vibration, training owners to ignore them.
* Instant alarms leave no room for the owner to check whether a movement was actually a threat before the alarm goes off.

BagBee reframes luggage security around this gap — moving away from a blunt motion-triggered alarm and toward an **intelligent, verified-alert security system**.

### The Solution

BagBee is a **touchless, verified-alert security node built for monitoring unattended luggage**. Rather than sounding an alarm the instant motion is sensed, it works through a layered decision flow:

```text
Movement Detection
        ↓
Motion Analysis
        ↓
Silent BLE Alert
        ↓
Owner Verification
        ↓
Alarm Escalation (if unverified)
```

This lets the system tell the difference between everyday environmental jostling and movement that actually looks like someone handling the bag.

### Who It Is For

BagBee is built for:

* Railway passengers
* Backpack and luggage users
* Anyone who needs portable, unattended asset monitoring

### How It Works

BagBee brings together several sensing and communication technologies:

* **APDS9960 Gesture Sensor** — for touchless arming and disarming
* **MPU6050 IMU** — for continuous motion monitoring
* **ESP32** — for edge-based processing and decision-making
* **BLE communication** — for silent alerts to the owner
* **BMP180**  —  Barometric pressure sensor for altitude sensing (to check bag lifting)
* **Piezo buzzer** — for final alarm escalation

**Key features:**

* Touchless gesture-based arming (no buttons, no touch)
* On-device motion analysis that filters out normal train vibration
* Silent BLE pre-alert before any audible alarm
* A verification window that gives the owner a chance to confirm intent
* Fully local decision-making on the ESP32 — no cloud dependency

The entire decision pipeline runs locally on the ESP32, so BagBee works reliably even without internet connectivity.

---

## Demo / Examples

### Images

<p align="center">
<img src="bagbee-cover.jpg" width="800"><br/>
<i>BagBee — touchless, verified-alert luggage security concept</i>
</p>

<p align="center">
<img src="prototype.jpg" width="800"><br/>
<i>BagBee prototype, built using the MYOSA Mini IoT Kit</i>
</p>

<p align="center">
<img src="gesture-arming.jpg" width="800"><br/>
<i>The touchless gesture sequence used to arm the system</i>
</p>

<p align="center">
<img src="ble-alert.jpg" width="800"><br/>
<i>Silent BLE pre-alert received on the owner's smartphone</i>
</p>

<p align="center">
<img src="alarm-demo.jpg" width="800"><br/>
<i>Alarm escalation after an unverified, suspicious movement</i>
</p>

### Videos

<video controls width="100%">
<source src="bagbee-demo.mp4" type="video/mp4">
</video>

---

## Features (Detailed)

### 1. Touchless Gesture-Based Security PIN

BagBee uses the **APDS9960 Gesture & Proximity Sensor** for fully touchless interaction. A predefined, multi-step gesture sequence acts as a security PIN for arming and disarming the device, giving users:

* Contactless operation
* Fewer accidental activations
* Better resistance to casual tampering

### 2. Intelligent Motion Monitoring

The **MPU6050 IMU** continuously tracks luggage movement while the system is armed, capturing:

* Movement intensity
* Orientation changes
* Spatial disturbances

The goal isn't to react to every twitch — it's to recognize patterns consistent with suspicious handling, such as dragging or lifting.

### 3. Vibration Filtering and False-Alarm Reduction

Train environments are full of constant, low-level vibration. BagBee applies motion-analysis techniques to filter out noise from:

* Railway vibration
* Minor environmental disturbances
* Small accidental knocks

This keeps alerts meaningful instead of routine — and worth the owner's attention.

### 4. Silent BLE Pre-Alert

When suspicious movement is detected, BagBee doesn't sound an alarm right away. It first sends a **silent Bluetooth Low Energy (BLE)** notification to the owner's smartphone, giving them the first chance to respond before anything becomes audible.

### 5. Owner Verification Window

Once alerted, the owner has a short window to verify what happened:

* **Intentional movement** → the alert is dismissed
* **No response** → the system escalates automatically

```text
Detection → Notification → Verification → Escalation
```

### 6. Multi-Stage Alarm Escalation

If a suspicious movement goes unverified, BagBee moves to its final warning stage:

* Piezo buzzer alarm
* Local OLED warning display

This ensures unattended, unverified movement never goes unanswered.

### 7. Tamper Detection

Beyond monitoring the luggage itself, BagBee has a separate detection path for tampering with the device while it's armed — covering both:

* Suspicious luggage movement
* Attempts to interfere with the security node directly

### 8. Edge-Based Processing

Every major decision happens locally on the ESP32:

* Gesture recognition
* Motion analysis
* Alert decision logic
* BLE communication
* Alarm escalation

This makes BagBee genuinely portable — no continuous internet connection required.

---

## Usage Instructions

1. Assemble the MYOSA Mini IoT Kit components along with the required sensors and buzzer.
2. Upload the firmware:

```plaintext
src/bagbee.ino
```

3. Power on the device.
4. Perform the gesture PIN sequence to arm BagBee.
5. Place the device with your luggage.
6. When suspicious movement occurs:
   * The ESP32 analyzes the motion on-device.
   * A silent BLE notification is sent to your smartphone.
7. Verify whether the movement was intentional.
8. If no verification is received in time, the system escalates to the audible alarm.

---

## Tech Stack

**Hardware**

* **ESP32** — Microcontroller
* **APDS9960** — Gesture & Proximity Sensor
* **MPU6050** — IMU Sensor
* **SSD1306** — OLED Display
* **BMP180**  —  Barometric pressure sensor
* **Piezo Buzzer**
* **3.7V LiPo Battery**

**Software**

* Arduino IDE / ESP32 Framework
* Embedded C++
* Bluetooth Low Energy (BLE)
* Sensor processing algorithms
* State-machine based decision logic

---

## Requirements / Installation

**Hardware Requirements**

* MYOSA Mini IoT Kit
* ESP32 board
* APDS9960 Gesture Sensor
* MPU6050 IMU Sensor
* SSD1306 OLED Display
* BMP180  —  Barometric pressure sensor
* Piezo Buzzer
* 3.7V LiPo Battery with charging protection
* Smartphone with BLE support

**Software Requirements**

* Arduino IDE 2.x or a compatible ESP32 development environment
* ESP32 board package
* Required sensor and display libraries

**Installation**

```bash
# Arduino IDE workflow
1. Install the ESP32 board package
2. Install the required libraries
3. Open src/bagbee.ino
4. Select your ESP32 board
5. Upload the firmware
```

---

## File Structure

```text
MYOSA-6.0-bagbee/
├── bagbee.md
├── README.md
├── LICENSE
├── bagbee-cover.jpg
├── prototype.jpg
├── gesture-arming.jpg
├── ble-alert.jpg
├── alarm-demo.jpg
├── bagbee-demo.mp4
└── src/
    └── bagbee.ino
```

---

## License

This project is released under the **MIT License**. See `LICENSE` for full terms.

---

## Contribution Notes

Planned improvements for BagBee include:

* Improving motion-classification accuracy across different travel environments
* Optimizing battery consumption for longer standby operation
* Refining the smartphone-side verification experience
* Designing a compact enclosure suited to real luggage integration

BagBee was built as a hands-on exploration of edge sensing, embedded intelligence, and verified-alert security design using the MYOSA Mini IoT Kit.
