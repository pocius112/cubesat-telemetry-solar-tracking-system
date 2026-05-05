# cubesat-telemetry-solar-tracking-system
CubeSat-inspired embedded system with solar tracking, IMU-based attitude sensing, and wireless telemetry using nRF24L01+.

  Overview

This project is a CubeSat-inspired embedded system that combines solar panel tracking, attitude sensing, and wireless telemetry.
The system dynamically adjusts a solar panel orientation based on light intensity, measures orientation using an IMU sensor, and transmits real-time data to a ground station.

  Features

1. Solar panel tracking using 3 photoresistors (LDR)
2. Servo-controlled panel angle adjustment
3. Attitude estimation (roll & pitch) using MPU6050 IMU
4. Wireless telemetry using nRF24L01+
5. Real-time data transmission to ground station
6. Custom mechanical frame design

   Hardware
   
Arduino Uno / Nano
3x Photoresistors (LDR)
Servo motor
MPU6050 (IMU)
nRF24L01+ (2x for TX/RX)
Breadboard & jumper wires
External power supply

  Mechanical Design

The structural frame was designed using SolidWorks.
Custom frame for mounting sensors and servo mechanism
Optimized layout for stability and compactness
Designed specifically for solar panel movement

  Structural Analysis

Basic simulations were performed to validate the mechanical design:
Static Study
Evaluated structural strength under load
Verified safe operation under component weight
Frequency Study
Identified natural frequencies
Ensured no resonance under typical operation

  System Architecture
  
Satellite (Transmitter)
Reads light sensor values
Calculates optimal solar panel angle
Measures roll and pitch using IMU
Sends telemetry data via RF
Ground Station (Receiver)
Receives RF data
Displays or logs telemetry

  Software
Arduino (C/C++)
RF24 library for nRF communication

  Media

Full system prototype
Solar tracking mechanism
CAD model screenshots
Simulation results

  Key Concepts

Embedded systems design
Feedback control systems
Sensor integration
Wireless communication
Basic structural analysis

  Future Improvements
  
Closed-loop attitude stabilization
GPS integration
Data visualization dashboard
Power optimization

