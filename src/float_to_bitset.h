#ifndef NUGEE_FLOAT_TO_BITSET_H
#define NUGEE_FLOAT_TO_BITSET_H

#include <bitset>
#include <cstdint>
#include <concepts>
#include <cmath>
#include "helpers.h"

BEGIN_NAMESPACE_DSNUGEE

// See also https://www.bilibili.com/video/BV1ps4y1d73V/?p=30&share_source=copy_web&vd_source=28b3766cd53cb71501bb1d0ed820805b&t=502

template<::std::size_t Sz>
struct uint_with_size
{
};

template<> struct uint_with_size<sizeof(uint8_t)> { using type = uint8_t; };
template<> struct uint_with_size<sizeof(uint16_t)>{ using type = uint16_t; };
template<> struct uint_with_size<sizeof(uint32_t)>{ using type = uint32_t; };
template<> struct uint_with_size<sizeof(uint64_t)>{ using type = uint64_t; };

template<::std::size_t Sz>
using uint_with_size_t = typename uint_with_size<Sz>::type;

auto to_bitset(::std::floating_point auto number)
{
    auto temp = ::std::bit_cast<uint_with_size_t<sizeof(number)>>(number);
    return ::std::bitset<sizeof(number) * 8>{ temp };
}

template<::std::floating_point FloatT>
FloatT to_floating(::std::bitset<sizeof(FloatT) * 8> bits) 
{
    static constexpr int total_bits = sizeof(FloatT) * 8;
    static constexpr int exponent_bits = (total_bits == 32) ? 8 : 11;
    static constexpr int mantissa_bits = (total_bits == 32) ? 23 : 52;
    static constexpr int exponent_bias = (total_bits == 32) ? 127 : 1023;
    static constexpr int msb = total_bits - 1;

    const int sign = bits[msb] ? -1 : 1;
    int exponent{};
    for (int i = total_bits - 2; i >= mantissa_bits; --i)
    {
        exponent = (exponent << 1) | bits[i];
    }
    exponent -= exponent_bias;
    FloatT mantissa = 1.0;
    FloatT fraction = 1.0;
    for (int i = mantissa_bits - 1; i >= 0; --i)
    {
        fraction /= 2.0;
        if (bits[i])
            mantissa += fraction;
    }
    return sign * ::std::pow(2.0, exponent) * mantissa;
}

END_NAMESPACE_DSNUGEE

#endif
