#include "gtest/gtest.h"
#include "fixed_point_multiplier_simulator.h"
#include "alu.h"

using namespace dsnugee;

TEST(simulators, fixed_point_multiplier_simulator_test)
{
    constexpr ::std::size_t scale = 5;
    ::std::bitset<scale> x("11101"), y("01011");
    const auto result = fixed_point_multiplier_simulator<scale, alu>(x, y).execute();
    ASSERT_EQ(result, ::std::bitset<scale>("11000")) << result.to_string();
}
