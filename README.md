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



# Interface

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



## Set Command

```c++
//todo
```

# Testing and Validation

```bash
# Create build folder based on CMakeLists.txt
cmake -S . -b build

# Compile the project
cmake --build build

# Execute test
cd build && ctest && cd ..
```

# Acknowledgements
