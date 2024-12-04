#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include <print> 
#include <vector>
#include <stack>
#include <unordered_set>

namespace dsnugee {

class directed_graph {
public:
    int vertices;
    ::std::vector<::std::vector<int>> adj_list;

    directed_graph(int v) : vertices(v), adj_list(v) {}

    void add_edge(int u, int v) {
        adj_list[u].push_back(v);
    }

    void topological_sort_util(
        int v, 
        ::std::unordered_set<int>& visited, 
        ::std::stack<int>& result_stack) 
    {
        visited.insert(v);

        for (int neighbor : adj_list[v]) {
            if (visited.find(neighbor) == visited.end()) {
                topological_sort_util(neighbor, visited, result_stack);
            }
        }

        result_stack.push(v);
    }

    auto topological_sort() {
        ::std::stack<int> result_stack;
        ::std::unordered_set<int> visited;

        for (int i = 0; i < vertices; ++i) {
            if (visited.find(i) == visited.end()) {
                topological_sort_util(i, visited, result_stack);
            }
        }
        return result_stack;
    }
};

inline void print_topological_sort_stack(::std::stack<int> result_stack) {
    ::std::print("Topological Sort: ");
    while (!result_stack.empty()) {
        ::std::print("{} ", result_stack.top());
        result_stack.pop();
    }
    ::std::println();
}

inline auto topological_sort_example() { 
    directed_graph g(6);

    g.add_edge(5, 2);
    g.add_edge(5, 0);
    g.add_edge(4, 0);
    g.add_edge(4, 1);
    g.add_edge(2, 3);
    g.add_edge(3, 1);

    return g.topological_sort();
}

} // namespace dsnugee

#endif
