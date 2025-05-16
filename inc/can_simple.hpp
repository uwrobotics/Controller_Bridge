#pragma once
#include <stdint.h>

namespace CanHeader {
    constexpr uint8_t broadcastNodeId = 0x3f;
    constexpr bool autoBuad = false; //support send beacon message
    constexpr uint16_t headerBound = 0x7ff;
    constexpr uint8_t cmdBound = 0x1f;
    constexpr uint8_t errorCode8 = static_cast<uint8_t>(-1);
    constexpr uint16_t errCode16 = static_cast<uint16_t>(-1);

    /// @todo: Support cmd decode and if not in enum assign UNDEFINE
    enum class CmdMap : uint8_t {
        Get_Version               = 0x000,
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
        Enter_DFU_Mode            = 0x01f
    };

    constexpr std::array<CmdMap, 28> valid_cmds = {
        CmdMap::Get_Version,
        CmdMap::Heartbeat,
        CmdMap::Estop,
        CmdMap::Get_Error,
        CmdMap::RxSdo,
        CmdMap::TxSdo,
        CmdMap::Address,
        CmdMap::Set_Axis_State,
        CmdMap::Get_Encoder_Estimates,
        CmdMap::Set_Controller_Mode,
        CmdMap::Set_Input_Pos,
        CmdMap::Set_Input_Vel,
        CmdMap::Set_Input_Torque,
        CmdMap::Set_Limits,
        CmdMap::Set_Traj_Vel_Limit,
        CmdMap::Set_Traj_Accel_Limits,
        CmdMap::Set_Traj_Inertia,
        CmdMap::Get_Iq,
        CmdMap::Get_Temperature,
        CmdMap::Reboot,
        CmdMap::Get_Bus_Voltage_Current,
        CmdMap::Clear_Errors,
        CmdMap::Set_Absolute_Position,
        CmdMap::Set_Pos_Gain,
        CmdMap::Set_Vel_Gains,
        CmdMap::Get_Torques,
        CmdMap::Get_Powers,
        CmdMap::Enter_DFU_Mode
    };
}



namespace CanPayload {
    #pragma pack(push, 1)
    struct GetVersionPayload {
        uint8_t protocol_version;
        uint8_t hw_version_major;
        uint8_t hw_version_minor;
        uint8_t hw_version_variant;
        uint8_t fw_version_major;
        uint8_t fw_version_minor;
        uint8_t fw_version_revision;
        uint8_t fw_version_unreleased;
    };
    
    struct HeartbeatPayload {
        uint32_t axis_error;
        uint8_t axis_state;
        uint8_t procedure_result;
        uint8_t trajectory_done;
        uint8_t reserved;
    };
    
    struct GetErrorPayload {
        uint32_t active_errors;
        uint32_t disarm_reason;
    };
    
    struct RxSdoPayload {
        uint8_t opcode;
        uint16_t endpoint_id;
        uint8_t reserved;
        uint32_t value;
    };
    
    struct TxSdoPayload {
        uint8_t reserved0;
        uint16_t endpoint_id;
        uint8_t reserved1;
        uint32_t value;
    };
    
    struct AddressPayload {
        uint8_t node_id;
        uint32_t serial_number_start;
        uint16_t serial_number_end;
        uint8_t connection_id;
    };
    
    struct EncoderEstimatesPayload {
        float pos_estimate;
        float vel_estimate;
    };
    
    struct GetIqPayload {
        float iq_setpoint;
        float iq_measured;
    };
    
    struct GetTemperaturePayload {
        float fet_temperature;
        float motor_temperature;
    };
    
    struct BusVoltageCurrentPayload {
        float bus_voltage;
        float bus_current;
    };
    
    struct GetTorquesPayload {
        float torque_target;
        float torque_estimate;
    };
    
    struct GetPowersPayload {
        float electrical_power;
        float mechanical_power;
    };
    
    struct SetAxisStatePayload {
        uint32_t axis_requested_state;
        uint32_t reserved;
    };
    
    struct SetControllerModePayload {
        uint8_t control_mode;
        uint8_t input_mode;
        uint16_t reserved0;
        uint32_t reserved1;
    };
    
