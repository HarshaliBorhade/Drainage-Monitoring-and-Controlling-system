# Drainage Monitoring and Controlling System

## Overview
This system is designed to monitor and control drainage conditions, ensuring the proper functioning of drainage systems. Using an Arduino, the system integrates sensors for detecting temperature, humidity, distance (to measure blockages or overflow), gas (for detecting toxic gases), and water overflow conditions. The system sends real-time alerts when hazardous conditions like drainage blockages, overflow, or toxic gas emissions are detected. Additionally, the system can trigger an alarm using a buzzer and send SMS notifications to a designated phone number.

The project can be used in various applications such as drainage systems, water storage tanks, and other environmental monitoring systems where controlling overflow, blockages, and hazardous gases is critical.

---

## Features
- **Temperature & Humidity Monitoring**: Monitors the temperature and humidity to detect abnormal conditions that could affect drainage systems.
- **Distance Measurement**: Detects blockages and overflows in drainage pipes using an ultrasonic sensor.
- **Gas Detection**: Monitors the presence of harmful gases (e.g., methane) using a gas sensor.
- **Overflow Detection**: Detects overflow conditions to prevent flooding or damage in drainage systems.
- **SMS Alerts**: Sends SMS notifications when any hazardous condition (gas, overflow, blockage) is detected.
- **LCD Display**: Displays real-time sensor data, including temperature, humidity, and distance, for easy monitoring.
- **Buzzer Alarm**: Activates when any alert condition is met, notifying the user of potential issues.

---

## Hardware Requirements
- **Arduino Uno**: The microcontroller used to manage the system.
- **DHT11 Sensor**: Used for reading temperature and humidity values.
- **Ultrasonic Sensor (HC-SR04)**: Measures the distance to detect blockages or overflow conditions.
- **Gas Sensor (MQ series)**: Detects the presence of harmful gases such as methane.
- **Overflow Sensor**: Monitors the overflow condition in drainage systems.
- **Buzzer**: Used to trigger an alert when any hazardous condition is detected.
- **LCD Display (16x2)**: Displays the temperature, humidity, and distance readings in real-time.
- **SIM900/800 GSM Module**: Used to send SMS alerts when the system detects hazardous conditions.

---

## Pin Configuration
| Component            | Pin     |
|----------------------|---------|
| DHT11 Sensor         | Pin 2   |
| Ultrasonic Sensor    | Trig: Pin 3, Echo: Pin 4 |
| Gas Sensor           | Pin A0  |
| Overflow Sensor      | Pin A1  |
| Buzzer               | Pin 5   |
| LCD RS               | Pin 6   |
| LCD Enable           | Pin 7   |
| LCD D4               | Pin 8   |
| LCD D5               | Pin 9   |
| LCD D6               | Pin 10  |
| LCD D7               | Pin 11  |

---

## Code Explanation

### Setup:
1. **Sensor Initialization**: The system initializes all the sensors, including the DHT11 (temperature and humidity sensor), ultrasonic sensor, gas sensor, and overflow sensor.
2. **LCD Setup**: The 16x2 LCD is initialized to display real-time data about the system’s conditions.
3. **Serial Communication**: Used for debugging and sending SMS messages using the GSM module.

### Main Loop:
1. **Sensor Data Collection**:
   - The temperature and humidity are read from the DHT11 sensor.
   - Distance is measured using the ultrasonic sensor to detect blockages or overflow.
   - Gas sensor readings are taken to monitor toxic gas levels.
   - Overflow conditions are checked using the overflow sensor.

2. **Condition Checks**:
   - **Gas Detection**: If the gas sensor reads a value above a threshold (e.g., > 800), it triggers an SMS alert for a "Toxic Gas detected" situation.
   - **Overflow Detection**: If the overflow sensor reads a value above a certain threshold (e.g., > 512), an SMS is sent with the alert "Drainage Overflow detected."
   - **Blockage Detection**: If the ultrasonic sensor detects an obstruction within 10 cm, it triggers a "Drainage Blockage detected" alert.

3. **Displaying Data on LCD**: The temperature, humidity, and distance measurements are continuously updated on the LCD screen. If any condition (gas, overflow, or blockage) is detected, the appropriate alert message is displayed.

4. **Triggering Alerts**: 
   - If any of the hazardous conditions (gas, overflow, blockage) are detected, the buzzer is activated, and an SMS alert is sent to the pre-configured phone number.

### SMS Alerts:
The system sends SMS messages for the following alerts:
- **Gas Detected**: Sends an SMS with the message "Alert! Toxic Gas detected."
- **Overflow Detected**: Sends an SMS with the message "Alert! Drainage Overflow detected."
- **Blockage Detected**: Sends an SMS with the message "Alert! Drainage Blockage detected."

The SMS is sent using the GSM module (SIM900 or SIM800), and you can configure the recipient's phone number in the code.

---

## Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/your-username/drainage-monitoring-system.git
   cd drainage-monitoring-system
