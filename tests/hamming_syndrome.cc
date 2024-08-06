#include "hamming_syndrome.h"
#include "gtest/gtest.h"
#include <vector>
#include <random>
#include <ranges>

using namespace dsnugee;

namespace r = ::std::ranges;
namespace rv = r::views;

TEST(hamming_syndrome, basic)
{
    static constinit ::std::size_t scale{ 16 };
    ::std::random_device rd;
    ::std::mt19937 gen{rd()};
    ::std::uniform_int_distribution<> dist(0, 1);
    auto bits = rv::iota(0ull, scale) | rv::transform([&](int) { return dist(gen); }) | r::to<::std::vector<bool>>();
    const auto result = hamming_syndrome(bits);

    // Make `bits` a well preparaed block
    for (::std::size_t i{}, j{ result }; i < scale; ++i, j >>= 1)
    {
        if (j & 1u) bits[1 << i] = not bits[1 << i];
    }
    ASSERT_EQ(hamming_syndrome(bits), 0);

    // For well preparaed block, hamming code could tell you which one bit has been flipped.
    auto flip = [](auto&& bit) { bit = not bit; };   

    flip(bits[9]);
    ASSERT_EQ(hamming_syndrome(bits), 9);
    flip(bits[9]);

    flip(bits[15]);
    ASSERT_EQ(hamming_syndrome(bits), 15);
    flip(bits[15]);
}
