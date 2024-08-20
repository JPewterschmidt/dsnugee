#ifndef DSNUGEE_SORT
#define DSNUGEE_SORT

#include <algorithm>
#include "helpers.h"

BEGIN_NAMESPACE_DSNUGEE

void quick_sort(::std::forward_iterator auto first, ::std::forward_iterator auto last)
{
    if (first == last)
        return;
 
    auto pivot = *std::next(first, std::distance(first, last) / 2);
    auto middle1 = std::partition(first, last, [pivot](const auto& em)
    {
        return em < pivot;
    });
    auto middle2 = std::partition(middle1, last, [pivot](const auto& em)
    {
        return !(pivot < em);
    });
 
    quick_sort(first, middle1);
    quick_sort(middle2, last);
}

END_NAMESPACE_DSNUGEE

#endif
