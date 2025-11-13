# 🚦 Smart Traffic Light System using ESP32

A real-time smart traffic control system that dynamically manages traffic lights based on **vehicle speed**, **pedestrian requests**, and **emergency overrides**.

---

## 🧩 Features
- Measures vehicle speed using **ultrasonic sensors (NewPing library)**.
- Dynamically switches traffic lights:
  - **Fast vehicle → Red light**
  - **Medium-speed vehicle → Green light**
  - **Slow vehicle → Red light**
- **Pedestrian crossing** trigger using push button.
- **Emergency override** sequence for priority vehicles.
- Modular design for future integration with **AI, Computer Vision, and IoT**.

---

## ⚙️ Hardware Components
| Component | Quantity | Description |
|------------|-----------|-------------|
| ESP32 Dev Board | 1 | Microcontroller |
| Ultrasonic Sensor (HC-SR04) | 2 | Speed measurement |
| LEDs (Red, Yellow, Green) | 3 | Traffic light indicators |
| Push Button | 1 | Pedestrian crossing |
| Switch | 1 | Emergency override |
| Breadboard + Jumper Wires | — | Circuit connections |

---

## 🧠 Working Principle
1. **Vehicle Detection:**  
   Ultrasonic sensors detect when a vehicle passes the first and second sensors, calculating travel time.
2. **Speed Evaluation:**  
   The time difference between sensor triggers determines whether the vehicle is fast, medium, or slow.
3. **Traffic Control:**  
   Based on speed, LEDs switch accordingly.
4. **Pedestrian & Emergency Override:**  
   - Pedestrian button requests a safe crossing.
   - Emergency switch activates a priority sequence (Red → Yellow → Green).

---
### 🧠 Flowchart
![Flowchart](flowchart.jpeg)
---
### 🛠️ Physical Prototype Setup
![Prototype Setup](prototype_setup.jpeg)
---
## 🧾 Code Overview
The main functions:
- `handleEmergencySequence()` – Controls emergency override sequence.
- `controlTrafficBasedonSpeed()` – Dynamically controls lights using sensor data.
- `measureTravelTime()` – Calculates travel time between sensors.
- `resetAllLights()` – Turns off all LEDs.

---

## 🔮 Future Scope
- Multi-lane & intersection coordination
- Real-time IoT data monitoring
- AI-based vehicle detection (computer vision)
- Blockchain for secure traffic data logging

---

## 📸 Prototype
*(Add your circuit and demo images here)*

---

## 🧑‍💻 Author
**Yokesh Ganesh Babu**  
B.Tech VLSI Design and Technology  
---

## 🪪 License
This project is licensed under the [MIT License](LICENSE).
