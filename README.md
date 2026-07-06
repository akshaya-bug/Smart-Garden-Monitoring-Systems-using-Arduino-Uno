# Smart-Garden-Monitoring-Systems-using-Arduino-Uno
A collection of **six Arduino Uno projects** focused on **Smart Garden Automation** using the **Soil Moisture Sensor**, **Raindrop Sensor**, **OLED Display**, **Active Buzzer**, **LEDs**, and **Push Button**.

These projects demonstrate real-time environmental monitoring, intelligent decision-making, weather alerts, and user-friendly dashboard interfaces for modern smart gardening applications.

---

# 📖 Project Overview

This repository contains six embedded systems projects developed using **Arduino Uno**. The projects monitor soil moisture and rainfall conditions, provide maintenance recommendations, generate alerts, and present information through an OLED display.

Each project builds upon the previous one, gradually introducing more advanced embedded programming concepts and sensor integration.

---

# 🛠 Components Used

* Arduino Uno
* Soil Moisture Sensor
* Raindrop Sensor Module
* SSD1306 I2C OLED Display (128×64)
* Active Buzzer
* Green LED
* Red LED
* Push Button
* 220Ω Resistors
* Breadboard
* Jumper Wires
* USB Cable

---

# 📂 Projects Included

---

## 🌱 Project 1 – Plant Water Alert System

### Objective

Monitor soil moisture and notify the user when watering is required.

### Features

* Reads live soil moisture percentage.
* Displays moisture level on the OLED.
* Classifies soil condition:

  * 🌱 Wet
  * 🌿 Normal
  * 🏜 Dry
* Displays **"WATER ME!"** when soil becomes dry.
* Activates the buzzer for dry soil.
* Horizontal moisture progress bar.

---

## 🌧 Project 2 – Smart Rain Detector

### Objective

Detect rainfall and warn the user.

### Features

* Reads raindrop sensor values.
* Displays rain level on the OLED.
* Classifies weather as:

  * ☀ Dry
  * 🌦 Drizzle
  * 🌧 Heavy Rain
* Displays **"CLOSE THE WINDOW!"**
* Activates the buzzer whenever rain is detected.
* OLED raindrop icon/animation.

---

## 🌿 Project 3 – Smart Garden Monitor

### Objective

Monitor soil moisture and rainfall together using a single dashboard.

### Features

* Displays:

  * Soil Moisture (%)
  * Rain Status
* Refreshes data every second.
* Sounds the buzzer when:

  * Soil is too dry
  * Heavy rain is detected
* Startup screen displaying **Smart Garden Monitor**.

---

## 💧 Project 4 – Automatic Watering Decision System

### Objective

Provide intelligent recommendations for plant maintenance based on soil and rainfall conditions.

### Decision Logic

| Soil Condition | Rain Status   | Recommendation        |
| -------------- | ------------- | --------------------- |
| Dry            | No Rain       | 💧 Water the Plant    |
| Dry            | Rain Detected | ⏳ Wait for Rain       |
| Good Moisture  | Any           | ✅ Soil Condition Good |

### Features

* Reads both sensors simultaneously.
* OLED recommendation display.
* Green LED indicates healthy soil.
* Red LED indicates action required.
* Real-time maintenance suggestions.

---

## 🏠 Project 5 – Smart Window Alert System

### Objective

Warn users when rain is detected.

### Features

* Continuous rain monitoring.

* OLED displays:

  * **RAIN DETECTED!**
  * **PLEASE CLOSE THE WINDOW**

* Continuous buzzer until rain stops.

* Automatically returns to normal mode.

* Displays total rain detection events.

---

## 📟 Project 6 – Multi-Page OLED Dashboard

### Objective

Create an interactive interface for viewing sensor data.

### OLED Pages

### Page 1

* Soil Moisture
* Moisture Percentage
* Soil Status

### Page 2

* Rain Detection
* Rain Percentage
* Rain Status

### Page 3

* Smart Garden Dashboard
* Combined sensor information
* Garden recommendation

### Features

* Push button page switching.
* Displays current page number.
* Automatic page rotation every 5 seconds.
* User-friendly dashboard layout.

---

# 🔌 Circuit Connections

## Common Connections

| Component               | Arduino Uno |
| ----------------------- | ----------- |
| Soil Moisture Sensor AO | A0          |
| Raindrop Sensor AO      | A1          |
| OLED SDA                | A4          |
| OLED SCL                | A5          |
| OLED VCC                | 5V          |
| OLED GND                | GND         |
| Push Button             | D2          |
| Green LED               | D6          |
| Red LED                 | D7          |
| Active Buzzer           | D8          |

---

# 💻 Programming Concepts

The projects demonstrate the following embedded system concepts:

* Analog sensor interfacing
* Soil moisture measurement
* Rain detection
* OLED graphics using SSD1306
* Push button interface
* LED indication
* Active buzzer control
* Threshold-based decision making
* Multi-page OLED menus
* Smart garden automation
* Real-time dashboard design
* Sensor calibration
* Serial Monitor debugging

---

# 📁 Repository Structure

Smart-Garden-Monitoring:
│
├── Project-1_Plant-Water-AlERT:
IMAGE1:
<img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/9dca9505-978c-4d48-b6b8-3a6962c84b7e" />
IMAGE2:
<img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/eb17a6b2-d67a-4863-adf8-0951c6bc72e4" />
IMAGE3:
<img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/a9f8e2bf-d503-48c4-9833-9cfc658fe4a3" />

├── Project-2_Smart-Rain-Detector:
IMAGE1:
<img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/4d038748-cbbd-4bd2-810d-55ccff5642bf" />
IMAGE2:
<img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/fd9f9ccd-3356-4ce7-a292-a0b4f725e3ca" />

├── Project-3_Smart-Garden-Monitor/
IMAGE1:
<img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/88dd5b85-800e-420f-b844-80d8d03ab3a2" />

├── Project-4_Automatic-Watering-Decision-System/
 IMAGE1:
 <img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/53c803d9-3f55-46dc-8669-756bd8217e79" />
 IMAGE2:
 <img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/8f63c919-54f2-4664-9277-a07554902c6e" />
│
├── Project-5_Smart-Window-Alert-System/
 IMAGE 1:
 <img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/1d2d4364-6910-4928-8f45-55cf1ef33e51" />
IMAGE2:
<img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/125fa89a-e0b1-4ab4-8dd7-3d9572052429" />
│
├── Project-6_Multi-Page-OLED-Dashboard/
 PAGE 1:
 <img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/680cf94a-e9a3-4ca4-bbaa-4fa3d3972252" />
 PAGE 2:
 <img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/480822d8-3b00-4731-955d-e7cb3109bee9" />
 PAGE 3:
<img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/cfd2f0ce-4401-4b35-a33b-5f908d0c3a59" />
 

# 🛠 Technologies Used

* Arduino Uno
* Embedded C (Arduino IDE)
* Soil Moisture Sensor
* Raindrop Sensor Module
* SSD1306 OLED Display
* Adafruit GFX Library
* Adafruit SSD1306 Library

---

# ⭐ Support

If you found these projects helpful, consider giving this repository a **⭐ Star** and feel free to **Fork** it for your own learning and experimentation.

Happy Coding! 🌱

