#include <gtest/gtest.h>
#include "utils.hpp"

using namespace CanHeader;

class CanHeaderEncode : public ::testing::Test {
    protected:
        void SetUp() override {
            // Runs before each TEST_F
        }
    
        void TearDown() override {
            // Runs after each TEST_F
        }

        const uint8_t testNodeId = 0x15;
        const uint16_t testNodeHeader = 0x2a0;
        const uint16_t testBroadNodeHeader = 0x7e0;
        const uint8_t testOutBoundNodeId = 0x4a;
};

TEST_F(CanHeaderEncode, NormalIdNoCmd) {
    uint16_t header = encode(HeaderInfo(testNodeId, cmd_map::Get_Version));
    ASSERT_EQ(header, testNodeHeader) << "[Error] Incorrect Node ID Shifting\n";
}

TEST_F(CanHeaderEncode, BroadCastIdNoCmd) {
    uint16_t header = encode(HeaderInfo(broadcastNodeId, cmd_map::Get_Version));
    ASSERT_EQ(header, testBroadNodeHeader) << "[Error] Incorrect Broad Cast Node ID Shifting\n";
}

TEST_F(CanHeaderEncode, OutBoundIdNoCmd) {
    uint16_t header = encode(HeaderInfo(testOutBoundNodeId, cmd_map::Get_Version));
    ASSERT_EQ(header, errCode16) << "[Error] Out-of-bound Node ID should return error\n";
}

class CanHeaderDecode : public ::testing::Test {
    protected:
        void SetUp() override {
            // Runs before each TEST_F
        }
    
        void TearDown() override {
            // Runs after each TEST_F
        }

        const uint8_t testNodeId = 0x15;
        const uint16_t testNodeHeader = 0x2a0;
        const uint16_t testBroadNodeHeader = 0x7e0;
        const uint16_t testOutBoundNodeHeader = 0x940;
};

TEST_F(CanHeaderDecode, NormalIdNoCmd) {
    HeaderInfo header = decode(testNodeHeader);
    ASSERT_EQ(header, HeaderInfo(testNodeId, cmd_map::Get_Version)) << "[Error] Incorrect decode";
}

TEST_F(CanHeaderDecode, BroadCastIdNoCmd) {
    HeaderInfo header = decode(testBroadNodeHeader);
    ASSERT_EQ(header, HeaderInfo(broadcastNodeId, cmd_map::Get_Version)) << "[Error] Incorrect decode";
}

TEST_F(CanHeaderDecode, OutBoundIdNoCmd) {
    HeaderInfo header = decode(testOutBoundNodeHeader);
    ASSERT_EQ(header, HeaderInfo(errorCode8, static_cast<cmd_map>(errorCode8))) << "[Error] Incorrect decode";
}