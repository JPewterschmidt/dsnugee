#ifndef NUGEE_FIXED_POINT_MULTIPLIER_SIMULATOR_H
#define NUGEE_FIXED_POINT_MULTIPLIER_SIMULATOR_H

#include <bitset>
#include "helpers.h"

BEGIN_NAMESPACE_DSNUGEE

template<::std::size_t N, template<size_t> typename ALU>
class fixed_point_multiplier_simulator
{
public:
    using rep = ::std::bitset<N>;

    fixed_point_multiplier_simulator(const rep& x, const rep& y)
    {
        // assume both the rep are true form.
        const bool x_sign = x[N - 1];
        const bool y_sign = y[N - 1];
        m_sign = x_sign ^ y_sign;

        m_x = ::std::move(x);
        m_mq = ::std::move(y);
        m_x[N - 1] = 0;
        m_mq[N - 1] = 0;
    }

    rep execute() 
    {
        for (::std::size_t i{}; i < numeric_bitlen(); ++i)
        {
            if (first_multip_lowerbit())
            {
                ALU<N>{}.add(m_acc, m_x);
            }
            m_mq >>= 1;
            m_mq[N - 1] = m_acc[0];
            m_acc >>= 1;
        }
        m_acc[N - 1] = m_sign;

        return m_acc;
    }

private:
    bool first_multip_lowerbit() const
    {
        return m_mq[0];
    }

    static consteval ::std::size_t numeric_bitlen() noexcept 
    {
        return N - 1;
    }

private:
    rep m_x{};
    rep m_acc{};
    rep m_mq{};
    bool m_sign{};
};

END_NAMESPACE_DSNUGEE

#endif
