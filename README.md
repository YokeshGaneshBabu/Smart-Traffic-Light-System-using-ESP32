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

## 📂 Project Structure
Smart-Traffic-Light-System-ESP32/
├── code/SmartTrafficLight.ino
├── images/
│ ├── circuit_diagram.png
│ ├── prototype_setup.jpg
│ └── output_serial_log.png
└── README.md
