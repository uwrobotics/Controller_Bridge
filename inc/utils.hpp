#pragma once
#include <stdint.h>
#include <array>
#include <algorithm>

/**
 * TODO:
 * - compile to library using cmake
 * - Support Error handling
 * - support odrive config
 * reference: https://github.com/odriverobotics/ODriveResources/blob/master/examples/can_restore_config.py
 */

template <typename Enum, size_t N>
bool IsDefined(uint8_t value, const std::array<Enum, N>& allowed) {
    Enum candidate = static_cast<Enum>(value);
    return std::find(allowed.begin(), allowed.end(), candidate) != allowed.end();
}

namespace CanHeader {
    constexpr uint8_t broadcastNodeId = 0x3f;
    constexpr bool autoBuad = false; //support send beacon message
    constexpr uint16_t headerBound = 0x7ff;
    constexpr uint8_t cmdBound = 0x1f;
    constexpr uint8_t errorCode8 = static_cast<uint8_t>(-1);
    constexpr uint16_t errCode16 = static_cast<uint16_t>(-1);

    /// @todo: Support cmd decode and if not in enum assign UNDEFINE
    enum class CmdMap : uint8_t {
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

    struct HeaderInfo{
        uint8_t id;
        CmdMap cmd;

        HeaderInfo(uint8_t id_val, CmdMap cmd_val)
            : id(id_val), cmd(cmd_val) {}
    };


    inline uint16_t encode(HeaderInfo header) {
        // Boundary Check
        if(header.id > broadcastNodeId) {
            return errCode16;
        }
        return (static_cast<uint16_t>(header.id) << 5) | static_cast<uint8_t>(header.cmd);
    }

    inline HeaderInfo decode(uint16_t buf) {
        // Boundary Check
        if(buf > headerBound) {
            return HeaderInfo(errorCode8, static_cast<CmdMap>(errorCode8));
        }
        return HeaderInfo(buf>>5 & broadcastNodeId, static_cast<CmdMap>(buf & cmdBound));
    }

    inline bool operator==(const HeaderInfo& lhs, const HeaderInfo& rhs) {
        return lhs.id == rhs.id && lhs.cmd == rhs.cmd;
    }

    inline bool is_defined(uint8_t cmd) {
        return IsDefined<CmdMap>(cmd, valid_cmds);
    }
}

namespace CanPayload {

}