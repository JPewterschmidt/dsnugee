#ifndef NUGEE_BINARY_TREE_POLICY
#define NUGEE_BINARY_TREE_POLICY

#include "helpers.h"
#include <concepts>
#include <cassert>
#include "binary_tree_node_concepts.h"

BEGIN_NAMESPACE_DSNUGEE

class plain_bt_policy
{
public:
    auto* find_parent(
        is_binary_tree_node auto const* const root, 
        is_binary_tree_node auto const* const newnode) const noexcept 
    {
        auto* cur{ root };
        decltype(cur) previous{};
        while (cur) 
        {
            if (auto ordering = *newnode <=> *cur; 
                ordering == ::std::partial_ordering::less)
            {
                previous = ::std::exchange(cur, cur->left());
            }
            else if (ordering == ::std::partial_ordering::greater)
            {
                previous = ::std::exchange(cur, cur->right());
            }
            else
            {
                previous = ::std::exchange(cur, nullptr);
            }
        }
        return previous;
    }

    // this function will return the new parential node.
    auto* insert_as_child(
        is_binary_tree_node auto* parent, 
        is_binary_tree_node auto* node)
    {
        assert(parent);

        node->set_parent(parent);

        if (auto ordering = *node <=> *parent; 
            ordering == ::std::partial_ordering::less)
        {
            assert(!parent->left());
            parent->set_left(node);;
        }
        else if (ordering == ::std::partial_ordering::greater)
        {
            assert(!parent->right());
            parent->set_right(node);
        }
        else if (ordering == ::std::partial_ordering::unordered)
        {
            throw not_implement_exception{};
        }

        return parent;
    }
};

END_NAMESPACE_DSNUGEE

#endif
