#include "disjoint.h"

using namespace dsnugee;

int disjoint_set::find(int i) const
{
    if (auto next_root = storage_.at(static_cast<size_t>(i)); next_root < 0) 
        return i;
    else return find(next_root);
}

void disjoint_set::union_sets(int root1, int root2)
{
    storage_.at(static_cast<size_t>(root2)) = root1;
}
