---

publishDate: 2026-08-23
title: BagBee - A Touchless, Verified-Alert Security Node for Unattended Luggage on Long-Distance Train Journeys
excerpt: BagBee is a portable luggage-security system that combines touchless gesture arming, motion-based theft detection, silent BLE alerts, owner verification, and staged alarm escalation using the MYOSA Mini IoT Kit.
image: bagbee-cover.jpg
tags:

* IoT
* ESP32
* Security

---

> *Don't just detect movement. Verify it.*

---

## Acknowledgements

BagBee was developed as part of **MYOSA Event 6.0 - IEEE SENSORS 2026** using the MYOSA Mini IoT Kit.

We would like to acknowledge the MYOSA platform for providing an embedded sensing environment that allowed us to explore a practical edge-based IoT security application. We also thank our faculty mentor, **Dr. Lekshmi Mohan**, for her guidance and support throughout the development of the project.

---

## Overview

BagBee is a **touchless, verified-alert security node designed for unattended luggage during long-distance train journeys**.

The idea comes from a familiar situation faced by railway passengers: having to sleep or rest while their luggage remains unattended under or beside their berth. Conventional solutions such as chains, locks, and basic motion alarms can provide deterrence, but they do not necessarily distinguish between genuine unauthorized movement and the continuous vibration experienced during a train journey.

A simple motion alarm can therefore create frequent false alarms. At the same time, immediately triggering a loud alarm does not give the owner an opportunity to determine whether the movement was intentional.

BagBee approaches this problem differently.

Instead of treating every movement as a theft event, the system follows a **layered detection-and-verification pipeline**. A touchless gesture sequence is used as a security PIN for arming and disarming. Once armed, an MPU6050 continuously monitors the luggage's motion. The ESP32 processes this information locally and applies filtering intended to distinguish normal train vibration from sustained movement associated with dragging or lifting.

When suspicious movement is detected, BagBee does **not immediately sound the alarm**.

It first sends a silent pre-alert to the owner's smartphone using Bluetooth Low Energy. The owner is given a short verification window. If the movement was intentional, the event can be silently dismissed. If there is no response, the system escalates to an audible alarm.

This transforms the traditional:

**Movement → Alarm**

model into:

**Movement → Detection → Silent Alert → Verification → Escalation**

### Key Features

* Touchless multi-step gesture-based security PIN.
* Continuous luggage motion monitoring using the MPU6050.
* Adaptive filtering for distinguishing train vibration from suspicious movement.
* Silent Bluetooth Low Energy pre-alert to the owner's smartphone.
* Short owner verification window before audible escalation.
* Tamper-distinct alarm path.
* Local edge processing using the ESP32.
* OLED-based setup and warning feedback.
* Portable battery-powered operation.

---

## Demo / Examples

### Images

All images are placed in the same folder as this Markdown file, as required by the MYOSA submission guidelines.

<p align="center">
<img src="bagbee-cover.jpg" width="800"><br/>
<i>BagBee - Touchless, verified-alert security node for unattended luggage</i>
</p>

<p align="center">
<img src="prototype.jpg" width="800"><br/>
<i>BagBee prototype built around the MYOSA Mini IoT Kit</i>
</p>

<p align="center">
<img src="gesture-arming.jpg" width="800"><br/>
<i>Touchless gesture sequence used to arm the BagBee security node</i>
</p>

<p align="center">
<img src="ble-alert.jpg" width="800"><br/>
<i>Silent BLE pre-alert received by the owner's smartphone</i>
</p>

<p align="center">
<img src="alarm-demo.jpg" width="800"><br/>
<i>Final alarm escalation following an unverified suspicious movement</i>
</p>

### Videos

The complete BagBee demonstration is provided as a local MP4 file in the same folder as this Markdown file. YouTube links are not used, in accordance with the MYOSA submission requirements.

<video controls width="100%">
<source src="bagbee-demo.mp4" type="video/mp4">
</video>

The demonstration follows four stages:

