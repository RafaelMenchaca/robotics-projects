# 🤖 Robie Jr. – v1 (Week 4)

This was the **first functional version** of Robie Jr., an autonomous obstacle-avoiding robot built using Arduino and basic motor/sensor logic.

---

## 🔧 Features

- Moves forward automatically
- Uses ultrasonic sensor to detect obstacles
- Stops, reverses, and turns based on distance
- Scans with a servo for smarter decisions
- LCD displays current movement
- LED "eye" glows while moving
- Clean, smooth 90-degree turning

---

## ⚙️ Hardware

- Arduino Uno
- 2x DC Gear Motors + Chassis
- L293D Motor Driver
- Ultrasonic Sensor (HC-SR04)
- Servo Motor (for scanning)
- LCD 1602 (parallel)
- LED (eye indicator on pin 13)
- Buzzer (optional for testing)
- Powered by 9V batteries

---

## 🚦 Wiring Summary

| Component        | Pin(s)        |
|------------------|---------------|
| Motor A (L293D)  | 9, 8, ENA: 6  |
| Motor B (L293D)  | 4, 3, ENB: 5  |
| Servo            | D7            |
| Ultrasonic Trig  | D12           |
| Ultrasonic Echo  | D11           |
| LCD1602 (Parallel) | A0–A5        |
| Eye LED          | D13           |

---

## 📹 Behavior

Robie Jr. moves forward, and when it detects an object within ~15 cm, it:
1. Stops
2. Reverses
3. Scans both directions with servo
4. Turns toward the clearer path
5. Continues forward

The LCD displays Robie's status like "Moving Forward" or "Turning Left", and the LED eye lights up while driving forward.
