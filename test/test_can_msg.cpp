#include <gtest/gtest.h>
#include "utils.hpp"

using namespace CanPayload;

class PackFixture : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PackFixture, Pack_GetVersionPayload) {
    auto val = pack_GetVersionPayload(207, 0, 188, 173, 34, 61, 203, 186);
    auto result = unpack_GetVersionPayload(val);
    EXPECT_EQ(result.protocol_version, 207);
    EXPECT_EQ(result.hw_version_major, 0);
    EXPECT_EQ(result.hw_version_minor, 188);
    EXPECT_EQ(result.hw_version_variant, 173);
    EXPECT_EQ(result.fw_version_major, 34);
    EXPECT_EQ(result.fw_version_minor, 61);
    EXPECT_EQ(result.fw_version_revision, 203);
    EXPECT_EQ(result.fw_version_unreleased, 186);
}
TEST_F(PackFixture, Pack_HeartbeatPayload) {
    auto val = pack_HeartbeatPayload(4106194757, 240, 176, 144, 232);
    auto result = unpack_HeartbeatPayload(val);
    EXPECT_EQ(result.axis_error, 4106194757);
    EXPECT_EQ(result.axis_state, 240);
    EXPECT_EQ(result.procedure_result, 176);
    EXPECT_EQ(result.trajectory_done, 144);
    EXPECT_EQ(result.reserved, 232);
}
TEST_F(PackFixture, Pack_GetErrorPayload) {
    auto val = pack_GetErrorPayload(1126843295, 779179158);
    auto result = unpack_GetErrorPayload(val);
    EXPECT_EQ(result.active_errors, 1126843295);
    EXPECT_EQ(result.disarm_reason, 779179158);
}
TEST_F(PackFixture, Pack_RxSdoPayload) {
    auto val = pack_RxSdoPayload(82, 17176, 63, 2471323060);
    auto result = unpack_RxSdoPayload(val);
    EXPECT_EQ(result.opcode, 82);
    EXPECT_EQ(result.endpoint_id, 17176);
    EXPECT_EQ(result.reserved, 63);
    EXPECT_EQ(result.value, 2471323060);
}
TEST_F(PackFixture, Pack_TxSdoPayload) {
    auto val = pack_TxSdoPayload(181, 14034, 199, 1726867364);
    auto result = unpack_TxSdoPayload(val);
    EXPECT_EQ(result.reserved0, 181);
    EXPECT_EQ(result.endpoint_id, 14034);
    EXPECT_EQ(result.reserved1, 199);
    EXPECT_EQ(result.value, 1726867364);
}
TEST_F(PackFixture, Pack_AddressPayload) {
    auto val = pack_AddressPayload(158, 1687132453, 13548, 83);
    auto result = unpack_AddressPayload(val);
    EXPECT_EQ(result.node_id, 158);
    EXPECT_EQ(result.serial_number_start, 1687132453);
    EXPECT_EQ(result.serial_number_end, 13548);
    EXPECT_EQ(result.connection_id, 83);
}
TEST_F(PackFixture, Pack_EncoderEstimatesPayload) {
    auto val = pack_EncoderEstimatesPayload(939.9461059570312, -343.69403076171875);
    auto result = unpack_EncoderEstimatesPayload(val);
    EXPECT_EQ(result.pos_estimate, 939.9461059570312);
    EXPECT_EQ(result.vel_estimate, -343.69403076171875);
}
TEST_F(PackFixture, Pack_GetIqPayload) {
    auto val = pack_GetIqPayload(-753.4401245117188, -583.8773193359375);
    auto result = unpack_GetIqPayload(val);
    EXPECT_EQ(result.iq_setpoint, -753.4401245117188);
    EXPECT_EQ(result.iq_measured, -583.8773193359375);
}
TEST_F(PackFixture, Pack_GetTemperaturePayload) {
    auto val = pack_GetTemperaturePayload(179.77752685546875, 706.0946044921875);
    auto result = unpack_GetTemperaturePayload(val);
    EXPECT_EQ(result.fet_temperature, 179.77752685546875);
    EXPECT_EQ(result.motor_temperature, 706.0946044921875);
}
TEST_F(PackFixture, Pack_BusVoltageCurrentPayload) {
    auto val = pack_BusVoltageCurrentPayload(934.9306640625, 522.6814575195312);
    auto result = unpack_BusVoltageCurrentPayload(val);
    EXPECT_EQ(result.bus_voltage, 934.9306640625);
    EXPECT_EQ(result.bus_current, 522.6814575195312);
}
TEST_F(PackFixture, Pack_GetTorquesPayload) {
    auto val = pack_GetTorquesPayload(754.4702758789062, 615.1375732421875);
    auto result = unpack_GetTorquesPayload(val);
    EXPECT_EQ(result.torque_target, 754.4702758789062);
    EXPECT_EQ(result.torque_estimate, 615.1375732421875);
}
TEST_F(PackFixture, Pack_GetPowersPayload) {
    auto val = pack_GetPowersPayload(-879.1647338867188, 625.155029296875);
    auto result = unpack_GetPowersPayload(val);
    EXPECT_EQ(result.electrical_power, -879.1647338867188);
    EXPECT_EQ(result.mechanical_power, 625.155029296875);
}
TEST_F(PackFixture, Pack_SetAxisStatePayload) {
    auto val = pack_SetAxisStatePayload(3711643247, 3299453749);
    auto result = unpack_SetAxisStatePayload(val);
    EXPECT_EQ(result.axis_requested_state, 3711643247);
    EXPECT_EQ(result.reserved, 3299453749);
}
TEST_F(PackFixture, Pack_SetControllerModePayload) {
    auto val = pack_SetControllerModePayload(93, 193, 55955, 1026479264);
    auto result = unpack_SetControllerModePayload(val);
    EXPECT_EQ(result.control_mode, 93);
    EXPECT_EQ(result.input_mode, 193);
    EXPECT_EQ(result.reserved0, 55955);
    EXPECT_EQ(result.reserved1, 1026479264);
}
TEST_F(PackFixture, Pack_SetInputPosPayload) {
    auto val = pack_SetInputPosPayload(751.236572265625, -7048, -2865);
    auto result = unpack_SetInputPosPayload(val);
    EXPECT_EQ(result.input_pos, 751.236572265625);
    EXPECT_EQ(result.vel_ff, -7048);
    EXPECT_EQ(result.torque_ff, -2865);
}
TEST_F(PackFixture, Pack_SetInputVelPayload) {
    auto val = pack_SetInputVelPayload(500.6752624511719, -409.4150390625);
    auto result = unpack_SetInputVelPayload(val);
    EXPECT_EQ(result.input_vel, 500.6752624511719);
    EXPECT_EQ(result.input_torque_ff, -409.4150390625);
}
TEST_F(PackFixture, Pack_SetInputTorquePayload) {
    auto val = pack_SetInputTorquePayload(979.186767578125, 1885310099);
    auto result = unpack_SetInputTorquePayload(val);
    EXPECT_EQ(result.input_torque, 979.186767578125);
    EXPECT_EQ(result.reserved, 1885310099);
}
TEST_F(PackFixture, Pack_SetLimitsPayload) {
    auto val = pack_SetLimitsPayload(-633.29638671875, 108.10169982910156);
    auto result = unpack_SetLimitsPayload(val);
    EXPECT_EQ(result.velocity_limit, -633.29638671875);
    EXPECT_EQ(result.current_limit, 108.10169982910156);
}
TEST_F(PackFixture, Pack_SetTrajVelLimitPayload) {
    auto val = pack_SetTrajVelLimitPayload(-996.68505859375, 4074180013);
    auto result = unpack_SetTrajVelLimitPayload(val);
    EXPECT_EQ(result.traj_vel_limit, -996.68505859375);
    EXPECT_EQ(result.reserved, 4074180013);
}
TEST_F(PackFixture, Pack_SetTrajAccelLimitsPayload) {
    auto val = pack_SetTrajAccelLimitsPayload(-635.3016357421875, -715.0675659179688);
    auto result = unpack_SetTrajAccelLimitsPayload(val);
    EXPECT_EQ(result.traj_accel_limit, -635.3016357421875);
    EXPECT_EQ(result.traj_decel_limit, -715.0675659179688);
}
TEST_F(PackFixture, Pack_SetTrajInertiaPayload) {
    auto val = pack_SetTrajInertiaPayload(255.33192443847656, 1464517241);
    auto result = unpack_SetTrajInertiaPayload(val);
    EXPECT_EQ(result.traj_inertia, 255.33192443847656);
    EXPECT_EQ(result.reserved, 1464517241);
}
TEST_F(PackFixture, Pack_RebootPayload) {
    auto val = pack_RebootPayload(98, 113, 53258, 1229868823);
    auto result = unpack_RebootPayload(val);
    EXPECT_EQ(result.action, 98);
    EXPECT_EQ(result.reserved1, 113);
    EXPECT_EQ(result.reserved2, 53258);
    EXPECT_EQ(result.reserved3, 1229868823);
}
TEST_F(PackFixture, Pack_ClearErrorsPayload) {
    auto val = pack_ClearErrorsPayload(3748010892, 1473327532);
    auto result = unpack_ClearErrorsPayload(val);
    EXPECT_EQ(result.identify, 3748010892);
    EXPECT_EQ(result.reserved, 1473327532);
}
TEST_F(PackFixture, Pack_SetAbsolutePositionPayload) {
    auto val = pack_SetAbsolutePositionPayload(-565.8623046875, 33672196);
    auto result = unpack_SetAbsolutePositionPayload(val);
    EXPECT_EQ(result.position, -565.8623046875);
    EXPECT_EQ(result.reserved, 33672196);
}
TEST_F(PackFixture, Pack_SetPosGainPayload) {
    auto val = pack_SetPosGainPayload(-497.8382263183594, 2656791018);
    auto result = unpack_SetPosGainPayload(val);
    EXPECT_EQ(result.pos_gain, -497.8382263183594);
    EXPECT_EQ(result.reserved, 2656791018);
}
TEST_F(PackFixture, Pack_SetVelGainsPayload) {
    auto val = pack_SetVelGainsPayload(-323.467041015625, 368.3490295410156);
    auto result = unpack_SetVelGainsPayload(val);
    EXPECT_EQ(result.vel_gain, -323.467041015625);
    EXPECT_EQ(result.vel_integrator_gain, 368.3490295410156);
}