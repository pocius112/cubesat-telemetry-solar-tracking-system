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
   
1. Arduino Uno / Nano
2. 3x Photoresistors (LDR)
3. Servo motor
4. MPU6050 (IMU)
5. nRF24L01+ (2x for TX/RX)
6. Breadboard & jumper wires
7. External power supply

  Mechanical Design

The structural frame was designed using SolidWorks.
Custom frame for mounting sensors and servo mechanism.
Optimized layout for stability and compactness.
Designed specifically for solar panel movement.

  Structural Analysis

Basic simulations were performed to validate the mechanical design:
Static Study:
1. Evaluated structural strength under load
2. Verified safe operation under component weight
Frequency Study:
1. Identified natural frequencies
2. Ensured no resonance under typical operation

  System Architecture
  
1. Satellite (Transmitter)
2. Reads light sensor values
3. Calculates optimal solar panel angle
4. Measures roll and pitch using IMU
5. Sends telemetry data via RF
6. Ground Station (Receiver)
7. Receives RF data
8. Displays or logs telemetry

  Software
1. Arduino (C/C++)
2. RF24 library for nRF communication

  Media

Full system prototype

Solar tracking mechanism

CAD model screenshots
<img width="615" height="602" alt="image" src="https://github.com/user-attachments/assets/b47a3d1a-a1bf-4771-823a-f4e4112d94c3" />

Simulation results
<img width="839" height="655" alt="image" src="https://github.com/user-attachments/assets/d1dd70ae-cb74-44a4-9e87-1fdf02c0ed28" />
<img width="792" height="656" alt="image" src="https://github.com/user-attachments/assets/5e91faad-9381-43db-8aab-22e05a792594" />
<img width="958" height="642" alt="image" src="https://github.com/user-attachments/assets/71207de3-c726-4119-a065-f09d2b740823" />
<img width="1046" height="654" alt="image" src="https://github.com/user-attachments/assets/131c2e34-0364-4471-94c6-bf1b59f572f0" />

  Key Concepts

1. Embedded systems design
2. Feedback control systems
3. Sensor integration
4. Wireless communication
5. Basic structural analysis

  Future Improvements
  
1. Closed-loop attitude stabilization
2. GPS integration
3. Data visualization dashboard
4. Power optimization

