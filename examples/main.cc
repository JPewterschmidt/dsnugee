#include "fmt/core.h"
#include "queue.h"
#include "disjoint.h"
#include "fmt/ranges.h"
#include <stack>
#include <tuple>
#include <string>
#include <iostream>
#include <cstddef>

#include "generalized_table.h"

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
    template<typename FormatCtx>
    auto format(const foo& f, FormatCtx& ctx)
    {
        return "f"s;
    }
};

int main()
{
}
