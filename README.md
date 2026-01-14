# Smart-Fan-System

## Description
This project implements a smart fan using 2 PSoC's microcontrollers. The DC motor will change its speed based on the time. The system also demonstrates UART communication between two PSoCs, allowing one to handle sensor data processing and the other to control the fan’s motor and servo mechanism. The first PSoC acts as the sensor unit. It reads the time from RTC module then sends commands to the second PSoC using UART. The second PSoC acts as the motor control unit. It receives the control signals and adjusts the fan’s DC motor speed and the servo rotation based on the commands.




## Hardware Components 
- 2 PSoC5LP microcontollers 
- DS3231 RTC Module
- DC Motor
- Motor Driver (L298N)
- Servo Motor
- Resistors
- Breadboard and Jumper Wires


## Top Design PSoC 1
![Top Deisgn PSoC 1](Images/Top_Design1.png) 
