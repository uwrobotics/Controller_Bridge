# Introduction

This is an official branch for all the device that need to interact with ODrive or Similar Motor Controller. Our team are currently using ODrive V3.6, ODrive Micro, and ODrive S1.

# Folder Structure

The project is divided into generic code & interface in the /inc and /src folder. Target specific code are linked in the /target folder.

```bash
.
├── inc
├── src
└── target
    ├── ros
    ├── seeedxiao
    └── stm 
```

# Project Objective

In short term, this project is aimed to support ODrive family. In long term, this project is also aiming to support custom FOC Device manufactured in house.
- Device Identification
- Device Command Abstraction over CAN
- Grouping Device Command
- INS/ GNSS Fusion and Logging
- Device Error Handling
- Robotics Simulation Abstraction(Gazebo)

Anyone using this library still need to integrate application/ simulation on top of this static library.

# Acknowledgements
