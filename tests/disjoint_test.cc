#include "gtest/gtest.h"
#include "fmt/core.h"
#include "disjoint.h"
#include <iostream>

using namespace ::std::string_view_literals;

class disjoint_test : public ::testing::Test
{
public:
    disjoint_test() = default;
    disjoint_test(disjoint_test&&) noexcept = default;
    ~disjoint_test() noexcept
    {
        for (int i : ds.storage())
        {
            ::std::cout << i << " ";
        }
        ::std::cout << ::std::endl;
    }
    
protected:
    disjoint_set ds{ 10 };
};

TEST_F(disjoint_test, initial_value_test)
{
    for (auto& val : ds.storage())
    {
        ASSERT_EQ(val, -1);
    }
}

TEST_F(disjoint_test, perform_union_then_finding)
{
    ds.union_sets(0, 5);
    ds.union_sets(5, 4);
    ds.union_sets(6, 8);
    ASSERT_EQ(ds.find(5), ds.find(4));
    ASSERT_EQ(ds.find(6), ds.find(8));
}
