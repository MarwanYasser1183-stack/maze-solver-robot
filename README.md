# 🤖 Maze Solver Robot

> An Arduino-based autonomous robot that navigates through a maze using three ultrasonic sensors and the **left-hand rule** algorithm — always preferring to turn left, then go forward, then right, and finally turn around if all paths are blocked.

---

## 📋 Table of Contents

- [Overview](#overview)
- [Algorithm](#algorithm)
- [Features](#features)
- [Hardware Components](#hardware-components)
- [Pin Configuration](#pin-configuration)
- [How It Works](#how-it-works)
- [Installation & Upload](#installation--upload)
- [Required Libraries](#required-libraries)
- [Project Structure](#project-structure)
- [License](#license)

---

## Overview

This robot uses three HC-SR04 ultrasonic sensors (left, front, right) to detect walls and obstacles in real time. It applies the **left-hand rule** (also known as the left-wall following algorithm) to navigate through any simply-connected maze and find the exit. All decisions are printed to the Serial Monitor for debugging.

---

## Algorithm

The left-hand rule works by always keeping the left wall in contact:

```
┌─────────────────────────────────────┐
│         LEFT-HAND RULE LOGIC        │
├─────────────────────────────────────┤
│  1. Is LEFT clear?  → TURN LEFT     │
│  2. Is FRONT clear? → MOVE FORWARD  │
│  3. Is RIGHT clear? → TURN RIGHT    │
│  4. All blocked?    → TURN AROUND   │
└─────────────────────────────────────┘
```

This guarantees the robot will find the exit of any maze that has no isolated walls (simply-connected maze).

---

## Features

- **3-sensor obstacle detection** — left, front, and right ultrasonic sensors
- **Left-hand rule navigation** — reliable maze solving algorithm
- **Dual motor control** — independent left/right motor speed via PWM (enable pins)
- **Serial monitor logging** — prints sensor distances and decisions in real time
- **Configurable parameters** — easily adjust speed, turn delay, and minimum distance

---

## Hardware Components

| Component              | Quantity | Purpose                        |
|------------------------|----------|--------------------------------|
| Arduino Uno            | 1        | Main microcontroller           |
| HC-SR04 Ultrasonic     | 3        | Left, front, right distance    |
| DC Motors              | 2        | Left and right wheel drive     |
| L298N Motor Driver     | 1        | Motor speed & direction control|
| Robot chassis          | 1        | Frame with 2 wheels + caster   |
| Battery pack (7-12V)   | 1        | Power supply                   |
| Jumper wires           | -        | Connections                    |

---

## Pin Configuration

| Pin | Component                  |
|-----|----------------------------|
| 2   | Right sensor TRIG          |
| 3   | Right sensor ECHO          |
| 4   | Right motor FORWARD        |
| 5   | Right motor BACKWARD       |
| 6   | Left motor ENABLE (PWM)    |
| 7   | Left motor FORWARD         |
| 8   | Left motor BACKWARD        |
| 9   | Right motor ENABLE (PWM)   |
| 10  | Front sensor TRIG          |
| 11  | Front sensor ECHO          |
| 12  | Left sensor TRIG           |
| 13  | Left sensor ECHO           |

---

## How It Works

```
┌──────────────┐     ┌─────────────────────┐     ┌──────────────────┐
│ 3x Ultrasonic│────▶│    Arduino Uno       │────▶│  L298N Driver    │
│   Sensors    │     │                     │     │                  │
│  Left/Front  │     │  Left-hand rule     │     │  Left Motor  🔄  │
│  Right       │     │  decision logic     │     │  Right Motor 🔄  │
└──────────────┘     └─────────────────────┘     └──────────────────┘
                              │
                              ▼
                      Serial Monitor
                   (L: xx  F: xx  R: xx)
                   (TURN LEFT / FORWARD...)
```

Each loop cycle (every 50ms):
1. Read distances from all 3 sensors
2. Apply left-hand rule to decide movement
3. Execute motor command
4. Print decision to Serial Monitor

---

## Configurable Parameters

You can easily tune these values at the top of the code:

```cpp
const int speedForward = 180;  // Forward speed (0-255)
const int speedTurn    = 150;  // Turning speed (0-255)
const int MIN_DISTANCE = 20;   // Wall detection distance in cm
const int TURN_DELAY   = 300;  // Turn duration in ms
```

---

## Installation & Upload

1. Install **Arduino IDE** from [arduino.cc](https://www.arduino.cc/en/software)
2. Install the `Ultrasonic` library (see below)
3. Open `src/maze_solver.ino`
4. Select **Board:** Arduino Uno
5. Select your **Port**
6. Click **Upload** ✓

---

## Required Libraries

Install via **Arduino IDE → Sketch → Include Library → Manage Libraries**:

| Library     | Install Name  | Purpose                    |
|-------------|---------------|----------------------------|
| Ultrasonic  | `Ultrasonic`  | HC-SR04 distance reading   |

---

## Project Structure

```
maze-solver-robot/
│
├── src/
│   └── maze_solver.ino        # Main Arduino sketch
│
├── schematics/
│   └── README.md              # Pin reference + circuit diagram placeholder
│
├── docs/                      # Add poster or report here
│
├── .gitignore
├── LICENSE
└── README.md
```

---

## License

This project is licensed under the [MIT License](LICENSE).