    struct SetInputPosPayload {
        float input_pos;
        int16_t vel_ff;
        int16_t torque_ff;
    };
    
    struct SetInputVelPayload {
        float input_vel;
        float input_torque_ff;
    };
    
    struct SetInputTorquePayload {
        float input_torque;
        uint32_t reserved;
    };
    
    struct SetLimitsPayload {
        float velocity_limit;
        float current_limit;
    };
    
    struct SetTrajVelLimitPayload {
        float traj_vel_limit;
        uint32_t reserved;
    };
    
    struct SetTrajAccelLimitsPayload {
        float traj_accel_limit;
        float traj_decel_limit;
    };
    
    struct SetTrajInertiaPayload {
        float traj_inertia;
        uint32_t reserved;
    };
    
    struct RebootPayload {
        uint8_t action;
        uint8_t reserved1;
        uint16_t reserved2;
        uint32_t reserved3;
    };
    
    struct ClearErrorsPayload {
        uint32_t identify;
        uint32_t reserved;
    };
    
    struct SetAbsolutePositionPayload {
        float position;
        uint32_t reserved;
    };
    
    struct SetPosGainPayload {
        float pos_gain;
        uint32_t reserved;
    };
    
    struct SetVelGainsPayload {
        float vel_gain;
        float vel_integrator_gain;
    };
    #pragma pack(pop)

    

    // Compile-time check that all CAN payloads are == 8 bytes
    static_assert(sizeof(GetVersionPayload) == 8, "GetVersionPayload too large");
    static_assert(sizeof(HeartbeatPayload) == 8, "HeartbeatPayload too large");
    static_assert(sizeof(GetErrorPayload) == 8, "GetErrorPayload too large");
    static_assert(sizeof(RxSdoPayload) == 8, "RxSdoPayload too large");
    static_assert(sizeof(TxSdoPayload) == 8, "TxSdoPayload too large");
    static_assert(sizeof(AddressPayload) == 8, "AddressPayload too large");
    static_assert(sizeof(EncoderEstimatesPayload) == 8, "EncoderEstimatesPayload too large");
    static_assert(sizeof(GetIqPayload) == 8, "GetIqPayload too large");
    static_assert(sizeof(GetTemperaturePayload) == 8, "GetTemperaturePayload too large");
    static_assert(sizeof(BusVoltageCurrentPayload) == 8, "BusVoltageCurrentPayload too large");
    static_assert(sizeof(GetTorquesPayload) == 8, "GetTorquesPayload too large");
    static_assert(sizeof(GetPowersPayload) == 8, "GetPowersPayload too large");
    static_assert(sizeof(SetAxisStatePayload) == 8, "SetAxisStatePayload too large");
    static_assert(sizeof(SetControllerModePayload) == 8, "SetControllerModePayload too large");
    static_assert(sizeof(SetInputPosPayload) == 8, "SetInputPosPayload too large");
    static_assert(sizeof(SetInputVelPayload) == 8, "SetInputVelPayload too large");
    static_assert(sizeof(SetInputTorquePayload) == 8, "SetInputTorquePayload too large");
    static_assert(sizeof(SetLimitsPayload) == 8, "SetLimitsPayload too large");
    static_assert(sizeof(SetTrajVelLimitPayload) == 8, "SetTrajVelLimitPayload too large");
    static_assert(sizeof(SetTrajAccelLimitsPayload) == 8, "SetTrajAccelLimitsPayload too large");
    static_assert(sizeof(SetTrajInertiaPayload) == 8, "SetTrajInertiaPayload too large");
    static_assert(sizeof(RebootPayload) == 8, "RebootPayload too large");
    static_assert(sizeof(ClearErrorsPayload) == 8, "ClearErrorsPayload too large");
    static_assert(sizeof(SetAbsolutePositionPayload) == 8, "SetAbsolutePositionPayload too large");
    static_assert(sizeof(SetPosGainPayload) == 8, "SetPosGainPayload too large");
    static_assert(sizeof(SetVelGainsPayload) == 8, "SetVelGainsPayload too large");
}