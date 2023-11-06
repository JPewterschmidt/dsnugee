#include "quick_sort.h"
#include "gtest/gtest.h"

#include <vector>

TEST(quick_sort, basic)
{
    ::std::vector v1{ 5,6,7,8,4,32,44,5,6,8,8,99 };
    ::std::vector v2 = v1;
    ::std::sort(v1.begin(), v1.end());
    dsnugee::quick_sort(v2.begin(), v2.end());
    
    ASSERT_EQ(v1, v2);
}
