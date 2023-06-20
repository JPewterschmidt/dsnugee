#ifndef DSNUGEE_BINARY_TREE
#define DSNUGEE_BINARY_TREE

#include <string>
#include <memory>
#include "helpers.h"

BEGIN_NAMESPACE_DSNUGEE

struct bt_node
{
    ::std::string element;
    bt_node* left{}, right{};
};

template<typename Policy>
concept bt_policy_concept = requires(Policy p)
{
};

template<bt_policy_concept Policy>
class binary_tree
{
public:
    binary_tree();
    

private:
    ::std::vector<::std::unique_ptr<bt_node>> s_;
    Policy p_;
};

END_NAMESPACE_DSNUGEE

#endif
