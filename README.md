# needy_plant

## Overview
This project is an automated houseplant watering system designed using a combination of analog electronics, digital sensors, and cloud connectivity. The system monitors soil moisture and environmental conditions, displays real-time data locally, publishes telemetry to Adafruit.io, and controls a relay-driven water pump for short controlled watering cycles. A custom dashboard enables both automatic and manual watering, along with integrated notifications.

---

## Features

### 🌱 Watering & Control
- **2N3906 Transistor Emitter Follower + Relay** used to safely switch a low-voltage water pump.
- **Automatic watering** when soil moisture drops below a threshold.
- Pump runs for **0.5 seconds** to prevent overwatering.
- **Manual watering** button integrated into the Adafruit.io dashboard.

### 📊 Sensors
- **BME280** for temperature, humidity, and pressure.
- **Seeed Soil Moisture Sensor** for soil water detection.

### 🖥 Local Display
- **OLED Display** shows real-time soil moisture and environmental readings.

### ☁️ Cloud Integration
- Publishes soil moisture and environmental data to **Adafruit.io**.
- Custom dashboard includes live charts, controls, and displays.

### 🔔 Notifications
- **Zapier SMS/Email alerts** for:
  - Low soil moisture
  - Successful watering events
  - Optional environmental threshold notifications

### 🪴 Physical Integration
- Custom or purchased structure to hold the plant, pump, sensors, and wiring.
- Fully integrated electronics for a clean and testable setup.

---

## Hardware Used
- Photon 2 (or board used in class)
- 2N3906 transistor  
- Relay module  
- Water pump  
- BME280 sensor  
- Seeed Soil Moisture Sensor  
- OLED I2C display  
- Tubing + water reservoir  
- Plant pot / enclosure  
- Breadboard or perfboard  
- Wires / jumper cables  

---

## System Operation
1. Sensors read soil moisture and environmental values.  
2. Data is displayed locally on the OLED.  
3. Data is published to multiple Adafruit.io feeds.  
4. If soil moisture drops below threshold:
   - Relay activates pump for **0.5 seconds**.
   - A Zapier SMS/email notification is triggered.
5. Manual watering can be activated through the dashboard button.
6. Dashboard displays trends, controls, and live values.

---

## Adafruit.io Dashboard Components
- Soil moisture gauge  
- Temperature, humidity, and pressure charts  
- Manual "Water Plant" button  
- Pump activity feed  
- Event feed for Zapier triggers  

---

## Wiring Summary
- **2N3906 → Relay** in emitter follower configuration  
- **Relay → Pump** for isolated switching  
- **I2C Bus:** BME280 + OLED display  
- **Analog Input:** Soil moisture sensor  
- **Digital Output:** Pump control pin  

*(Insert wiring diagram here if you generate one.)*

---

## Software / Firmware Overview
- Reads sensors at fixed intervals  
- Updates OLED with latest values  
- Publishes data to Adafruit.io (MQTT)  
- Subscribes to dashboard button feed for manual watering  
- Handles pump activation timing and safety  
- Implements thresholds and basic error handling  

---

## Video Demonstration
The final video includes:
- Live readings on OLED  
- Adafruit.io dashboard updates  
- Automatic watering demo  
- Manual watering button demo  
- Zapier notifications  
- Enclosure overview  

---

## Future Improvements
- Add reservoir water-level sensing  
- Improve enclosure design  
- Add RGB LED status indicators  
- Implement long-term soil moisture averaging for smarter watering  

---
