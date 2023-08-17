#include "gtest/gtest.h"
#include "fmt/core.h"
#include "disjoint.h"
#include "helpers.h"
#include "generalized_table.h"
#include <exception>

using namespace ::std::string_view_literals;
using namespace ::std::string_literals;
using namespace dsnugee;

class foo
{
public:
    foo() = default;
    foo(foo&&)                  noexcept {}
    foo& operator=(foo&&)       noexcept { return *this; }
    foo(const foo&)             { throw ::std::exception{}; }
    foo& operator=(const foo&)  { throw ::std::exception{}; return *this; }

    constexpr bool operator==(const foo&) const noexcept { return true; }
};

TEST(generalized_table, performance)
{
    ::std::tuple t1{ 1, 2, 3, foo{} };
    auto t2 = tail(::std::move(t1));
    auto t3 = tail(tail(::std::move(t2)));
}

TEST(generalized_table, basic)
{
    ::std::tuple t1{ 1, 2, 3, foo{} };
    auto t2 = tail(::std::move(t1));
    ASSERT_EQ((head(t2)), 3);
    auto t3 = tail(tail(::std::move(t2)));
    ::std::tuple t4{ foo{} };
    ASSERT_EQ(t3, t4);
}

TEST(generalized_table, empty_table)
{
    ::std::tuple t1{};
    auto t2 = tail(t1);
    ASSERT_EQ((is_specialization_of<decltype(t2), ::std::tuple>), true);
    ASSERT_EQ(::std::tuple_size<decltype(t2)>(), 0);
    ASSERT_EQ(t1, t2);
    ASSERT_EQ(typeid(t1).name(), typeid(t2).name());
}
