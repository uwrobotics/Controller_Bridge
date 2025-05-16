#pragma once
#include <stdint.h>
#include <array>
#include <algorithm>

#include "can_simple.hpp"

/**
 * TODO:
 * - compile to library using cmake
 * - Support Error handling
 * - support odrive config
 * reference: https://github.com/odriverobotics/ODriveResources/blob/master/examples/can_restore_config.py
 */

template <typename Enum, size_t N>
inline bool IsDefined(uint8_t value, const std::array<Enum, N>& allowed) {
    Enum candidate = static_cast<Enum>(value);
    return std::find(allowed.begin(), allowed.end(), candidate) != allowed.end();
}

template <typename T>
inline uint64_t pack_struct_to_u64(const T& src) {
    static_assert(sizeof(T) <= sizeof(uint64_t), "Struct too large to fit in uint64_t");
    uint64_t buf = 0;
    memcpy(&buf, &src, sizeof(T));
    return buf;
}

template <typename T>
inline T unpack_u64_to_struct(uint64_t data) {
    static_assert(sizeof(T) <= sizeof(uint64_t), "Struct too large to unpack from uint64_t");
    T result;
    memcpy(&result, &data, sizeof(T));
    return result;
}

namespace CanHeader {
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
    inline uint64_t align_int48_t(uint32_t upper, uint16_t lower) {
        return static_cast<uint64_t> (upper << 16) & lower;
    }

    inline uint64_t pack_GetVersionPayload(uint8_t proto, uint8_t hw_maj, uint8_t hw_min, uint8_t hw_var,
                                        uint8_t fw_maj, uint8_t fw_min, uint8_t fw_rev, uint8_t fw_unrel) {
        return pack_struct_to_u64(GetVersionPayload(proto, hw_maj, hw_min, hw_var, fw_maj, fw_min, fw_rev, fw_unrel));
    }

    inline uint64_t pack_HeartbeatPayload(uint32_t err, uint8_t state, uint8_t result, uint8_t done, uint8_t res) {
        return pack_struct_to_u64(HeartbeatPayload(err, state, result, done, res));
    }

    inline uint64_t pack_GetErrorPayload(uint32_t errors, uint32_t reason) {
        return pack_struct_to_u64(GetErrorPayload(errors, reason));
    }

    inline uint64_t pack_RxSdoPayload(uint8_t op, uint16_t ep, uint8_t res, uint32_t val) {
        return pack_struct_to_u64(RxSdoPayload(op, ep, res, val));
    }

    inline uint64_t pack_TxSdoPayload(uint8_t res0, uint16_t ep, uint8_t res1, uint32_t val) {
        return pack_struct_to_u64(TxSdoPayload(res0, ep, res1, val));
    }

    inline uint64_t pack_AddressPayload(uint8_t nid, uint32_t sn_start, uint16_t sn_end, uint8_t conn_id) {
        return pack_struct_to_u64(AddressPayload(nid, sn_start, sn_end, conn_id));
    }

    inline uint64_t pack_EncoderEstimatesPayload(float pos, float vel) {
        return pack_struct_to_u64(EncoderEstimatesPayload(pos, vel));
    }

    inline uint64_t pack_GetIqPayload(float set, float meas) {
        return pack_struct_to_u64(GetIqPayload(set, meas));
    }

    inline uint64_t pack_GetTemperaturePayload(float fet, float motor) {
        return pack_struct_to_u64(GetTemperaturePayload(fet, motor));
    }

    inline uint64_t pack_BusVoltageCurrentPayload(float volt, float curr) {
        return pack_struct_to_u64(BusVoltageCurrentPayload(volt, curr));
    }

    inline uint64_t pack_GetTorquesPayload(float tgt, float est) {
        return pack_struct_to_u64(GetTorquesPayload(tgt, est));
    }

    inline uint64_t pack_GetPowersPayload(float elec, float mech) {
        return pack_struct_to_u64(GetPowersPayload(elec, mech));
    }

    inline uint64_t pack_SetAxisStatePayload(uint32_t req, uint32_t res) {
        return pack_struct_to_u64(SetAxisStatePayload(req, res));
    }

    inline uint64_t pack_SetControllerModePayload(uint8_t ctrl, uint8_t input, uint16_t res0, uint32_t res1) {
        return pack_struct_to_u64(SetControllerModePayload(ctrl, input, res0, res1));
    }

    inline uint64_t pack_SetInputPosPayload(float pos, int16_t vff, int16_t tff) {
        return pack_struct_to_u64(SetInputPosPayload(pos, vff, tff));
    }

    inline uint64_t pack_SetInputVelPayload(float vel, float torque_ff) {
        return pack_struct_to_u64(SetInputVelPayload(vel, torque_ff));
    }

    inline uint64_t pack_SetInputTorquePayload(float torque, uint32_t res) {
        return pack_struct_to_u64(SetInputTorquePayload(torque, res));
    }

    inline uint64_t pack_SetLimitsPayload(float vel, float curr) {
        return pack_struct_to_u64(SetLimitsPayload(vel, curr));
    }

    inline uint64_t pack_SetTrajVelLimitPayload(float vel, uint32_t res) {
        return pack_struct_to_u64(SetTrajVelLimitPayload(vel, res));
    }

    inline uint64_t pack_SetTrajAccelLimitsPayload(float accel, float decel) {
        return pack_struct_to_u64(SetTrajAccelLimitsPayload(accel, decel));
    }

