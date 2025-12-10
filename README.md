# C++ Arduino Game Controller

Arduino-based custom videogame controller with a C++ Windows client that reads button states over serial and maps them to game actions or keyboard events for PC games.

## Overview

This project implements a **physical game controller** built around an Arduino board and a **C++ client application for Windows**:

- The **Arduino firmware** reads the state of physical buttons on the controller and encodes them into a compact binary format.
- The data is sent to the PC through the **serial (USB) connection**.
- On Windows, a **C++ application** opens the serial port, decodes the incoming bytes and translates them into:
  - internal game actions, and/or
  - virtual keyboard input, so that the controller can be used with existing games.

The goal of this project is to explore **embedded programming (Arduino)** together with **systems programming in C++ on Windows**, building a complete end-to-end prototype of a custom game controller.

## Features

- Custom physical controller layout (buttons wired to an Arduino board)
- Arduino firmware that:
  - Reads digital inputs using `INPUT_PULLUP`
  - Packs button states into a single byte (bitmask protocol)
  - Sends data at a fixed rate over the serial port
- C++ Windows client that:
  - Opens and manages a serial connection (e.g., `COM3`)
  - Parses the bitmask into individual button states
  - Logs or maps button presses to actions
  - Emulates keyboard events (optional) to control PC games

## Tech Stack

- **Hardware**
  - Arduino (e.g., Arduino Uno/Nano)
  - Physical buttons (and/or joystick)
- **Firmware**
  - Arduino C/C++ (compiled with the Arduino toolchain)
- **PC Client**
  - C++ (Windows)
  - Serial communication using WinAPI-based serial handling
  - (Optional) Keyboard emulation via WinAPI `SendInput`

## Project Structure

- `firmware/` – Arduino code for reading buttons and sending serial data  
- `pc-client/` – C++ Windows application that reads serial input and maps it to actions/keyboard events  
- `docs/` – Documentation, diagrams and protocol description  
- `hardware/` – References for controller layout, wiring, and 3D printed case

## Getting Started

### 1. Firmware (Arduino)

1. Open `firmware/game_controller.ino` in the Arduino IDE.
2. Adjust the `buttonPins` array to match your wiring.
3. Upload the sketch to your Arduino board.
4. Make sure the serial baud rate matches the PC client (default: `115200`).

### 2. PC Client (C++ on Windows)

The PC client is a small C++ application that:

- Opens a given serial port (e.g., `COM3`);
- Continuously reads 1-byte packets representing button states;
- Decodes the bitmask into individual button flags;
- Prints the states to the console and optionally triggers keyboard events.

You can build it using CMake:

```bash
cd pc-client
mkdir build
cd build
cmake ..
cmake --build .
```

Then run, for example:

```bash
./pc-client.exe COM3
```

(or `pc-client.exe COM3` on Windows).

## Protocol

The Arduino sends **1 byte** at a time over serial. Each bit in the byte represents a button:

- Bit 0 → UP  
- Bit 1 → DOWN  
- Bit 2 → LEFT  
- Bit 3 → RIGHT  
- Bit 4 → A  
- Bit 5 → B  

Bit = 1 means "pressed", bit = 0 means "released".

See `docs/protocol.md` for more details.

## Status

> Initial prototype focused on:
> - reading button states on the Arduino,
> - sending them via serial,
> - visualizing and mapping them in the C++ Windows client.