1. **Arming** - The presenter performs the correct gesture sequence and demonstrates an incorrect sequence failing to arm the device.
2. **Vibration Immunity** - The luggage is tapped or shaken to simulate ordinary train movement while the system remains silent.
3. **Simulated Theft** - The luggage is slowly dragged, causing the system to detect suspicious movement and send a silent BLE pre-alert.
4. **Escalation** - If the verification window expires without owner confirmation, the audible alarm and local warning indication are activated.

This sequence demonstrates the core security concept of BagBee: **detect first, notify silently, verify, and escalate only when necessary.**

---

## Features (Detailed)

### 1. Touchless Gesture-PIN Arming and Disarming

BagBee uses the **APDS9960 Gesture & Proximity Sensor** as a touchless security interface.

Rather than using a single gesture such as a simple wave, BagBee is designed around a specific ordered sequence of gestures. This sequence functions as a security PIN for the system.

This provides two important advantages:

* It reduces accidental arming or disarming.
* A person who encounters the device cannot casually disable it using a single common gesture.

During setup, the OLED provides visual feedback and an arming countdown. Once armed, the display can be powered down for stealth operation.

---

### 2. Continuous Motion Monitoring Using the MPU6050

The **MPU6050 IMU** forms the primary motion-sensing layer of BagBee.

When the system is armed, it establishes a baseline for the luggage's spatial state and continuously monitors changes in motion.

The system does not simply ask whether the luggage has moved. It analyses the characteristics of the movement before deciding whether it should be considered suspicious.

This is particularly important in railway environments, where continuous background vibration is unavoidable.

---

### 3. Adaptive Vibration Filtering

One of the central challenges of luggage security on trains is distinguishing normal environmental vibration from intentional luggage movement.

BagBee uses adaptive low-pass filtering as part of its motion-processing logic.

The intended distinction is between:

* High-frequency, low-amplitude vibration associated with normal train movement.
* Sustained, low-frequency horizontal drift associated with luggage being dragged or lifted.

This filtering layer allows the system to avoid treating every vibration as a theft event.

The objective is therefore not simply to make the sensor more sensitive, but to make the detection **more meaningful**.

---

### 4. Silent BLE Pre-Alert

When the motion-processing layer identifies suspicious movement, the ESP32 uses its built-in **Bluetooth Low Energy capability** to communicate with the owner's smartphone.

The first response is deliberately silent.

Instead of immediately activating the buzzer, BagBee sends a pre-alert to the owner.

This gives the owner an opportunity to respond before the system produces an audible warning.

The approach is particularly useful for the project's intended scenario because a single loud alarm may be ineffective if the owner is asleep or if the alarm is physically muffled.

---

### 5. Owner Verification Window

Following a suspicious movement event, BagBee provides a short verification window.

The owner is presented with a simple confirmation such as:

> **Was this you?**

If the movement was intentional, the owner can confirm it and silently disarm the system.

If the owner does not respond within the configured verification period, the system treats the event as unverified and proceeds to the escalation stage.

This creates a verification layer between sensing and alarming.

---

### 6. Multi-Stage Alarm Escalation

BagBee follows a staged response rather than activating the buzzer immediately.

The complete sequence is:

**Detection → Silent Notification → Verification → Alarm**

If the suspicious movement is confirmed as intentional, the system can stop the event without producing an audible alarm.

If there is no response, the **piezo buzzer** is activated as the final escalation mechanism. The OLED can also provide a local warning indication.

This layered response is one of the central ideas behind BagBee.

---

### 7. Tamper-Distinct Alarm Path

BagBee also considers a different type of security event: interference with the security node itself.

An attempt to open or remove the node while the system is armed, without the correct disarm gesture, follows a separate tamper-detection path.

This prevents the security logic from relying solely on luggage movement.

---

### 8. Edge-Based Security Processing

The **ESP32 acts as the central state-machine controller** for BagBee.

It continuously processes:

* Gesture input
* IMU data
* Motion filtering
* Detection decisions
* OLED feedback
* BLE communication
* Alarm escalation

The core filtering and decision-making logic runs locally on the device rather than depending on cloud connectivity.

