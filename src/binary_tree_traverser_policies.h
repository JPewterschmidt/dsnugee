#ifndef NUGEE_BINARY_TREE_TRAVERSER_POLICIES
#define NUGEE_BINARY_TREE_TRAVERSER_POLICIES

#include "helpers.h"
#include "binary_tree_node_concepts.h"

BEGIN_NAMESPACE_DSNUGEE

template<is_binary_tree_node Node>
class root_first
{
public:   
    using const_node_ptr = const Node*;

private:
    enum class left_visited{};
    enum class right_visited{};
    
public:
    const_node_ptr init(const_node_ptr root) noexcept { return root; }

    const_node_ptr next(const_node_ptr node) noexcept
    {
        if (!node) [[unlikely]] return nullptr;
        if (node->left()) return node->left();
        else if (node->right()) return node->right();
        return next_from_parent(node);
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

private:
    const_node_ptr next(const_node_ptr node, left_visited) noexcept
    {
        if (auto ch = node->right(); ch) return ch;
        return next_from_parent(node);
    }

    const_node_ptr next(const_node_ptr node, right_visited) noexcept
    {
        return next_from_parent(node);
    }

    const_node_ptr next_from_parent(const_node_ptr node) noexcept
    {
        if (node->is_left_child())
            return next(node->parent(), left_visited{});
        else if (node->is_right_child())
            return next(node->parent(), right_visited{});
        
        // or `node` is the root node
        return nullptr;
    }
};

template<is_binary_tree_node Node>
class root_last
{
public:   
    using const_node_ptr = const Node*;

private:
    enum class left_visited{};
    enum class right_visited{};
    
public:
    const_node_ptr init(const_node_ptr root) noexcept
    {
        return root->left_most_leaf();
    }

    const_node_ptr next(const_node_ptr node) noexcept
    {
        if (!node) [[unlikely]] return nullptr;
        if (!node->has_child())
        {
            return next_from_parent(node);
        }
    }

private:
    // TODO
};

END_NAMESPACE_DSNUGEE

#endif
