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

void bobble_sort(::std::forward_iterator auto first, ::std::forward_iterator auto last)
{
    if (first == last) 
        return;

    for (auto pivot = first; pivot != last; ::std::advance(pivot, 1))
    {
        for (auto i = ::std::next(pivot); i != last; ::std::advance(i, 1))
        {
            if (::std::less{}(*i, *pivot))
                ::std::swap(*i, *pivot);
        }
    }
}

void insert_sort(::std::random_access_iterator auto first, ::std::random_access_iterator auto last)
{
    if (first == last) 
        return;

    for (auto it = first + 1; it != last; ++it) 
    {
        auto key = *it;
        auto j = it - 1;

        while (j >= first && key < *j) 
        {
            *(j + 1) = *j;
            --j;
        }
        *(j + 1) = key;
    }
}

END_NAMESPACE_DSNUGEE

#endif
