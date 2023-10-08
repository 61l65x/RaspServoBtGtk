# Servo Controller via Bluetooth RFCOMM

![Project Image](your_project_image.png)

This project establishes a Bluetooth RFCOMM connection between a controller and a user interface, enabling the control of servo motors. Servos can be used to control various devices, from car mirrors to robotic arms.

## Features

- Bluetooth Classic / RFCOMM communication.
- Two sliders for controlling two servo motors.
- Servos can be controlled via either software or hardware PWM signals.
- User-friendly GTK GUI for controlling the servos.
- Supports digital mode servo control.

## Libraries Used

### Server Side
- **WiringPi**: This library is used for the low-level control for Raspberry.

### Connection
- **Bluetooth**: The connection is build with the low level bluetooth libary with.

### User Side
- **Gtk**: The graphical user interface is built using the Gtk library, providing a smooth and interactive control experience.

## Getting Started

To get started with this project, follow these steps:

1. [Installation](#installation): Set up the required libraries and dependencies.
2. [Usage](#usage): Learn how to use the software and control the servos.
3. [Troubleshooting](#troubleshooting): Find solutions to common issues.
4. [Contributing](#contributing): Contribute to the project and make it better.
5. [License](#license): Understand the project's licensing terms.

## Installation

To use this servo controller, you need to install the required libraries:

```bash
sudo apt install libgtk-4-dev  # Install for the GUI
sudo apt install wiringpi  # Install for the pin control
sudo apt-get install libbluetooth-dev # Install for communication
 