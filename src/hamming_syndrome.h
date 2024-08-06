#ifndef NUGEE_HAMMING_SYNFROME_H
#define NUGEE_HAMMING_SYNFROME_H

#include <ranges>
#include <algorithm>
#include <vector>
#include "helpers.h"

BEGIN_NAMESPACE_DSNUGEE

// Credit: 

inline ::std::size_t hamming_syndrome(const ::std::vector<bool>& bits) 
{
    namespace r = ::std::ranges;
    namespace rv = r::views;

    return r::fold_left_first(
        bits
        | rv::enumerate
        | rv::filter([](auto&& index_bit) { auto&& [i, bit] = index_bit; return bit; }) 
        | rv::keys
        , ::std::bit_xor<::std::size_t>{}
    ).value_or(0);
}

END_NAMESPACE_DSNUGEE

#endif
