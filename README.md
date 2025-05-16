# Introduction

This is an official library repository for all the device that need to interact with ODrive  micro or S1 or similar Motor Controller. Our team are currently using ODrive V3.6, ODrive Micro, and ODrive S1. Currently the command set support ODrive Micro and S1 using documentation 6.11. [ODrive Docs](https://docs.odriverobotics.com/v/latest/guides/getting-started.html)

# Project Objective

In short term, this project is aimed to support ODrive family. In long term, this project is also aiming to support custom FOC Device manufactured in house.

- High-Level CAN Message Agent
  - Device Identification
  - Device Command Abstraction over CAN
  - Grouping Device Command
- INS/ GNSS Fusion and Logging
- Device Error Handling
- Robotics Simulation Abstraction(Gazebo)

Anyone using this library still need to integrate this library into the application/ simulation on top of this static library.

On my computer the post-compiled library is libodrive.a.

# Folder Structure

The project

```bash
.
├── C++.gitignore
├── CMake.gitignore
├── CMakeLists.txt
├── LICENSE
├── README.md
├── build
├── inc
├── src
└── test   
```

## Movement Command

```c++
enum class MvCmd {
    Vel,
    Pos
};

class MvCmd {
    MvCmd mode;
    uint16_t id;
   	float32 value[2]; //X, Y component for vel or pos
}
```

Note: Vel_FF, Torque_FF is preconfigured variable.

## Get Command

```cpp
class InsOut {
    float fet_temp;
    float bus_volt;
    float bus_curr;
    float pos_est;
    float vel_est;
    float torque_est;
}

class Logging {
    float fet_temp;
    float bus_volt;
    float bus_curr;
    float pos_est;
    float vel_est;
    float torque_est;
    float motor_temp;
    float phase_current_setpoint;
    float phase_current_measured;
    float torque_tar;
    float elec_power;
    float mech_power;
}
```

# Compile Library and UnitTest

```bash
mkdir build && cd build

cmake .. && cd ..

# Create build folder based on CMakeLists.txt
cmake -B build -DCMAKE_INSTALL_PREFIX=lib

# Compile the project
cmake --build build

cmake --install build
```

# Testing and Validation

```bash
# Execute test
cd build && ctest && cd ..
```

# Acknowledgements
