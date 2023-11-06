#ifndef NUGEE_BINARY_TREE_NODE_CONCEPTS
#define NUGEE_BINARY_TREE_NODE_CONCEPTS

#include "helpers.h"

#include <concepts>
#include <cassert>

BEGIN_NAMESPACE_DSNUGEE

template<typename BTNode>
concept is_binary_tree_node = requires(BTNode node)
{
    { node.left() }   -> ::std::same_as<const BTNode*>;
    { node.right() }  -> ::std::same_as<const BTNode*>;
    { node.parent() } -> ::std::same_as<const BTNode*>;
    node.set_left(::std::declval<BTNode*>());
    node.set_right(::std::declval<BTNode*>());
    node.set_parent(::std::declval<BTNode*>());
    node <=> node;
};

END_NAMESPACE_DSNUGEE

#endif
