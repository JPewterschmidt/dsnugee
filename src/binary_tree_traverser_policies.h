#ifndef NUGEE_BINARY_TREE_TRAVERSER_POLICIES
#define NUGEE_BINARY_TREE_TRAVERSER_POLICIES

#include "helpers.h"
#include "binary_tree_node_concepts.h"

BEGIN_NAMESPACE_DSNUGEE

namespace detials
{
    enum class left_visited{};
    enum class right_visited{};

    const auto* next_from_parent(auto& policy, is_binary_tree_node auto const* node) noexcept
    {
        if (node->is_left_child())
            return policy.next(node->parent(), detials::left_visited{});
        else if (node->is_right_child())
            return policy.next(node->parent(), detials::right_visited{});
        
        // or `node` is the root node
        return decltype(node){};
    }

    const auto* prev_from_parent(auto& policy, is_binary_tree_node auto const* node) noexcept
    {
        if (node->is_left_child())
            return policy.prev(node->parent(), detials::left_visited{});
        else if (node->is_right_child())
            return policy.prev(node->parent(), detials::right_visited{});

        return decltype(node){};
    }
}

template<is_binary_tree_node Node>
class root_first
{
public:   
    using const_node_ptr = const Node*;

public:
    const_node_ptr first_node_by_root(const_node_ptr root) noexcept { return root; }
    const_node_ptr last_node_by_root(const_node_ptr root) noexcept 
    {
        const_node_ptr cur{ root }, result{};
        while (true)
        {
            result = cur->right_most_leaf();
            if (!result->has_child()) break;
            cur = result->left();
        }
        return result;
    }

    const_node_ptr next(const_node_ptr node) noexcept
    {
        if (!node) [[unlikely]] return nullptr;
        if (node->left()) return node->left();
        else if (node->right()) return node->right();
        return detials::next_from_parent(*this, node);
    }

    const_node_ptr prev(const_node_ptr node) 
    {
        assert(node);
        const_node_ptr result{};
        if (node->is_right_child())
        {
            const_node_ptr possible_prev{};
            if (auto p = node->parent(); p && p->left())
            {
                possible_prev = p->left()->right_most_leaf();
            }
            else if (p)
            {
                return p;
            }

            const_node_ptr pp_left{};
            while ((pp_left = possible_prev->left()))
            {
                possible_prev = pp_left->right_most_leaf();
            }
            result = possible_prev;
        }
        else if (node->is_left_child())
        {
            result = node->parent();
        }
        else result = nullptr;

        return result;
    }       

    const_node_ptr next(const_node_ptr node, detials::left_visited) noexcept
    {
        if (auto ch = node->right(); ch) return ch;
        return detials::next_from_parent(*this, node);
    }

    const_node_ptr next(const_node_ptr node, detials::right_visited) noexcept
    {
        return detials::next_from_parent(*this, node);
    }

};

template<is_binary_tree_node Node>
class root_last
{
public:   
    using const_node_ptr = const Node*;

public:
    const_node_ptr first_node_by_root(const_node_ptr root) noexcept
    {
        return root->left_most_leaf();
    }

    const_node_ptr last_node_by_root(const_node_ptr root) noexcept 
    { 
        return root; 
    }

    const_node_ptr next(const_node_ptr node) noexcept
    {
        if (!node) [[unlikely]] return nullptr;
        if (node->is_leaf())
        {
            return detials::next_from_parent(*this, node);
        }
        if (node->is_right_child())
            return node->parent();
        return detials::next_from_parent(*this, node);
    }

    const_node_ptr next(const_node_ptr node, detials::left_visited) noexcept
    {
        const_node_ptr rchild{ node->right() };
        if (!rchild) return node;

        const_node_ptr cur{ rchild };
        while (cur)
        {
            cur = cur->left_most_leaf();
            if (cur->is_leaf()) break;
            cur = cur->right();
        }
        return cur;
    }

    const_node_ptr next(const_node_ptr node, detials::right_visited) noexcept
    {
        return node;
    }

    const_node_ptr prev(const_node_ptr node, detials::left_visited) noexcept
    {
        return detials::prev_from_parent(*this, node);
    }

    const_node_ptr prev(const_node_ptr node, detials::right_visited) noexcept
    {
        const_node_ptr lchild = node->left();
        if (!lchild)
            return detials::prev_from_parent(*this, node);
        return lchild;
    }

    const_node_ptr prev(const_node_ptr node) noexcept
    {
        assert(node);
        const_node_ptr result = node->right() ? node->right() : node->left();
        if (!result) 
            return detials::prev_from_parent(*this, node);
        return result;
    }
};

END_NAMESPACE_DSNUGEE

#endif
