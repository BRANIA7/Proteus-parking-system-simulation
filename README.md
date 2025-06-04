# 🚗 Automated Parking System Simulation (Proteus + Arduino)

This project simulates a smart parking system using Proteus 8 Professional and Arduino (ESP32-based). It includes both **Entry Toll** and **Exit Toll** processes integrated with sensors, simulated cameras, LCDs, and a number plate recognition system.

---

## 🛠 Technologies Used

- Proteus 8 Professional
- Arduino ESP32 (Simulated)
- Ultrasonic Sensors (HC-SR04)
- LCD Displays (16x2)
- Simulated Camera Terminals
- Optical Character Recognition (OCR) [conceptual]
- Serial Terminals for I/O Logs

---

## 🚦 System Overview

### Entry Toll Process

1. **Vehicle Detection**: An ultrasonic sensor detects vehicle presence.
2. **Obstacle Check**: If detected, the system waits 1 minute.
3. **Boot Process Check**: Verifies if the system is ready.
4. **Capture Photo**: A simulated camera takes an image of the vehicle's license plate.
5. **OCR Processing**: Converts the captured image into text.
6. **Plate Verification**: Determines if the text is a valid number plate.
7. **Database Storage**: Saves the number plate into a database.
8. **Slot Assignment**: Assigns a parking slot and displays it to the driver.
9. **Gate Control**: Opens the gate to allow entry.

### Exit Toll Process

1. **Address Prompt**: Requests the address of the exit toll booth.
2. **Exit Photo Capture**: Takes a picture at the exit point.
3. **OCR Conversion**: Converts the image into text.
4. **Receipt Handling**: Prints a receipt based on OCR results.

#### Alternative Flow A:

- Delay 30 seconds ➝ Detect vehicle ➝ Open gate ➝ Check if parking is free ➝ Print receipt.

#### Alternative Flow B (License Plate Verification):

- OCR ➝ Check database ➝ Plate match?
  - **No** ➝ Sound buzzer ➝ Prompt override ➝ Wait for attendant or open gate.
  - **Yes** ➝ Open gate.

---

## 📁 Files Included

- `Automated toll arduino.pdsprj` – Proteus project file
- `.png` – Schematic screenshot
- Source code (to be added or linked if applicable)

---

## 📌 Notes

- The OCR and camera functionality are **simulated** for proof of concept.
- This is a simulation-only project meant to demonstrate the logical flow and integration of hardware modules.

---

## ✅ Future Improvements

- Implement actual OCR with an image processing library.
- Add real-time communication between entry and exit modules.
- Integrate with a database (e.g., Firebase or MySQL) for persistent storage.

---

## 📜 License

MIT License

---

## 👨‍💻 Author

ABESIGA BRANIA
abesigabrania7@gmail.com
