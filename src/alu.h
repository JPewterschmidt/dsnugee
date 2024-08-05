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

struct alu_flags
{
    bool was_carry      : 1 = {};
    bool was_overflow   : 1 = {};
    bool was_zero       : 1 = {};
    bool was_signed     : 1 = {};
};

template<::std::size_t N>
class alu : public alu_base<N>
{
public:
    using rep = ::std::bitset<alu_base<N>::number_bits()>;
    
    void add(rep& x, const rep& y, bool carry_in = false)
    {
        m_flags = {};
        bool carry = carry_in;
        const bool msb_x = x[this->most_signaficant_bit_index()];
        const bool msb_y = y[this->most_signaficant_bit_index()];

        for (::std::size_t i{}; i < this->number_bits(); ++i)
        {
            const bool bit_x = x[i];
            const bool bit_y = y[i];
            const bool sum = (bit_x ^ bit_y) ^ carry;
            carry = (bit_x && bit_y) || (bit_x && carry) || (bit_y && carry);
            x[i] = sum;
        }
        const bool msb_result = x[this->most_signaficant_bit_index()];
        m_flags = { 
            .was_carry = carry, 
            .was_overflow = (msb_x == msb_y) && (msb_x != msb_result), 
            .was_zero = x.none(), 
            .was_signed = x[this->most_signaficant_bit_index()],
        };

        // handle sign extension if needed (for larger bitsets)
        if (x[this->most_signaficant_bit_index()])
        {
            for (::std::size_t i{ this->number_bits() }; i < x.size(); ++i)
                x[i] = 1;
        }
    }

    alu_flags flags() const noexcept { return m_flags; }

    static consteval ::std::size_t most_signaficant_bit_index() noexcept 
    {
        return alu_base<N>::number_bits() - 1;
    }

private:
    alu_flags m_flags{};
};

END_NAMESPACE_DSNUGEE

#endif