    inline uint64_t pack_SetTrajInertiaPayload(float inertia, uint32_t res) {
        return pack_struct_to_u64(SetTrajInertiaPayload(inertia, res));
    }

    inline uint64_t pack_RebootPayload(uint8_t act, uint8_t r1, uint16_t r2, uint32_t r3) {
        return pack_struct_to_u64(RebootPayload(act, r1, r2, r3));
    }

    inline uint64_t pack_ClearErrorsPayload(uint32_t id, uint32_t res) {
        return pack_struct_to_u64(ClearErrorsPayload(id, res));
    }

    inline uint64_t pack_SetAbsolutePositionPayload(float pos, uint32_t res) {
        return pack_struct_to_u64(SetAbsolutePositionPayload(pos, res));
    }

    inline uint64_t pack_SetPosGainPayload(float gain, uint32_t res) {
        return pack_struct_to_u64(SetPosGainPayload(gain, res));
    }

    inline uint64_t pack_SetVelGainsPayload(float gain, float igain) {
        return pack_struct_to_u64(SetVelGainsPayload(gain, igain));
    }

    inline GetVersionPayload unpack_GetVersionPayload(uint64_t data) {
        return unpack_u64_to_struct<GetVersionPayload>(data);
    }

    inline HeartbeatPayload unpack_HeartbeatPayload(uint64_t data) {
        return unpack_u64_to_struct<HeartbeatPayload>(data);
    }

    inline GetErrorPayload unpack_GetErrorPayload(uint64_t data) {
        return unpack_u64_to_struct<GetErrorPayload>(data);
    }

    inline RxSdoPayload unpack_RxSdoPayload(uint64_t data) {
        return unpack_u64_to_struct<RxSdoPayload>(data);
    }

    inline TxSdoPayload unpack_TxSdoPayload(uint64_t data) {
        return unpack_u64_to_struct<TxSdoPayload>(data);
    }

    inline AddressPayload unpack_AddressPayload(uint64_t data) {
        return unpack_u64_to_struct<AddressPayload>(data);
    }

    inline EncoderEstimatesPayload unpack_EncoderEstimatesPayload(uint64_t data) {
        return unpack_u64_to_struct<EncoderEstimatesPayload>(data);
    }

    inline GetIqPayload unpack_GetIqPayload(uint64_t data) {
        return unpack_u64_to_struct<GetIqPayload>(data);
    }

    inline GetTemperaturePayload unpack_GetTemperaturePayload(uint64_t data) {
        return unpack_u64_to_struct<GetTemperaturePayload>(data);
    }

    inline BusVoltageCurrentPayload unpack_BusVoltageCurrentPayload(uint64_t data) {
        return unpack_u64_to_struct<BusVoltageCurrentPayload>(data);
    }

    inline GetTorquesPayload unpack_GetTorquesPayload(uint64_t data) {
        return unpack_u64_to_struct<GetTorquesPayload>(data);
    }

    inline GetPowersPayload unpack_GetPowersPayload(uint64_t data) {
        return unpack_u64_to_struct<GetPowersPayload>(data);
    }

    inline SetAxisStatePayload unpack_SetAxisStatePayload(uint64_t data) {
        return unpack_u64_to_struct<SetAxisStatePayload>(data);
    }

    inline SetControllerModePayload unpack_SetControllerModePayload(uint64_t data) {
        return unpack_u64_to_struct<SetControllerModePayload>(data);
    }

    inline SetInputPosPayload unpack_SetInputPosPayload(uint64_t data) {
        return unpack_u64_to_struct<SetInputPosPayload>(data);
    }

    inline SetInputVelPayload unpack_SetInputVelPayload(uint64_t data) {
        return unpack_u64_to_struct<SetInputVelPayload>(data);
    }

    inline SetInputTorquePayload unpack_SetInputTorquePayload(uint64_t data) {
        return unpack_u64_to_struct<SetInputTorquePayload>(data);
    }

    inline SetLimitsPayload unpack_SetLimitsPayload(uint64_t data) {
        return unpack_u64_to_struct<SetLimitsPayload>(data);
    }

    inline SetTrajVelLimitPayload unpack_SetTrajVelLimitPayload(uint64_t data) {
        return unpack_u64_to_struct<SetTrajVelLimitPayload>(data);
    }

    inline SetTrajAccelLimitsPayload unpack_SetTrajAccelLimitsPayload(uint64_t data) {
        return unpack_u64_to_struct<SetTrajAccelLimitsPayload>(data);
    }

    inline SetTrajInertiaPayload unpack_SetTrajInertiaPayload(uint64_t data) {
        return unpack_u64_to_struct<SetTrajInertiaPayload>(data);
    }

    inline RebootPayload unpack_RebootPayload(uint64_t data) {
        return unpack_u64_to_struct<RebootPayload>(data);
    }

    inline ClearErrorsPayload unpack_ClearErrorsPayload(uint64_t data) {
        return unpack_u64_to_struct<ClearErrorsPayload>(data);
    }

    inline SetAbsolutePositionPayload unpack_SetAbsolutePositionPayload(uint64_t data) {
        return unpack_u64_to_struct<SetAbsolutePositionPayload>(data);
    }

    inline SetPosGainPayload unpack_SetPosGainPayload(uint64_t data) {
        return unpack_u64_to_struct<SetPosGainPayload>(data);
    }

    inline SetVelGainsPayload unpack_SetVelGainsPayload(uint64_t data) {
        return unpack_u64_to_struct<SetVelGainsPayload>(data);
    }
}