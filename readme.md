# IoT and Embedded Systems - Day 1 Summary

This document provides a consolidated summary of discussions and coding sessions completed on Day 1 of the IoT and Embedded Systems program. The topics covered on Day 1 include basic IoT architecture, sensor interfacing, communication protocols, and real-world applications using Arduino.

---

## Table of Contents
1. [Introduction to IoT Architecture](#introduction-to-iot-architecture)
2. [Embedded Systems and Sensor Interfacing](#embedded-systems-and-sensor-interfacing)
3. [Detailed Session Summaries](#detailed-session-summaries)
   - [Discussion 1: IoT Architecture and 4D Technology](#discussion-1-iot-architecture-and-4d-technology)
   - [Discussion 2: IoT Layered Architecture](#discussion-2-iot-layered-architecture)
   - [Discussion 3: Node and Gateway Configuration](#discussion-3-node-and-gateway-configuration)
   - [Discussion 4: Microcontrollers and Signal Handling](#discussion-4-microcontrollers-and-signal-handling)
   - [Discussion 5: Node and Sensor Communication](#discussion-5-node-and-sensor-communication)
   - [Discussion 6: Environmental Monitoring Case Study](#discussion-6-environmental-monitoring-case-study)
   - [Discussion 7: DHT11 Sensor Wiring](#discussion-7-dht11-sensor-wiring)
   - [Discussion 8: Soil Moisture Sensor Wiring](#discussion-8-soil-moisture-sensor-wiring)
   - [Discussion 9: NPK Sensor Interfacing with RS-485](#discussion-9-npk-sensor-interfacing-with-rs-485)
   - [Discussion 10: Advanced NPK Sensor Communication](#discussion-10-advanced-npk-sensor-communication)
   - [Discussion 11: Multi-Sensor Data Collection Code](#discussion-11-multi-sensor-data-collection-code)

---

## 1. Introduction to IoT Architecture

Day 1 began with an introduction to the IoT architecture, which includes layers and components used in data collection, processing, and visualization. Topics like sensor types, data transmission protocols, and layered IoT architecture were discussed to provide a foundation for understanding embedded IoT systems.

---

## 2. Embedded Systems and Sensor Interfacing

Key discussions on embedded systems covered sensor interfacing techniques, communication protocols like RS-485, and control mechanisms using microcontrollers such as Arduino. Real-world applications, including environmental monitoring, were explored through practical coding and wiring examples.

---

## 3. Detailed Session Summaries

### Discussion 1: IoT Architecture and 4D Technology
- Overview of 4D technology within IoT, including data collection, storage, visualization, and security.
- Embedded systems were introduced with examples of hardware/software integration for specific tasks.

### Discussion 2: IoT Layered Architecture
- A deep dive into the 5-layer IoT architecture, covering:
  - Sensory Layer
  - Node Layer
  - Gateway Layer
  - Cloud Layer
  - Application Layer
- Applications in areas like healthcare were highlighted.

### Discussion 3: Node and Gateway Configuration
- Details on configuring nodes and gateways, focusing on wired/wireless communication protocols.
- Discussed how each layer contributes to overall data processing.

### Discussion 4: Microcontrollers and Signal Handling
- Discussion on the use of microcontrollers and sensors for monitoring and controlling tasks.
- Introduction to analog and digital signal processing for embedded systems.

### Discussion 5: Node and Sensor Communication
- Covered RS-485, SPI, I2C, and UART protocols for long-distance and reliable data transmission.
- Examples of practical applications using these communication protocols.

### Discussion 6: Environmental Monitoring Case Study
- Case study focused on temperature, humidity, soil moisture, and nutrient monitoring.
- Introduction to NPK sensors for soil nutrient monitoring and analog soil moisture sensors.

### Discussion 7: DHT11 Sensor Wiring
- Configuration and wiring for the DHT11 sensor to measure temperature and humidity.
- Overview of interfacing the DHT11 sensor with Arduino.

### Discussion 8: Soil Moisture Sensor Wiring
- Setup and wiring of an analog soil moisture sensor to an Arduino.
- Explanation of analog output and how soil moisture is read in an IoT system.

### Discussion 9: NPK Sensor Interfacing with RS-485
- Wiring and interfacing of the NPK sensor with Arduino via an RS-485 module.
- Sending requests and receiving responses from the NPK sensor to measure soil nutrients.

### Discussion 10: Advanced NPK Sensor Communication
- Further details on control and data flow for NPK sensor communication.
- Explanation of request-response protocol using RS-485 in an Arduino environment.

### Discussion 11: Multi-Sensor Data Collection Code
- Code implementation for collecting data from DHT11, soil moisture, and NPK sensors.
- Overview of RS-485 communication with Arduino, including serial communication settings and sensor requests.

---

Each discussion on Day 1 involved hands-on examples and coding exercises to reinforce the concepts. The sessions provided a comprehensive foundation in IoT architecture, sensor interfacing, and embedded system programming.

---
# References
1. https://lastminuteengineers.com/dht11-dht22-arduino-tutorial/
2. https://lastminuteengineers.com/soil-npk-sensor-arduino-tutorial/
3. https://www.raspberrypi.com/documentation/computers/getting-started.html
4. https://www.arduino.cc
5. https://www.thingspeak.com
6. https://wokwi.com/ 
