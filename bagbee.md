---
publishDate: 2026-08-25
title: BagBee
excerpt: BagBee is a touchless, verified-alert luggage security node that detects suspicious movement, notifies the owner silently, and escalates only when unverified.
image: bagbee-cover.jpg
tags:
  - iot
  - esp32
  - security
  - luggage-protection
  - motion-detection
  - ble
---

> Turning ordinary motion sensing into intelligent luggage protection.

---

## Acknowledgements

BagBee was developed as part of **MYOSA Event 6.0 - IEEE SENSORS 2026** using the MYOSA Mini IoT Kit.

We acknowledge the MYOSA platform for enabling practical embedded sensing development and thank our faculty mentors for guidance during project development.

---

## Overview

BagBee is a **touchless, verified-alert security node for unattended luggage during long-distance train journeys**.

It solves a common travel problem: luggage often remains unattended while passengers sleep, rest, or use washrooms. Conventional chains/locks are inconvenient, while simple motion alarms frequently trigger false alerts due to train vibration.

BagBee uses a layered pipeline instead of immediate siren-first logic:

**Movement → Detection → Silent Alert → Verification → Escalation**

This makes alerts more meaningful by giving the owner a short verification window before audible alarm escalation.

**Who it is for:** long-distance rail passengers, sleeper-class travelers, and anyone needing portable unattended luggage monitoring.

**How it works (high level):**

* Gesture PIN arms/disarms the node.
* MPU6050-based motion sensing monitors luggage movement.
* Filtering suppresses normal vibration noise.
* ESP32 sends silent BLE pre-alert to owner.
* No timely owner verification triggers buzzer alarm.

---

## Demo / Examples

### Images

<p align="center">
<img src="bagbee-cover.jpg" width="800"><br/>
<i>BagBee touchless verified-alert luggage security concept</i>
</p>

<p align="center">
<img src="prototype.jpg" width="800"><br/>
<i>BagBee prototype built around the MYOSA Mini IoT Kit</i>
</p>

<p align="center">
<img src="gesture-arming.jpg" width="800"><br/>
<i>Touchless multi-step gesture sequence used for arming</i>
</p>

<p align="center">
<img src="ble-alert.jpg" width="800"><br/>
<i>Silent BLE pre-alert received by the owner's smartphone</i>
</p>

<p align="center">
<img src="alarm-demo.jpg" width="800"><br/>
<i>Audible escalation stage after unverified suspicious movement</i>
</p>

### Videos

<video controls width="100%">
<source src="/bagbee-demo.mp4" type="video/mp4">
</video>

---

## Features (Detailed)

### 1. Touchless Gesture-PIN Arming and Disarming

BagBee uses the **APDS9960 Gesture & Proximity Sensor** with an ordered multi-step gesture sequence that acts as a security PIN. This reduces accidental arming/disarming and resists casual interference.

### 2. Continuous Motion Monitoring Using MPU6050

The **MPU6050 IMU** continuously tracks luggage motion while armed, establishing baseline behavior and detecting deviations.

### 3. Adaptive Vibration Filtering

Filtering distinguishes normal high-frequency train vibration from sustained low-frequency drift (drag/lift behavior), reducing false alarms.

### 4. Silent BLE Pre-Alert

When suspicious movement is detected, ESP32 sends a **silent BLE alert** first, avoiding immediate public alarm.

### 5. Owner Verification Window

The owner gets a short response window to confirm intentional movement. Confirmed events can be silently dismissed.

### 6. Multi-Stage Alarm Escalation

If verification is not received in time, BagBee escalates to buzzer + local warning display.

### 7. Tamper-Distinct Alarm Path

Node-level tamper attempts while armed follow a separate escalation path, not only motion-based logic.

### 8. Edge-Based Processing on ESP32

Gesture, filtering, decision logic, BLE signaling, and escalation run locally on device for reliability in low-connectivity travel environments.

---

## Usage Instructions

1. Connect required MYOSA Mini IoT Kit components and piezo buzzer.
2. Upload firmware (`src/bagbee.ino`) to ESP32.
3. Power on the node and complete gesture-PIN arming.
4. Place the node with luggage and keep phone ready for BLE pre-alert.
5. On suspicious motion, verify intentional movement within the prompt window.
6. If ignored/unverified, the system escalates to audible alarm.

---

## Tech Stack

* **Hardware:** ESP32, APDS9960, MPU6050, SSD1306 OLED, Piezo buzzer, LiPo battery
* **Firmware:** C++ on Arduino/ESP32 framework
* **Communication:** Bluetooth Low Energy (BLE)
* **Architecture:** Embedded edge state-machine with local filtering and escalation logic

---

## Requirements / Installation

### Hardware Requirements

* MYOSA Mini IoT Kit
* ESP32 board
* APDS9960 Gesture & Proximity Sensor
* MPU6050 IMU
* SSD1306 OLED display
* Piezo buzzer
* 3.7V LiPo battery with charging/protection
* Smartphone for BLE verification demo

### Software Requirements

* Arduino IDE 2.x (or compatible ESP32 environment)
* ESP32 board package
* Sensor/OLED libraries used by firmware

### Installation

```bash
# Arduino IDE workflow
# 1) Install ESP32 board package
# 2) Install required libraries
# 3) Open src/bagbee.ino
# 4) Verify and upload to ESP32
```

---

## File Structure (Optional)

```text
MYOSA-6.0-bagbee/
├── bagbee.md
├── bagbee-demo.mp4
├── assets/
│   └── images/
│       └── bagbee/
│           ├── bagbee-cover.jpg
│           ├── prototype.jpg
│           ├── gesture-arming.jpg
│           ├── ble-alert.jpg
│           └── alarm-demo.jpg
├── src/
│   ├── bagbee.ino
│   └── README_SETUP.md
├── README.md
└── LICENSE
```

---

## License (Optional)

This project is released under the **MIT License**. See `LICENSE` for full terms.

---

## Contribution Notes (Optional)

BagBee was built for MYOSA Event 6.0 as a practical personal-security concept using edge sensing and staged alert verification.

Suggested future contributions:

* Improve motion classification across diverse travel scenarios.
* Optimize battery usage for longer runtime.
* Enhance smartphone-side UX for faster verification.
* Improve enclosure design for robust luggage integration.
