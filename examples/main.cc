#include "fmt/core.h"
#include "queue.h"
#include "disjoint.h"
#include "fmt/ranges.h"
#include <ranges>
#include <stack>
#include <tuple>
#include <string>
#include <cstddef>
#include <unordered_map>
#include <map>
#include "generalized_table.h"
#include "helpers.h"
#include <algorithm>
#include <iterator>
#include <thread>
#include "sort.h"
#include <print>
#include "kmp.h"
#include "binary_tree.h"
#include "binary_tree_traverser.h"
#include "directed_graph.h"

using namespace ::std::string_literals;
using namespace dsnugee;

namespace dsnugee
{
    void put_red();
    void put_white();
    void pick_white();
    void pick_red();
}

int main()
{
    {
        ::std::vector<::std::jthread> thrs;
        thrs.emplace_back(put_red);
        thrs.emplace_back(put_white);
        thrs.emplace_back(pick_red);
        thrs.emplace_back(pick_white);
    }

    ::std::println();   
    print_topological_sort_stack(topological_sort_example());
}
