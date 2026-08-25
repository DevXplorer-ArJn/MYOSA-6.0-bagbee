# BagBee

### A Touchless, Verified-Alert Security Node for Unattended Luggage on Long-Distance Train Journeys

> **Don't just detect movement. Verify it.**

BagBee is a portable luggage-security system designed to address a familiar problem faced by passengers on long-distance train journeys: **the uncertainty of leaving luggage unattended while resting or sleeping.**

Instead of relying on a simple motion-triggered alarm, BagBee uses a **layered, verified-alert approach**. It combines gesture-based security, motion analysis, silent Bluetooth notification, and staged alarm escalation to distinguish normal train vibrations from suspicious luggage movement.

---

## The Problem

On long-distance train journeys, passengers often have to sleep while their luggage remains unattended under or beside their berth.

Traditional solutions such as chains, locks, or basic motion alarms have limitations:

* Mechanical locks can only delay unauthorized movement.
* Simple motion alarms may trigger due to normal train vibrations.
* A loud alarm provides no opportunity for the owner to verify whether the movement was intentional.
* An audible alarm can potentially be muffled before the owner reacts.

**BagBee approaches luggage security as a verified-alert pipeline rather than a single alarm trigger.**

---

## Our Approach

BagBee continuously monitors the luggage while remaining unobtrusive.

The system follows a layered sequence:

```text
          ┌─────────────────────┐
          │   Gesture-Based     │
          │     Arming          │
          └──────────┬──────────┘
                     ↓
          ┌─────────────────────┐
          │  Motion Monitoring  │
          │      via IMU        │
          └──────────┬──────────┘
                     ↓
          ┌─────────────────────┐
          │ Suspicious Movement │
          │      Detected        │
          └──────────┬──────────┘
                     ↓
          ┌─────────────────────┐
          │   Silent BLE Alert  │
          │   to Owner's Phone  │
          └──────────┬──────────┘
                     ↓
          ┌─────────────────────┐
          │  Verification       │
          │     Window          │
          └───────┬─────┬───────┘
                  │     │
             Owner      No Response
             confirms        │
                  │          ↓
                  ↓    ┌───────────────┐
             Disarm     │ Alarm /       │
                        │ Escalation    │
                        └───────────────┘
```

This allows BagBee to respond differently to **normal environmental movement** and **potential theft**.

---

## Key Features

### Gesture-Based Security PIN

BagBee uses the **APDS9960 gesture sensor** for touchless arming and disarming.

Instead of a single gesture, a specific multi-step gesture sequence acts as a security PIN, reducing the possibility of accidental or casual disarming.

### Vibration vs. Theft Detection

The **MPU6050 IMU** continuously monitors the luggage's spatial movement.

BagBee applies filtering and motion analysis to distinguish:

* Normal train vibration
* Small environmental disturbances
* Sustained horizontal movement associated with dragging or lifting

The objective is to avoid treating every movement as a theft event.

### Silent BLE Pre-Alert

When suspicious movement is detected, BagBee first sends a **silent notification to the owner's smartphone using Bluetooth Low Energy (BLE)**.

The audible alarm is not immediately activated.

### Verification Window

The owner receives a verification prompt asking whether the detected movement was intentional.

If the owner confirms the movement, the system can be silently disarmed.

If there is no response within the verification window, BagBee proceeds to the next stage.

### Multi-Stage Alarm Escalation

If suspicious movement remains unverified, the system escalates to an audible alarm using a **piezo buzzer** and local warning indication.

This creates a progression from:

**Detection → Notification → Verification → Escalation**

### Tamper Detection

BagBee also provides a separate escalation path for unauthorized attempts to interfere with the security node while it is armed.

---

## Hardware

BagBee is built around the **MYOSA Mini IoT Kit** and uses its core components for distinct functions.

| Component             | Role                                            |
| --------------------- | ----------------------------------------------- |
| **ESP32**             | Central controller and state-machine processing |
| **APDS9960**          | Touchless gesture-based arming/disarming        |
| **MPU6050**           | Motion and spatial monitoring                   |
| **SSD1306 OLED**      | Local status and warning display                |
| **ESP32 BLE**         | Silent communication with owner's phone         |
| **Piezo Buzzer**      | Final audible alarm                             |
| **3.7V LiPo Battery** | Portable power source                           |

