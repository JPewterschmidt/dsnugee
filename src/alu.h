#ifndef NUGEE_ALU_H
#define NUGEE_ALU_H

#include "helpers.h"
#include <bitset>
#include <cstdint>

BEGIN_NAMESPACE_DSNUGEE

template<::std::size_t N>
struct alu_base
{
    static consteval ::std::size_t number_bits() noexcept { return N; }
};

template<::std::size_t N>
class alu : public alu_base<N>
{
public:
    using rep = ::std::bitset<alu_base<N>::number_bits()>;
    
    void add(rep& x, const rep& y, bool carry_in = false)
    {
        bool carry = carry_in;
        for (::std::size_t i{}; i < this->number_bits(); ++i)
        {
            const bool bit_x = x[i];
            const bool bit_y = y[i];
            const bool sum = (bit_x ^ bit_y) ^ carry;
            carry = (bit_x && bit_y) || (bit_x && carry) || (bit_y && carry);
            x[i] = sum;
        }
    }
};

END_NAMESPACE_DSNUGEE

#endif
