# 🧠 Robie Jr. – Polished Version (Week 5)

This version of Robie Jr. includes **fully refactored code**, **LCD feedback**, a **buzzer**, and **improved power handling**.

---

## ✅ Features

- 🚀 Clean & modular Arduino code
- 🧠 Smart turning with servo scan
- 🧱 Obstacle avoidance
- 🗨️ LCD screen displays current action
- 📢 Buzzer beeps based on obstacle distance
- 🔋 Dual 9V battery support for motor + logic
- ⚡ LCD glitch fixed (buzzer/servo timer conflict resolved)

---

## 🚦 Wiring (Arduino Uno)

| Component        | Pin(s)        |
|------------------|---------------|
| Motor A (L293D)  | 9, 8, ENA: 6  |
| Motor B (L293D)  | 4, 3, ENB: 5  |
| Servo            | D7            |
| Ultrasonic Trig  | D12           |
| Ultrasonic Echo  | D11           |
| Buzzer           | D2            |
| LCD1602 (Parallel) | A0–A5        |

---

## 📝 Notes

- Servo + tone() libraries can interfere with timers. Resolved by moving buzzer to **pin 2**
- LCD glitch was caused by unstable USB power. Solved by using **dual 9V batteries**
- Code uses `lcdStatus()` with string tracking to reduce unnecessary refreshes

---

## 📸 Preview

![Robie Jr.](./images/robiejr.jpg)

---

## 🔧 Improvements Planned

- 👀 LED eyes while moving
- 🎭 Idle servo scan animation
- 💬 Custom startup message

---

## 🚀 How to Run

1. Open `robie_jr-polished.ino` in the Arduino IDE
2. Upload to Arduino Uno
3. Power Arduino with 9V battery
4. Power L293D motor supply with second 9V battery
