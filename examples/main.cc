#include "fmt/core.h"
#include "queue.h"
#include "disjoint.h"
#include "fmt/ranges.h"
#include <stack>
#include <tuple>
#include <string>

#include "generalized_table.h"

using namespace ::std::string_literals;
using namespace dsnugee;

int main()
{
    ::std::tuple tt{ 1, 2, 3, "ssss"s };
    fmt::print("{}\n", tt);
    fmt::print("{}\n", head(tt));
    fmt::print("{}\n", tail(tt));
}
