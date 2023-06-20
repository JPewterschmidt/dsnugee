#ifndef NUGEE_DISJOINT_SET
#define NUGEE_DISJOINT_SET

#include <vector>
#include "helpers.h"

BEGIN_NAMESPACE_DSNUGEE

class disjoint_set
{
public:
    disjoint_set(size_t num_elements) 
        : storage_(num_elements, -1)
    {
    }

    int find(int i) const;
    void union_sets(int root1, int root2);
    const auto& storage() const noexcept { return storage_; }
    
private:
    ::std::vector<int> storage_;
};

END_NAMESPACE_DSNUGEE

#endif
