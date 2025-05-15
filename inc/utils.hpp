#pragma once
#include <stdint.h>

/**
 * TODO:
 * - support unit testing
 * - compile using cmake
 * - Support Error handling
 * - support odrive config
 * reference: https://github.com/odriverobotics/ODriveResources/blob/master/examples/can_restore_config.py
 */

constexpr uint8_t broadcastNodeId = 0x3f;
constexpr bool autoBuad = false; //support send beacon message

constexpr uint16_t errCode = static_cast<uint16_t>(-1);

/// @brief support if not defined command then use undefined
enum class cmd_map : uint8_t {
    Get_Version                = 0x000,
    Heartbeat                 = 0x001,
    Estop                     = 0x002,
    Get_Error                 = 0x003,
    RxSdo                     = 0x004,
    TxSdo                     = 0x005,
    Address                   = 0x006,
    Set_Axis_State            = 0x007,
    Get_Encoder_Estimates     = 0x009,
    Set_Controller_Mode       = 0x00b,
    Set_Input_Pos             = 0x00c,
    Set_Input_Vel             = 0x00d,
    Set_Input_Torque          = 0x00e,
    Set_Limits                = 0x00f,
    Set_Traj_Vel_Limit        = 0x011,
    Set_Traj_Accel_Limits     = 0x012,
    Set_Traj_Inertia          = 0x013,
    Get_Iq                    = 0x014,
    Get_Temperature           = 0x015,
    Reboot                    = 0x016,
    Get_Bus_Voltage_Current   = 0x017,
    Clear_Errors              = 0x018,
    Set_Absolute_Position     = 0x019,
    Set_Pos_Gain              = 0x01a,
    Set_Vel_Gains             = 0x01b,
    Get_Torques               = 0x01c,
    Get_Powers                = 0x01d,
    Enter_DFU_Mode            = 0x01f,
    UNDEFINE                  = 0x0FF,
};


inline uint16_t set_arbitration_id(uint8_t node_id, cmd_map cmd) {
    // Boundary Check
    if(node_id > broadcastNodeId) {
        return errCode;
    }
    return (static_cast<uint16_t>(node_id) << 5) | static_cast<uint8_t>(cmd);
}

inline uint16_t get_arbitration_id(uint8_t node_id, cmd_map cmd) {
    // Boundary Check
    if(node_id > broadcastNodeId) {
        return errCode;
    }
    return (static_cast<uint16_t>(node_id) << 5) | static_cast<uint8_t>(cmd);
}

// output is 8 byte and then parse it into a struct?