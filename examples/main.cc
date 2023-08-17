#include "fmt/core.h"
#include "queue.h"
#include "disjoint.h"
#include "fmt/ranges.h"
#include <ranges>
#include <stack>
#include <tuple>
#include <string>
#include <iostream>
#include <cstddef>
#include <unordered_map>
#include "generalized_table.h"
#include "helpers.h"
#include <algorithm>
#include <iterator>
#include "quick_sort.h"

using namespace ::std::string_literals;
using namespace dsnugee;

class foo
{
public:
    foo()                       noexcept { fmt::print("ctor\n"); }
    foo(foo&&)                  noexcept { fmt::print("foo move ctor\n"); }
    foo(const foo&)             noexcept { fmt::print("foo copy ctor\n"); }
    foo& operator=(foo&&)       noexcept { fmt::print("foo move oper\n"); return *this; }
    foo& operator=(const foo&)  noexcept { fmt::print("foo copy oper\n"); return *this; }
    ~foo()                      noexcept { fmt::print("dtor\n"); }
};

::std::ostream& operator<<(::std::ostream& os, const foo& f)
{
    return os << "ok ";
}

template<>
class fmt::formatter<foo>
{
    auto format(const foo& f, auto& ctx)
    {
        return "f"s;
    }
};

void test_unordered_map()
{
    auto primes = generate_n_prime_number(100);
    ::std::unordered_map<int, int> iimap;
    for (int i = 0; i < 999; ++i)
    {
        iimap[i] = i + 1;
    }
}

int main()
{
    auto riota_view = ::std::ranges::iota_view(0, 20) | ::std::views::reverse;
    ::std::vector ivec(riota_view.begin(), riota_view.end());
    //::std::sort(ivec.begin(), ivec.end());

    dsnugee::quick_sort(ivec.begin(), ivec.end());
    fmt::print("{}\n", ivec);
}
