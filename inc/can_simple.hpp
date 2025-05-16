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

        GetVersionPayload() = default;
        GetVersionPayload(uint8_t proto, uint8_t hw_maj, uint8_t hw_min, uint8_t hw_var,
                        uint8_t fw_maj, uint8_t fw_min, uint8_t fw_rev, uint8_t fw_unrel)
            : protocol_version(proto), hw_version_major(hw_maj), hw_version_minor(hw_min),
            hw_version_variant(hw_var), fw_version_major(fw_maj), fw_version_minor(fw_min),
            fw_version_revision(fw_rev), fw_version_unreleased(fw_unrel) {}
    };

    struct HeartbeatPayload {
        uint32_t axis_error{};
        uint8_t axis_state{};
        uint8_t procedure_result{};
        uint8_t trajectory_done{};
        uint8_t reserved{};

        HeartbeatPayload() = default;
        HeartbeatPayload(uint32_t err, uint8_t state, uint8_t result, uint8_t done, uint8_t res)
            : axis_error(err), axis_state(state), procedure_result(result), trajectory_done(done), reserved(res) {}
    };

    struct GetErrorPayload {
        uint32_t active_errors{};
        uint32_t disarm_reason{};

        GetErrorPayload() = default;
        GetErrorPayload(uint32_t errors, uint32_t reason)
            : active_errors(errors), disarm_reason(reason) {}
    };

    struct RxSdoPayload {
        uint8_t opcode{};
        uint16_t endpoint_id{};
        uint8_t reserved{};
        uint32_t value{};

        RxSdoPayload() = default;
        RxSdoPayload(uint8_t op, uint16_t ep, uint8_t res, uint32_t val)
            : opcode(op), endpoint_id(ep), reserved(res), value(val) {}
    };

    struct TxSdoPayload {
        uint8_t reserved0{};
        uint16_t endpoint_id{};
        uint8_t reserved1{};
        uint32_t value{};

        TxSdoPayload() = default;
        TxSdoPayload(uint8_t res0, uint16_t ep, uint8_t res1, uint32_t val)
            : reserved0(res0), endpoint_id(ep), reserved1(res1), value(val) {}
    };

    struct AddressPayload {
        uint8_t node_id{};
        uint32_t serial_number_start{};
        uint16_t serial_number_end{};
        uint8_t connection_id{};

        AddressPayload() = default;
        AddressPayload(uint8_t nid, uint32_t sn_start, uint16_t sn_end, uint8_t conn_id)
            : node_id(nid), serial_number_start(sn_start), serial_number_end(sn_end), connection_id(conn_id) {}
    };

    struct EncoderEstimatesPayload {
        float pos_estimate{};
        float vel_estimate{};

        EncoderEstimatesPayload() = default;
        EncoderEstimatesPayload(float pos, float vel) : pos_estimate(pos), vel_estimate(vel) {}
    };

    struct GetIqPayload {
        float iq_setpoint{};
        float iq_measured{};

        GetIqPayload() = default;
        GetIqPayload(float set, float meas) : iq_setpoint(set), iq_measured(meas) {}
    };

    struct GetTemperaturePayload {
        float fet_temperature{};
        float motor_temperature{};

        GetTemperaturePayload() = default;
        GetTemperaturePayload(float fet, float motor) : fet_temperature(fet), motor_temperature(motor) {}
    };

    struct BusVoltageCurrentPayload {
        float bus_voltage{};
        float bus_current{};

        BusVoltageCurrentPayload() = default;
        BusVoltageCurrentPayload(float volt, float curr) : bus_voltage(volt), bus_current(curr) {}
    };

    struct GetTorquesPayload {
        float torque_target{};
        float torque_estimate{};

        GetTorquesPayload() = default;
        GetTorquesPayload(float tgt, float est) : torque_target(tgt), torque_estimate(est) {}
    };

    struct GetPowersPayload {
        float electrical_power{};
        float mechanical_power{};

        GetPowersPayload() = default;
        GetPowersPayload(float elec, float mech) : electrical_power(elec), mechanical_power(mech) {}
    };

    struct SetAxisStatePayload {
        uint32_t axis_requested_state{};
        uint32_t reserved{};

        SetAxisStatePayload() = default;
        SetAxisStatePayload(uint32_t req, uint32_t res) : axis_requested_state(req), reserved(res) {}
    };

    struct SetControllerModePayload {
        uint8_t control_mode{};
        uint8_t input_mode{};
        uint16_t reserved0{};
        uint32_t reserved1{};

        SetControllerModePayload() = default;
        SetControllerModePayload(uint8_t ctrl, uint8_t input, uint16_t res0, uint32_t res1)
            : control_mode(ctrl), input_mode(input), reserved0(res0), reserved1(res1) {}
    };

    struct SetInputPosPayload {
        float input_pos{};
        int16_t vel_ff{};
        int16_t torque_ff{};

        SetInputPosPayload() = default;
        SetInputPosPayload(float pos, int16_t vff, int16_t tff) : input_pos(pos), vel_ff(vff), torque_ff(tff) {}
    };

    struct SetInputVelPayload {
        float input_vel{};
        float input_torque_ff{};

        SetInputVelPayload() = default;
        SetInputVelPayload(float vel, float torque_ff) : input_vel(vel), input_torque_ff(torque_ff) {}
    };

    struct SetInputTorquePayload {
        float input_torque{};
        uint32_t reserved{};

        SetInputTorquePayload() = default;
        SetInputTorquePayload(float torque, uint32_t res) : input_torque(torque), reserved(res) {}
    };

    struct SetLimitsPayload {
        float velocity_limit{};
        float current_limit{};

        SetLimitsPayload() = default;
        SetLimitsPayload(float vel, float curr) : velocity_limit(vel), current_limit(curr) {}
    };

    struct SetTrajVelLimitPayload {
        float traj_vel_limit{};
        uint32_t reserved{};

        SetTrajVelLimitPayload() = default;
        SetTrajVelLimitPayload(float vel, uint32_t res) : traj_vel_limit(vel), reserved(res) {}
    };

    struct SetTrajAccelLimitsPayload {
        float traj_accel_limit{};
        float traj_decel_limit{};

        SetTrajAccelLimitsPayload() = default;
        SetTrajAccelLimitsPayload(float accel, float decel) : traj_accel_limit(accel), traj_decel_limit(decel) {}
    };

    struct SetTrajInertiaPayload {
        float traj_inertia{};
        uint32_t reserved{};

        SetTrajInertiaPayload() = default;
        SetTrajInertiaPayload(float inertia, uint32_t res) : traj_inertia(inertia), reserved(res) {}
    };

    struct RebootPayload {
        uint8_t action{};
        uint8_t reserved1{};
        uint16_t reserved2{};
        uint32_t reserved3{};

        RebootPayload() = default;
        RebootPayload(uint8_t act, uint8_t r1, uint16_t r2, uint32_t r3)
            : action(act), reserved1(r1), reserved2(r2), reserved3(r3) {}
    };

    struct ClearErrorsPayload {
        uint32_t identify{};
        uint32_t reserved{};

        ClearErrorsPayload() = default;
        ClearErrorsPayload(uint32_t id, uint32_t res) : identify(id), reserved(res) {}
    };

    struct SetAbsolutePositionPayload {
        float position{};
        uint32_t reserved{};

        SetAbsolutePositionPayload() = default;
        SetAbsolutePositionPayload(float pos, uint32_t res) : position(pos), reserved(res) {}
    };

    struct SetPosGainPayload {
        float pos_gain{};
        uint32_t reserved{};

        SetPosGainPayload() = default;
        SetPosGainPayload(float gain, uint32_t res) : pos_gain(gain), reserved(res) {}
    };

    struct SetVelGainsPayload {
        float vel_gain{};
        float vel_integrator_gain{};

        SetVelGainsPayload() = default;
        SetVelGainsPayload(float gain, float igain) : vel_gain(gain), vel_integrator_gain(igain) {}
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