#include "float_to_bitset.h"
#include "gtest/gtest.h"

using namespace dsnugee;

TEST(float_to_bitset, to_floating)
{
    float num = to_floating<float>(0xc0a00000);
    ASSERT_EQ(num, -5) << num;
}
