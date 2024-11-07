# IoT and Embedded Systems - Discussion 11

This document provides an overview of the code discussed in the eleventh session, focusing on interfacing and reading data from multiple sensors with an Arduino. The setup includes a **DHT11** sensor for temperature and humidity, a **soil moisture sensor**, and an **NPK sensor** for soil nutrient levels, using an RS-485 communication module.

---

## Table of Contents
1. [Overview](#overview)
2. [Components Used](#components-used)
3. [Pin Configuration](#pin-configuration)
4. [Sensor Requests and Responses](#sensor-requests-and-responses)
5. [Code Explanation](#code-explanation)
6. [Session Diagram](#session-diagram)

---

## 1. Overview

This code is designed to read temperature, humidity, soil moisture, and soil nutrient levels (Nitrogen, Phosphorus, and Potassium) from sensors connected to an Arduino. The NPK sensor communicates via RS-485, a reliable protocol for long-distance communication, using predefined commands to request each nutrient level.

---

## 2. Components Used

- **DHT11 Sensor**: Measures temperature and humidity.
- **Soil Moisture Sensor**: Measures the moisture level in the soil.
- **NPK Sensor**: Measures Nitrogen (N), Phosphorus (P), and Potassium (K) levels in the soil, connected through an RS-485 module.
- **RS-485 Module**: Facilitates communication between the NPK sensor and the Arduino.

---

## 3. Pin Configuration

- **dhtPin (9)**: DHT11 data pin connected to pin 9 on the Arduino.
- **soilPin (A0)**: Soil moisture sensor connected to analog pin A0.
- **roPin (2)**: Receiver Output connected to pin 2 on the Arduino.
- **rePin (8)**: Receiver Enable connected to pin 8.
- **dePin (7)**: Data Enable connected to pin 7.
- **diPin (3)**: Data Input connected to pin 3.

---

## 4. Sensor Requests and Responses

### NPK Sensor Commands
- **Nitrogen Request**: `{0x01, 0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c}`
- **Phosphorus Request**: `{0x01, 0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc}`
- **Potassium Request**: `{0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0}`

These commands are sent to the NPK sensor through RS-485 to retrieve each nutrient value. The sensor responds with data that is read and processed by the Arduino.

---

## 5. Code Explanation

### Setup
- **DHT11 Initialization**: The DHT11 sensor is initialized on pin 9 for temperature and humidity measurements.
- **Serial Communication**: The `Serial` and `mod` objects are set up at a baud rate of 9600 for standard and RS-485 communication.
- **Pin Mode Configuration**: Pins for soil moisture, RS-485 control (RE and DE), and data (DI, RO) are configured as inputs or outputs as needed.

### Loop
1. **Read DHT11**: Temperature and humidity are read using the `dht.readHumidity()` and `dht.readTemperature()` functions.
2. **Read Soil Moisture**: The analog value from the soil moisture sensor is read from `soilPin` using `analogRead()`.
3. **Error Handling**: Checks if the readings from the DHT11 sensor are valid, printing an error message if not.
4. **Display Environmental Data**: Prints temperature, humidity, and soil moisture values to the serial monitor.

### Reading NPK Values
- **Nitrogen, Phosphorus, and Potassium**:
  - Each nutrient value is read using `readNitrogen()`, `readPhosphorous()`, and `readPotassium()` functions.
  - For each nutrient:
    - The Arduino enables the RS-485 module to transmit by setting `DE` and `RE` HIGH.
    - The request command for the specific nutrient is sent.
    - The Arduino then sets `DE` and `RE` LOW to receive the response.
    - The data is read from `mod` and stored in the `values` array, with the nutrient level stored in `values[4]`.

### Example Code Snippet
```cpp
byte readNitrogen() {
  digitalWrite(dePin, HIGH);
  digitalWrite(rePin, HIGH);
  delay(10);
  if(mod.write(nitrogenRequest, sizeof(nitrogenRequest)) == 8) {
    digitalWrite(dePin, LOW);
    digitalWrite(rePin, LOW);
    for(byte i = 0; i < 7; i++) {
      values[i] = mod.read();
      Serial.print(values[i], HEX);
    }
    Serial.println();
  }
  return values[4];
}