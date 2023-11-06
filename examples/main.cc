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
#include <map>
#include "generalized_table.h"
#include "helpers.h"
#include <algorithm>
#include <iterator>
#include "quick_sort.h"
#include "kmp.h"
#include "binary_tree.h"
#include "binary_tree_traverser.h"

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
    void hi() { ::std::cout << "hi" << ::std::endl; }
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

void print(::std::ranges::range auto & r)
{
    for ( auto& i : r)
        ::std::cout << i << ",";
    ::std::cout << ::std::endl;
}

int main()
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

    root_first_traverser<int> rf{ bt };
    print(rf);
    print(rf);
    auto rv = ::std::ranges::reverse_view(rf);
    print(rv);

    ::std::vector<int> result1(rf.begin(), rf.end());
    ::std::vector<int> result2(rv.begin(), rv.end());
}
