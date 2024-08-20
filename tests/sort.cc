#include "sort.h"
#include "gtest/gtest.h"

#include <vector>
#include "fmt/ranges.h"
#include "fmt/format.h"

TEST(sort, quick_sort)
{
    ::std::vector v1{ 5,6,7,8,4,32,44,5,6,8,8,99,0 };
    ::std::vector v2 = v1;
    ::std::sort(v1.begin(), v1.end());

    dsnugee::quick_sort(v2.begin(), v2.end());

    ASSERT_EQ(v1, v2) << fmt::format("{}", v2);
}

TEST(sort, bobble_sort)
{
    ::std::vector v1{ 5,6,7,8,4,32,44,5,6,8,8,99,0 };
    ::std::vector v2 = v1;
    ::std::sort(v1.begin(), v1.end());

    dsnugee::bobble_sort(v2.begin(), v2.end());

    ASSERT_EQ(v1, v2) << fmt::format("{}", v2);
}

TEST(sort, insert_sort)
{
    ::std::vector v1{ 5,6,7,8,4,32,44,5,6,8,8,99,0 };
    ::std::vector v2 = v1;
    ::std::sort(v1.begin(), v1.end());

    dsnugee::insert_sort(v2.begin(), v2.end());

    ASSERT_EQ(v1, v2) << fmt::format("{}", v2);
}
