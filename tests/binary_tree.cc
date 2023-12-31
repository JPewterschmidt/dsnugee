#include "gtest/gtest.h"

#include "binary_tree.h"
#include "binary_tree_traverser.h"

#include <vector>
#include <ranges>

using namespace dsnugee;

auto make_testing_tree()
{
    binary_tree<int> bt;
    bt.insert(10);
    bt.insert(5);
    bt.insert(15);
    bt.insert(2);
    bt.insert(6);
    bt.insert(13);
    bt.insert(1);
    bt.insert(3);
    bt.insert(7);
    bt.insert(12);
    bt.insert(11);
    bt.insert(14);
    bt.insert(4);
    bt.insert(8);
    bt.insert(9);
    
    return bt;
}

TEST(binary_tree, root_first_trvarse)
{
    auto bt = make_testing_tree();   
    root_first_traverser<int> rf{ bt };
    auto rv = ::std::ranges::reverse_view(rf);

    ::std::vector<int> result1(rf.begin(), rf.end());
    ::std::vector<int> result2(rv.begin(), rv.end());

    ::std::vector<int> answer1{ 10,5,2,1,3,4,6,7,8,9,15,13,12,11,14 };
    ::std::vector<int> answer2{ 14,11,12,13,15,9,8,7,6,4,3,1,2,5,10 };

    ASSERT_EQ(result1, answer1);
    ASSERT_EQ(result2, answer2);
}

TEST(binary_tree, root_last_trvarse)
{
    auto bt = make_testing_tree();   
    root_last_traverser<int> rf{ bt };
    auto rv = ::std::ranges::reverse_view(rf);

    ::std::vector<int> result1(rf.begin(), rf.end());
    ::std::vector<int> result2(rv.begin(), rv.end());

    ::std::vector<int> answer1{ 1,4,3,2,9,8,7,6,5,11,12,14,13,15,10 };
    ::std::vector<int> answer2{ 10,15,13,14,12,11,5,6,7,8,9,2,3,4,1 };

    ASSERT_EQ(result1, answer1);
    ASSERT_EQ(result2, answer2);
}
