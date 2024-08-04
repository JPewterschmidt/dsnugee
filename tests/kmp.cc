#include "kmp.h"
#include "gtest/gtest.h"
#include <string>
#include <vector>
#include "fmt/format.h"
#include "fmt/ranges.h"

using namespace dsnugee;

TEST(kmp, next_evaluation)
{
    ::std::string pattern{ "aaab" };
    const auto next = evaluate_next(pattern);
    ASSERT_EQ(next, (::std::vector{0, 1, 2, 0})) << fmt::format("{}", next);
}