This is particularly relevant for a moving train environment where network connectivity may be unreliable.

---

## Usage Instructions

### Hardware Setup

1. Connect the MYOSA Mini IoT Kit components required by BagBee.
2. Connect the additional piezo buzzer to the appropriate ESP32 GPIO.
3. Provide the system with the required portable power source.
4. Position the BagBee node securely with the luggage.
5. Ensure that the gesture sensor and IMU are able to operate correctly in the installed position.

### Arming

1. Power on the BagBee node.
2. Follow the displayed setup instructions.
3. Perform the configured multi-step gesture sequence.
4. Wait for the arming countdown.
5. Once armed, the system enters monitoring mode.

### Monitoring

While armed, BagBee continuously monitors the luggage using the MPU6050.

Normal train vibration is processed through the motion-filtering stage.

The system remains silent unless movement satisfies the configured suspicious-motion conditions.

### Suspicious Movement

When suspicious movement is detected:

1. The ESP32 registers the event.
2. A silent BLE pre-alert is sent to the owner's smartphone.
3. The verification window begins.
4. The audible alarm remains inactive during this stage.

### Verification

If the owner confirms that the movement was intentional, the system can be silently disarmed.

If no confirmation is received during the verification window, BagBee proceeds to the final escalation stage.

### Alarm Escalation

The piezo buzzer is activated and the OLED provides the local warning indication.

The system therefore completes the full:

**Detect → Notify → Verify → Escalate**

security pipeline.

---

## Tech Stack

### Hardware

* **MYOSA Mini IoT Kit**
* **ESP32** - Central controller and BLE communication
* **APDS9960 Gesture & Proximity Sensor** - Touchless security input
* **MPU6050 IMU** - Motion and spatial monitoring
* **SSD1306 OLED Display** - Local status and warning feedback
* **Piezo Buzzer** - Audible alarm actuator
* **3.7V LiPo Cell** - Portable power
* **Charging / Protection Circuit** - Battery management

### Firmware

* **C++**
* **Arduino / ESP32 Framework**
* Embedded state-machine architecture
* Local motion filtering and decision logic
* Bluetooth Low Energy communication

---

## Requirements / Installation

### Hardware Requirements

* MYOSA Mini IoT Kit
* ESP32 motherboard/core
* APDS9960 Gesture & Proximity Sensor
* MPU6050 IMU
* SSD1306 OLED
* Piezo buzzer
* 3.7V LiPo cell
* Basic charging and protection circuit
* Smartphone for BLE notification demonstration

### Software Requirements

* Arduino-compatible ESP32 development environment
* ESP32 board support
* Required sensor libraries for the APDS9960, MPU6050 and SSD1306
* BagBee embedded firmware

### Installation

1. Install the ESP32 board support in the Arduino development environment.
2. Install the required libraries for the sensors and OLED used by the project.
3. Open the BagBee firmware source code.
4. Select the appropriate ESP32 board and serial port.
5. Connect the MYOSA board to the computer.
6. Compile and upload the firmware.
7. Power the BagBee node.
8. Verify gesture sensing, motion monitoring, OLED feedback, BLE notification and alarm operation.

---

## File Structure

```text
/MYOSA-6.0-bagbee
├── README.md
├── LICENSE
├── bagbee.md
├── bagbee-cover.jpg
├── prototype.jpg
├── gesture-arming.jpg
├── ble-alert.jpg
├── alarm-demo.jpg
└── bagbee-demo.mp4
```

All project images and the demonstration video are stored in the same folder as `bagbee.md`, following the MYOSA file and media requirements.

---

## License

This project is released under the **MIT License**.

The `LICENSE` file included in this repository contains the applicable license terms.

---

## Contribution Notes

BagBee was developed as an MYOSA Event 6.0 project to demonstrate the use of an edge-based IoT platform for a practical personal-security application.

Future development can explore improvements to motion classification, detection threshold tuning, power optimization, smartphone notification handling, and physical integration of the security node into different types of luggage.

Contributions and improvements are welcome provided that they respect the project's originality and open-source requirements.

---