---

## System Architecture

BagBee performs its core decision-making locally on the ESP32.

```text
                 ┌───────────────────┐
                 │   APDS9960        │
                 │ Gesture Sensor    │
                 └─────────┬─────────┘
                           │
                           ↓
┌───────────────┐   ┌───────────────────┐   ┌────────────────┐
│   MPU6050     │──→│      ESP32        │──→│    SSD1306     │
│     IMU       │   │  Decision Logic   │   │     OLED       │
└───────────────┘   └─────────┬─────────┘   └────────────────┘
                              │
                    ┌─────────┴─────────┐
                    ↓                   ↓
             ┌─────────────┐     ┌──────────────┐
             │    BLE      │     │ Piezo Buzzer │
             │ Notification│     │   Alarm      │
             └─────────────┘     └──────────────┘
```

The filtering, gesture logic, and escalation state machine are designed to run **on-device**, without depending on cloud connectivity.

---

##  Intended Application

BagBee is primarily designed for:

* Long-distance train journeys
* Sleeper-class travel
* Backpack and luggage security
* Situations where luggage must remain unattended
* Portable, battery-powered personal security

The concept can also serve as a foundation for other portable asset-monitoring applications.

---

## Demonstration

The planned demonstration showcases the complete security pipeline:

### 1. Arming

The presenter performs the correct gesture sequence.

The OLED provides the arming feedback before the system enters stealth monitoring mode.

### 2. Vibration Immunity

The luggage is tapped or shaken to simulate normal train movement.

BagBee should remain silent rather than immediately triggering an alarm.

### 3. Simulated Theft

The luggage is slowly dragged away.

BagBee detects the suspicious movement and sends a silent BLE notification to the owner's phone.

### 4. Escalation

If the owner does not respond within the verification window, BagBee activates the final alarm stage.

This demonstrates the complete:

> **Gesture → Detection → Silent Alert → Verification → Escalation**

pipeline.

---

## Technology Stack

* **ESP32**
* **Arduino / ESP32 Framework**
* **C++**
* **APDS9960 Gesture & Proximity Sensor**
* **MPU6050 IMU**
* **SSD1306 OLED**
* **Bluetooth Low Energy (BLE)**
* **Piezo Buzzer**
* **3.7V LiPo Battery**

---

##  Repository Structure

```text
MYOSA-6.0-bagbee/
│
├── README.md
├── LICENSE
├── bagbee.md
│
├── bagbee-cover.jpg
├── prototype.jpg
├── gesture-arming.jpg
├── ble-alert.jpg
├── alarm-demo.jpg
│
├── bagbee-demo.mp4
│
└── src/
    └── bagbee.ino
```

The detailed MYOSA project documentation, demonstration media, usage instructions, and technical information are provided in **`bagbee.md`**.

---

##  Team

### BagBee — MYOSA Event 6.0

**Arjun S Nair**
3rd Year, B.Tech EEE
College of Engineering Trivandrum

**Nivin Ajith**
3rd Year, B.Tech EEE
College of Engineering Trivandrum

**A Adithya**
3rd Year, B.Tech EEE
College of Engineering Trivandrum

### Faculty Mentor

**Dr. Lekshmi Mohan**
Department of Electrical and Electronics Engineering
College of Engineering Trivandrum

---

## Vision

BagBee explores how a small edge-computing platform can transform a simple motion alarm into a **context-aware, verified security system**.

Rather than reacting to every movement, the system attempts to understand the difference between **normal environmental motion and suspicious movement**, while giving the owner an opportunity to verify an alert before escalating it.

> **BagBee — Detect. Verify. Protect.**

---

## License

This project is released under the **MIT License**.

See [`LICENSE`](LICENSE) for details.

---

##  MYOSA Event 6.0

Developed as a project for **MYOSA Event 6.0 — IEEE SENSORS 2026**.

The project utilizes the MYOSA Mini IoT Kit as an edge-sensing platform for a real-world personal security application.
