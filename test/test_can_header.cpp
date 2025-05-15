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
    uint16_t header = encode(HeaderInfo(testNodeId, CmdMap::Get_Version));
    ASSERT_EQ(header, testNodeHeader) << "[Error] Incorrect Node ID Shifting\n";
}

TEST_F(CanHeaderEncode, BroadCastIdNoCmd) {
    uint16_t header = encode(HeaderInfo(broadcastNodeId, CmdMap::Get_Version));
    ASSERT_EQ(header, testBroadNodeHeader) << "[Error] Incorrect Broad Cast Node ID Shifting\n";
}

TEST_F(CanHeaderEncode, OutBoundIdNoCmd) {
    uint16_t header = encode(HeaderInfo(testOutBoundNodeId, CmdMap::Get_Version));
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
    ASSERT_EQ(header, HeaderInfo(testNodeId, CmdMap::Get_Version)) << "[Error] Incorrect decode";
}

TEST_F(CanHeaderDecode, BroadCastIdNoCmd) {
    HeaderInfo header = decode(testBroadNodeHeader);
    ASSERT_EQ(header, HeaderInfo(broadcastNodeId, CmdMap::Get_Version)) << "[Error] Incorrect decode";
}

TEST_F(CanHeaderDecode, OutBoundIdNoCmd) {
    HeaderInfo header = decode(testOutBoundNodeHeader);
    ASSERT_EQ(header, HeaderInfo(errorCode8, static_cast<CmdMap>(errorCode8))) << "[Error] Incorrect decode";
}

class CanCmdDecode : public ::testing::Test {
    protected:
        void SetUp() override {
            // Runs before each TEST_F
        }
    
        void TearDown() override {
            // Runs after each TEST_F
        }

        const uint8_t test_cmd = static_cast<uint8_t>(CmdMap::Clear_Errors);
        const uint8_t test_outbound_cmd = 0x20;
        const uint8_t test_inbound_invalid_cmd = 0x08;
};

TEST_F(CanCmdDecode, ValidCmd) {
    bool valid_cmd = is_defined(test_cmd);
    ASSERT_EQ(valid_cmd, true) << "[Error] Incorrect Cmd Identification";
}

TEST_F(CanCmdDecode, InvalidCmd) {
    bool valid_cmd = is_defined(test_outbound_cmd);
    ASSERT_EQ(valid_cmd, false) << "[Error] Incorrect Cmd Identification";
}
TEST_F(CanCmdDecode, InvalidInboundCmd) {
    bool valid_cmd = is_defined(test_inbound_invalid_cmd);
    ASSERT_EQ(valid_cmd, false) << "[Error] Incorrect Cmd Identification";
}