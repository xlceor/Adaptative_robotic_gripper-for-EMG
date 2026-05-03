# PROJECT KHYMERA

## Modular Robotic Prosthetic System | Functional, Scalable, Real

---

## 🚀 TL;DR

A low-cost modular robotic prosthetic system built with real hardware, real iteration, and real-world constraints.

- Dual-servo optimized gripper  
- Fully functional prototype (V0 → V2)  
- Designed for future EMG control  
- Built with 3D printing + embedded systems  

---

## 🎥 Live Demonstration

<img width="426" height="240" alt="0503 (1)(1)" src="https://github.com/user-attachments/assets/0723a297-9c53-4c58-bc31-9306177bcf14" />


This is not a concept.

This is a working system:
- Real movement  
- Real grip  
- Real control  

---

## 🧠 Overview

Project KHYMERA is a modular robotic prosthetic system designed to challenge the traditional approach to upper-limb prosthetics.

Instead of replicating the human hand, this project focuses on:

- Mechanical efficiency  
- Modularity  
- Accessibility  
- Scalability toward myoelectric control  

The result is a functional robotic gripper system built through iterative engineering, not theoretical design.

---

## 🛠️ System Architecture

### ⚙️ Mechanical System

- Parallel gripper design  
- Four-bar linkage mechanism  
- Dual servo actuation  
- Geometry optimized for full range of motion  

---
### 💻 Control system

#### Control Layer
Handles smooth motion interpolation between target and current positions:
- Real-time servo control loop (~20 ms)
- Dual-servo synchronized movement

#### Communication Layer
Provides external control and monitoring:
- REST API endpoints (`/servo`, `/ping`, `/demo`)
- WiFi Access Point mode
- Server-Sent Events (SSE) for real-time streaming

#### Telemetry Layer
Streams system diagnostics to the UI:
- Simulated temperature, voltage, load, vibration, ADC
- Designed to emulate real sensor behavior

#### State Layer
Maintains and broadcasts system state:
- Target vs current angle tracking
- Real-time synchronization with UI

#### UI Integration
Designed for real-time dashboard interaction:
- Low-latency feedback via SSE
- Compatible with advanced HUD-style interfaces

### 🔩 Manufacturing

- 3D Printing (FDM):
  - PLA → structural components  
  - TPU → flexible gripping surfaces  
- Rapid prototyping workflow  

---

### 🔌 Electronics

- Arduino-based control  
- Servo motors (MG996R)  
- Power system:
  - Dual 18650 batteries  
  - DC-DC regulator (XL4016)  
- Capacitor-based stabilization  

---

## 📁 Repository Structure
/mechanical/   → CAD files (V0, V1, V2)
/firmware/     → Embedded control code

---

## 🚨 The Problem

Modern prosthetics face critical limitations:

- High cost → inaccessible to many users  
- Mechanical complexity  
- Limited adaptability  

Even open-source solutions often struggle with:

- Inefficient actuation  
- Poor force transmission  
- Overreliance on biomimicry  

---

## 💡 The Approach

KHYMERA proposes a shift in design philosophy:

**From biomimicry → functional modularity**

Instead of replicating the human hand, the system is designed as:

- A robotic gripper module  
- Mechanically efficient  
- Easy to manufacture  
- Ready for integration into larger systems  

---

## 🔁 Development Process

Built through iterative engineering:

| Version | Purpose | Result |
|--------|--------|--------|
| V0 | Validate mechanism | Functional proof of concept |
| V1 | Integrate actuation | Improved structure, limited motion |
| V2 | Optimize geometry | Full range of motion, stable operation |

### Key Improvements

- Enhanced motion transmission  
- Improved grip using TPU surfaces  
- Structural alignment refinements  

---

## 📊 Functional Capabilities

Validated through real-world testing:

- ✔ Stable opening and closing motion  
- ✔ Reliable object gripping  
- ✔ Adaptability to different object shapes  
- ✔ Improved friction via TPU contact surfaces  

---

## 🧪 Methodology

- Experimental + technological research approach  
- Iterative prototyping  
- Direct functional testing  
- Qualitative performance evaluation  

Follows a standard engineering loop:

**Design → Build → Test → Optimize**

---

## 🚀 Why This Project Matters

- Demonstrates real engineering execution  
- Focuses on accessibility and affordability  
- Bridges mechanics, electronics, and embedded systems  
- Designed under real-world constraints, not ideal conditions  

---

## 🧭 Future Work

- EMG signal acquisition (ESP32-S3)  
- Myoelectric control system  
- Force sensing integration  
- Closed-loop control  
- Full robotic arm system  
- Advanced materials and optimization  

---

## ⚡ Quick Start

1. 3D print components (PLA + TPU)  
2. Assemble mechanical structure  
3. Upload firmware to Arduino  
4. Power with regulated ~6.2V supply  

**Recommended:** basic experience with electronics and 3D printing  

---

## 👨‍💻 Author

Carlos Osorio  
Systems Builder | Robotics | Embedded Systems | Applied Engineering  

Focused on building systems that interact with the real world.

---

## ⚠️ Disclaimer

This project is an experimental prototype and is not intended for clinical use.
