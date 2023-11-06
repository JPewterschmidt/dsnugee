#include "kmp.h"
#include "gtest/gtest.h"
#include <string>
#include "fmt/core.h"
#include "fmt/ranges.h"

using namespace dsnugee;

TEST(kmp, next_evaluation)
{
    ::std::string pattern{ "aaab" };
    const auto next = evaluate_next(pattern);
    fmt::print("{}\n", next);   
}
