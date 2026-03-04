# 🚀 S32K144 Embedded Projects Collection

A collection of firmware development projects for the **NXP S32K144** microcontroller, developed using **S32 Design Studio v3.5**.

---

## 📌 Repository Overview
This repository contains multiple projects focusing on Bootloader, Timers, and Communication Protocols (I2C, UART).

| Project | Key Features | Peripherals | Tools Used |
| :--- | :--- | :--- | :--- |
| **Bootloader** | Firmware Update over UART | UART, Flash, GPIO | S-Record, Terminal |
| **GPIO & SysTick** | Periodic Task Handling | GPIO, SysTick | S32DS |
| **I2C Protocol** | Master-Slave Communication | I2C, LPIT, ADC | Logic Analyzer |
| **UART Protocol** | S-Record Parsing | UART | Hercules Terminal |

---

## 🛠 Project 1: Custom Bootloader
A robust bootloader to update application firmware via UART without a debugger.

* **IDE:** S32DS v3.5
* **Hardware:** S32K144 Board
* **Baudrate:** `9600`
* **App Start Address:** `0x4000`

### 📖 Operating Sequence
1.  **Power On/Reset:** Red light blinks 3 times.
2.  **Enter Boot Mode:** Press and hold **SW2** until the **Blue light** turns ON.
3.  **Data Transfer:** Transmit **S-record** file via UART terminal.
4.  **Status Indicators:**
    * ✅ **Green light ON:** Flash successful.
    * ❌ **Red light ON:** Flash failed.
5.  **Execution:** Reset board. If no action is taken, the board blinks Red 3 times and automatically jumps to the application (if previously flashed).

---

## 🛠 Project 2: GPIO & SysTick Timer
Demonstrating system tick interrupts for precise LED control.

* **IDE:** S32 Design Studio v3.5
* **Hardware:** S32K144EVB Devkit
* **Features:**
    * Uses SysTick interrupt to trigger a user-defined **callback function**.
    * The callback handles LED toggling/control.
    * **Configurable:** Users can modify settings in the `board/config` folder.

---

## 🛠 Project 3: I2C Protocol (Master-Slave)
Implementation of I2C communication between two S32K144 MCUs.

* **Hardware:** 2x S32K144EVB Devkit
* **Testing Tool:** Logic Analyzer

### 🔌 Hardware Setup
* Connect **A2** and **A3** between the two MCUs.
* Connect a common **GND** wire.

### 📝 Execution Steps
1.  Flash **Master** code to MCU 1 and **Slave** code to MCU 2.
2.  **Important:** Reset MCU 2 (Slave) first, then Reset MCU 1 (Master).
3.  Use a **Logic Analyzer** to verify the data packets.

### 💡 Slave Behavior
* **Case 1:** LED blinks (1s to 10s frequency) based on ADC values sent from Master (controlled by LPIT).
* **Case 2:** Pin mapping: D11 (Pin 3), D12 (Pin 4).

---

## 🛠 Project 4: UART Protocol & S-Record Parser
High-speed UART communication and firmware data parsing.

* **Baudrate:** `115200`
* **Terminal:** Hercules
* **Functionality:** Receives data from Hercules, validates, and parses the **S-Record** format.

### 🚀 Operating Sequence
1.  Load the program to the MCU.
2.  Reset the MCU and open **Hercules Terminal**.
3.  Transmit the S-record file via Hercules.
4.  Monitor the parsing results directly on the terminal output.

---

## ⚙️ Environment Requirements
* **IDE:** S32 Design Studio version 3.5.
* **SDK:** S32K1xx SDK.
* **Hardware:** S32K144EVB Devkit.

---
**THANK YOU!** 🙌
