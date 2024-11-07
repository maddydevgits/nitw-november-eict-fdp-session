# IoT and Embedded Systems - Discussion 10

This document summarizes the tenth discussion in the IoT and Embedded Systems session, focusing on the detailed wiring and data flow for interfacing an NPK sensor with an Arduino through an RS-485 module. This setup enables robust communication for monitoring soil nutrients, which is essential in agricultural applications.

---

## Table of Contents
1. [Overview of NPK Sensor Interfacing](#overview-of-npk-sensor-interfacing)
2. [Components Used](#components-used)
3. [Wiring and Connections](#wiring-and-connections)
4. [Control and Data Flow](#control-and-data-flow)
5. [Arduino Code Example](#arduino-code-example)
6. [Session Diagram](#session-diagram)

---

## 1. Overview of NPK Sensor Interfacing

The NPK sensor is used to measure Nitrogen (N), Phosphorus (P), and Potassium (K) levels in soil, which are crucial for plant growth. The sensor is connected to an Arduino via an RS-485 module, allowing for long-distance and noise-resistant data transmission.

---

## 2. Components Used

- **NPK Sensor**: Measures soil nutrient levels.
- **RS-485 Module**: Provides differential communication between the NPK sensor and the Arduino.
- **Arduino**: Microcontroller to process and read data from the NPK sensor via the RS-485 module.

---

## 3. Wiring and Connections

### NPK Sensor Connections
- **VCC**: Connect to a 12V power source.
- **A and B**: RS-485 communication lines.
- **GND**: Connect to ground.

### RS-485 Module Connections
- **VCC**: Connect to the 5V pin on the Arduino.
- **GND**: Connect to the GND pin on both the Arduino and the NPK sensor.
- **DI (Data Input)**: Connected to the Arduino for sending requests.
- **RO (Receive Output)**: Connected to the Arduino for receiving data.
- **DE (Data Enable)** and **RE (Receive Enable)**: Control pins that toggle between sending (request) and receiving (response) modes.

### Arduino Connections
- **Control Pins (DE and RE)**: Connected to digital pins (e.g., pin 1 and pin 3) to manage the RS-485 module's mode.
- **Data Pins (DI and RO)**: Connected to digital pins on the Arduino to handle data transmission and reception.

---

## 4. Control and Data Flow

- **Control Pins**:
  - **DE (Data Enable)** and **RE (Receive Enable)** control the RS-485 module’s transmission mode.
  - When DE and RE are HIGH, the module is in transmit mode (sending requests).
  - When DE and RE are LOW, the module switches to receive mode (receiving responses).
- **Data Flow**:
  - **Request**: The Arduino sends a request to the NPK sensor to retrieve nutrient levels via `DI`.
  - **Response**: The NPK sensor sends back nutrient data through `RO`, which is read by the Arduino.
- **Reading Data**:
  - The Arduino stores received values in an array, where `values[i] = mod.read();`, representing N, P, and K levels.

---

## 5. Arduino Code Example

Below is a simplified Arduino code snippet to communicate with the NPK sensor via the RS-485 module:

```cpp
// Control pins for DE and RE
int DE = 3;  // Data Enable
int RE = 1;  // Receive Enable

// Setup control pins as outputs
pinMode(DE, OUTPUT);
pinMode(RE, OUTPUT);

// Switch to transmit mode
digitalWrite(DE, HIGH);  
digitalWrite(RE, HIGH);

// Send request to NPK sensor
mod.write(requestCommand);

// Switch to receive mode
digitalWrite(DE, LOW);   
digitalWrite(RE, LOW);

// Read the response
int values[3];  // Array to store N, P, K values
values[0] = mod.read();  // Read nitrogen level
values[1] = mod.read();  // Read phosphorus level
values[2] = mod.read();  // Read potassium level