#include <iostream>
#include <string.h>  // For memcpy
#include "utils.hpp"

int main() {
    using namespace CanHeader;
    using namespace CanPayload;

    // Encode CAN header
    HeaderInfo header(0x01, CmdMap::Get_Version);
    uint16_t encoded = encode(header);
    auto decoded = decode(encoded);

    std::cout << "[Header] Encoded: 0x" << std::hex << encoded << std::dec << "\n";
    std::cout << "[Header] Decoded ID: " << static_cast<int>(decoded.id)
              << ", CMD: " << static_cast<int>(decoded.cmd) << "\n";

    // Encode & decode payload
    uint64_t packed = pack_GetVersionPayload(1, 2, 3, 4, 5, 6, 7, 8);
    auto payload = unpack_GetVersionPayload(packed);

    std::cout << "[Payload] Packed: 0x" << std::hex << packed << std::dec << "\n";
    std::cout << "[Payload] Decoded: Proto=" << static_cast<int>(payload.protocol_version)
              << ", HW=" << static_cast<int>(payload.hw_version_major) << "."
              << static_cast<int>(payload.hw_version_minor) << "."
              << static_cast<int>(payload.hw_version_variant)
              << ", FW=" << static_cast<int>(payload.fw_version_major) << "."
              << static_cast<int>(payload.fw_version_minor) << "."
              << static_cast<int>(payload.fw_version_revision) << "."
              << static_cast<int>(payload.fw_version_unreleased) << "\n";

    return 0;
}