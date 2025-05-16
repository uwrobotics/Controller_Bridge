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
bool IsDefined(uint8_t value, const std::array<Enum, N>& allowed) {
    Enum candidate = static_cast<Enum>(value);
    return std::find(allowed.begin(), allowed.end(), candidate) != allowed.end();
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
}