// Copyright (C) 2020-2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#include <vector>

#include "gtest/gtest.h"
#include "hexl/number-theory/number-theory.hpp"
#include "hexl/util/compiler.hpp"

namespace intel {
namespace hexl {

TEST(NumberTheory, Log2) {
  ASSERT_EQ(0, Log2(1));
  ASSERT_EQ(1, Log2(2));
  ASSERT_EQ(2, Log2(4));
  ASSERT_EQ(3, Log2(8));
  ASSERT_EQ(4, Log2(16));
  ASSERT_EQ(5, Log2(32));
  ASSERT_EQ(6, Log2(64));
  ASSERT_EQ(7, Log2(128));
  ASSERT_EQ(8, Log2(256));
  ASSERT_EQ(9, Log2(512));
  ASSERT_EQ(10, Log2(1024));
  ASSERT_EQ(11, Log2(2048));
  ASSERT_EQ(12, Log2(4096));
  ASSERT_EQ(13, Log2(8192));
}

TEST(NumberTheory, MultiplyMod) {
  uint64_t modulus(2);
  ASSERT_EQ(0ULL, MultiplyMod(0, 0, modulus));
  ASSERT_EQ(0ULL, MultiplyMod(0, 1, modulus));
  ASSERT_EQ(0ULL, MultiplyMod(1, 0, modulus));
  ASSERT_EQ(1ULL, MultiplyMod(1, 1, modulus));

  modulus = 10;
  ASSERT_EQ(0ULL, MultiplyMod(0, 0, modulus));
  ASSERT_EQ(0ULL, MultiplyMod(0, 1, modulus));
  ASSERT_EQ(0ULL, MultiplyMod(1, 0, modulus));
  ASSERT_EQ(1ULL, MultiplyMod(1, 1, modulus));
  ASSERT_EQ(9ULL, MultiplyMod(7, 7, modulus));
  ASSERT_EQ(2ULL, MultiplyMod(6, 7, modulus));
  ASSERT_EQ(2ULL, MultiplyMod(7, 6, modulus));

  modulus = 2305843009211596801ULL;
  ASSERT_EQ(0ULL, MultiplyMod(0, 0, modulus));
  ASSERT_EQ(0ULL, MultiplyMod(0, 1, modulus));
  ASSERT_EQ(0ULL, MultiplyMod(1, 0, modulus));
  ASSERT_EQ(1ULL, MultiplyMod(1, 1, modulus));
  ASSERT_EQ(
      576460752302899200ULL,
      MultiplyMod(1152921504605798400ULL, 1152921504605798401ULL, modulus));
  ASSERT_EQ(
      576460752302899200ULL,
      MultiplyMod(1152921504605798401ULL, 1152921504605798400ULL, modulus));
  ASSERT_EQ(
      1729382256908697601ULL,
      MultiplyMod(1152921504605798401ULL, 1152921504605798401ULL, modulus));
  ASSERT_EQ(1ULL, MultiplyMod(2305843009211596800ULL, 2305843009211596800ULL,
                              modulus));
}

TEST(NumberTheory, MultiplyModPreCon) {
  uint64_t modulus(2);
  MultiplyFactor mf0(0, 64, modulus);
  MultiplyFactor mf1(1, 64, modulus);
  ASSERT_EQ(0ULL, MultiplyMod(0, 0, mf0.BarrettFactor(), modulus));
  ASSERT_EQ(0ULL, MultiplyMod(0, 1, mf1.BarrettFactor(), modulus));
  ASSERT_EQ(0ULL, MultiplyMod(1, 0, mf0.BarrettFactor(), modulus));
  ASSERT_EQ(1ULL, MultiplyMod(1, 1, mf1.BarrettFactor(), modulus));

  modulus = 10;
  MultiplyFactor mf6(6, 64, modulus);
  MultiplyFactor mf7(7, 64, modulus);
  ASSERT_EQ(0ULL, MultiplyMod(0, 0, mf0.BarrettFactor(), modulus));
  ASSERT_EQ(0ULL, MultiplyMod(0, 1, mf1.BarrettFactor(), modulus));
  ASSERT_EQ(0ULL, MultiplyMod(1, 0, mf0.BarrettFactor(), modulus));
  ASSERT_EQ(1ULL, MultiplyMod(1, 1, mf1.BarrettFactor(), modulus));
  ASSERT_EQ(9ULL, MultiplyMod(7, 7, mf7.BarrettFactor(), modulus));
  ASSERT_EQ(2ULL, MultiplyMod(6, 7, mf7.BarrettFactor(), modulus));
  ASSERT_EQ(2ULL, MultiplyMod(7, 6, mf6.BarrettFactor(), modulus));

  modulus = 2305843009211596801ULL;
  ASSERT_EQ(0ULL, MultiplyMod(0, 0, mf0.BarrettFactor(), modulus));
  ASSERT_EQ(0ULL, MultiplyMod(0, 1, mf1.BarrettFactor(), modulus));
  ASSERT_EQ(0ULL, MultiplyMod(1, 0, mf0.BarrettFactor(), modulus));
  ASSERT_EQ(1ULL, MultiplyMod(1, 1, mf1.BarrettFactor(), modulus));

  MultiplyFactor mf1152921504605798401(1152921504605798401ULL, 64, modulus);
  MultiplyFactor mf1152921504605798400(1152921504605798400ULL, 64, modulus);
  MultiplyFactor mf2305843009211596800(2305843009211596800ULL, 64, modulus);
  ASSERT_EQ(576460752302899200ULL,
            MultiplyMod(1152921504605798400ULL, 1152921504605798401ULL,
                        mf1152921504605798401.BarrettFactor(), modulus));
  ASSERT_EQ(576460752302899200ULL,
            MultiplyMod(1152921504605798401ULL, 1152921504605798400ULL,
                        mf1152921504605798400.BarrettFactor(), modulus));
  ASSERT_EQ(1729382256908697601ULL,
            MultiplyMod(1152921504605798401ULL, 1152921504605798401ULL,
                        mf1152921504605798401.BarrettFactor(), modulus));
  ASSERT_EQ(1ULL, MultiplyMod(2305843009211596800ULL, 2305843009211596800ULL,
                              mf2305843009211596800.BarrettFactor(), modulus));
}

TEST(NumberTheory, PowMod) {
  uint64_t modulus = 5;
  ASSERT_EQ(1ULL, PowMod(1, 0, modulus));
  ASSERT_EQ(1ULL, PowMod(1, 0xFFFFFFFFFFFFFFFFULL, modulus));
  ASSERT_EQ(3ULL, PowMod(2, 0xFFFFFFFFFFFFFFFFULL, modulus));

  modulus = 0x1000000000000000ULL;
  ASSERT_EQ(0ULL, PowMod(2, 60, modulus));
  ASSERT_EQ(0x800000000000000ULL, PowMod(2, 59, modulus));

  modulus = 131313131313;
  ASSERT_EQ(39418477653ULL, PowMod(2424242424, 16, modulus));
}

TEST(NumberTheory, IsPowerOfTwo) {
  std::vector<uint64_t> powers_of_two{1,   2,    4,    8,    16,    32,
                                      512, 1024, 2048, 4096, 16384, 32768};
  std::vector<uint64_t> not_powers_of_two{0, 3, 5, 7, 9, 31, 33, 1025, 4095};

  for (auto power_of_two : powers_of_two) {
    EXPECT_TRUE(IsPowerOfTwo(power_of_two));
  }

  for (auto not_power_of_two : not_powers_of_two) {
    EXPECT_FALSE(IsPowerOfTwo(not_power_of_two));
  }
}

TEST(NumberTheory, IsPrimitiveRoot) {
  uint64_t modulus = 11;
  ASSERT_TRUE(IsPrimitiveRoot(10, 2, modulus));
  ASSERT_FALSE(IsPrimitiveRoot(9, 2, modulus));
  ASSERT_FALSE(IsPrimitiveRoot(10, 4, modulus));

  modulus = 29;
  ASSERT_TRUE(IsPrimitiveRoot(28, 2, modulus));
  ASSERT_TRUE(IsPrimitiveRoot(12, 4, modulus));
  ASSERT_FALSE(IsPrimitiveRoot(12, 2, modulus));
  ASSERT_FALSE(IsPrimitiveRoot(12, 8, modulus));

  modulus = 1234565441ULL;
  ASSERT_TRUE(IsPrimitiveRoot(1234565440ULL, 2, modulus));
  ASSERT_TRUE(IsPrimitiveRoot(960907033ULL, 8, modulus));
  ASSERT_TRUE(IsPrimitiveRoot(1180581915ULL, 16, modulus));
  ASSERT_FALSE(IsPrimitiveRoot(1180581915ULL, 32, modulus));
  ASSERT_FALSE(IsPrimitiveRoot(1180581915ULL, 8, modulus));
  ASSERT_FALSE(IsPrimitiveRoot(1180581915ULL, 2, modulus));
}

TEST(NumberTheory, MinimalPrimitiveRoot) {
  uint64_t modulus = 11;

  ASSERT_EQ(10ULL, MinimalPrimitiveRoot(2, modulus));

  modulus = 29;
  ASSERT_EQ(28ULL, MinimalPrimitiveRoot(2, modulus));
  ASSERT_EQ(12ULL, MinimalPrimitiveRoot(4, modulus));

  modulus = 1234565441;
  ASSERT_EQ(1234565440ULL, MinimalPrimitiveRoot(2, modulus));
  ASSERT_EQ(249725733ULL, MinimalPrimitiveRoot(8, modulus));
}

TEST(NumberTheory, InverseMod) {
  uint64_t input;
  uint64_t modulus;

  input = 1, modulus = 2;
  ASSERT_EQ(1ULL, InverseMod(input, modulus));

#ifdef HEXL_DEBUG
  input = 2, modulus = 2;
  EXPECT_ANY_THROW(InverseMod(input, modulus));

  input = 0xFFFFFE, modulus = 2;
  EXPECT_ANY_THROW(InverseMod(input, modulus));

  input = 12345, modulus = 3;
  EXPECT_ANY_THROW(InverseMod(input, modulus));
#endif

  input = 3, modulus = 2;
  ASSERT_EQ(1ULL, InverseMod(input, modulus));

  input = 0xFFFFFF, modulus = 2;
  ASSERT_EQ(1ULL, InverseMod(input, modulus));

  input = 5, modulus = 19;
  ASSERT_EQ(4ULL, InverseMod(input, modulus));

  input = 4, modulus = 19;
  ASSERT_EQ(5ULL, InverseMod(input, modulus));
}

TEST(NumberTheory, MultiplyModLazy64) {
  uint64_t modulus = 2;
  uint64_t y = 0;
  ASSERT_EQ(0ULL, MultiplyModLazy<64>(0, y, modulus));
  ASSERT_EQ(0ULL, MultiplyModLazy<64>(1, y, modulus));
  y = 1;
  ASSERT_EQ(0ULL, MultiplyModLazy<64>(0, y, modulus));
  ASSERT_EQ(1ULL, MultiplyModLazy<64>(1, y, modulus));

  modulus = 10;
  y = 0;
  ASSERT_EQ(0ULL, MultiplyModLazy<64>(0, y, modulus));
  ASSERT_EQ(0ULL, MultiplyModLazy<64>(1, y, modulus));
  y = 1;
  ASSERT_EQ(0ULL, MultiplyModLazy<64>(0, y, modulus));
  ASSERT_EQ(1ULL, MultiplyModLazy<64>(1, y, modulus));
  y = 6;
  ASSERT_EQ(2ULL, MultiplyModLazy<64>(7, y, modulus));
  y = 7;
  ASSERT_EQ(9ULL, MultiplyModLazy<64>(7, y, modulus));
  ASSERT_EQ(2ULL, MultiplyModLazy<64>(6, y, modulus));

  modulus = 2305843009211596801ULL;
  y = 0;
  ASSERT_EQ(0ULL, MultiplyModLazy<64>(0, y, modulus));
  ASSERT_EQ(0ULL, MultiplyModLazy<64>(1, y, modulus));
  y = 1;
  ASSERT_EQ(0ULL, MultiplyModLazy<64>(0, y, modulus));
  ASSERT_EQ(1ULL, MultiplyModLazy<64>(1, y, modulus));
  y = 1152921504605798400ULL;
  ASSERT_EQ(576460752302899200ULL,
            MultiplyModLazy<64>(1152921504605798401ULL, y, modulus));
  y = 1152921504605798401ULL;
  ASSERT_EQ(576460752302899200ULL,
            MultiplyModLazy<64>(1152921504605798400ULL, y, modulus));
  ASSERT_EQ(1729382256908697601ULL,
            MultiplyModLazy<64>(1152921504605798401ULL, y, modulus));
  y = 2305843009211596800ULL;
  ASSERT_EQ(2305843009211596802ULL,
            MultiplyModLazy<64>(2305843009211596800ULL, y, modulus));
}

TEST(NumberTheory, MultiplyModLazy52) {
  uint64_t modulus = 2;
  uint64_t y = 0;
  ASSERT_EQ(0ULL, MultiplyModLazy<52>(0, y, modulus));
  ASSERT_EQ(0ULL, MultiplyModLazy<52>(1, y, modulus));
  y = 1;
  ASSERT_EQ(0ULL, MultiplyModLazy<52>(0, y, modulus));
  ASSERT_EQ(1ULL, MultiplyModLazy<52>(1, y, modulus));

  modulus = 10;
  y = 0;
  ASSERT_EQ(0ULL, MultiplyModLazy<52>(0, y, modulus));
  ASSERT_EQ(0ULL, MultiplyModLazy<52>(1, y, modulus));
  y = 1;
  ASSERT_EQ(0ULL, MultiplyModLazy<52>(0, y, modulus));
  ASSERT_EQ(1ULL, MultiplyModLazy<52>(1, y, modulus));
  y = 6;
  ASSERT_EQ(2ULL, MultiplyModLazy<52>(7, y, modulus));
  y = 7;
  ASSERT_EQ(9ULL, MultiplyModLazy<52>(7, y, modulus));
  ASSERT_EQ(2ULL, MultiplyModLazy<52>(6, y, modulus));

#ifdef HEXL_DEBUG
  y = 1152921504605798400ULL;
  EXPECT_ANY_THROW(MultiplyModLazy<52>(1152921504605798401ULL, y, modulus));
  y = 1152921504605798401ULL;
  EXPECT_ANY_THROW(MultiplyModLazy<52>(1152921504605798400ULL, y, modulus));
  EXPECT_ANY_THROW(MultiplyModLazy<52>(1152921504605798401ULL, y, modulus));
  y = 2305843009211596800ULL;
  EXPECT_ANY_THROW(MultiplyModLazy<52>(2305843009211596800ULL, y, modulus));
#endif
}

TEST(NumberTheory, MaximumValue) {
  ASSERT_EQ(MaximumValue(64), 0xffffffffffffffff);
  ASSERT_EQ(MaximumValue(52), 0xfffffffffffff);
}

TEST(NumberTheory, IsPrime) {
  ASSERT_TRUE(IsPrime(2));
  ASSERT_TRUE(IsPrime(3));
  ASSERT_TRUE(IsPrime(5));
  ASSERT_TRUE(IsPrime(2305843009211596801ULL));
  ASSERT_TRUE(IsPrime(2305843009211596801ULL));
  ASSERT_TRUE(IsPrime(36893488147419103ULL));
  ASSERT_TRUE(IsPrime(0xffffffffffc0001ULL));
  ASSERT_TRUE(IsPrime(0xffffee001));

  ASSERT_FALSE(IsPrime(72307ULL * 59399ULL));
  ASSERT_FALSE(IsPrime(2305843009211596802ULL));
  ASSERT_FALSE(IsPrime(36893488147419107ULL));
}

TEST(NumberTheory, GeneratePrimes) {
  for (int bit_size = 40; bit_size < 62; ++bit_size) {
    std::vector<uint64_t> primes = GeneratePrimes(10, bit_size, 4096);
    ASSERT_EQ(primes.size(), 10);
    for (const auto& prime : primes) {
      ASSERT_EQ(prime % 8192, 1);
      ASSERT_TRUE(IsPrime(prime));
      ASSERT_TRUE(prime <= (1ULL << (bit_size + 1)));
      ASSERT_TRUE(prime >= (1ULL << bit_size));
    }
  }
}

TEST(NumberTheory, AddUInt64) {
  uint64_t result;
  EXPECT_EQ(0, AddUInt64(1, 0, &result));
  EXPECT_EQ(1, result);

  EXPECT_EQ(0, AddUInt64(1, 1, &result));
  EXPECT_EQ(2, result);

  EXPECT_EQ(0, AddUInt64(10, 7, &result));
  EXPECT_EQ(17, result);

  EXPECT_EQ(0, AddUInt64(1ULL << 32, 1ULL << 16, &result));
  EXPECT_EQ(4295032832, result);

  // Test overflow
  EXPECT_EQ(1, AddUInt64(1ULL << 63, 1ULL << 63, &result));
  EXPECT_EQ(0, result);

  EXPECT_EQ(1, AddUInt64((1ULL << 63) + 1, 1ULL << 63, &result));
  EXPECT_EQ(1, result);

  EXPECT_EQ(1, AddUInt64((1ULL << 63) + 13, (1ULL << 63) + 17, &result));
  EXPECT_EQ(30, result);
}

TEST(NumberTheory, AddUIntMod) {
  {
    uint64_t modulus = 2;
    EXPECT_EQ(1, AddUIntMod(1, 0, modulus));
    EXPECT_EQ(1, AddUIntMod(0, 1, modulus));
    EXPECT_EQ(0, AddUIntMod(1, 1, modulus));
  }

  {
    uint64_t modulus = 10;
    EXPECT_EQ(0, AddUIntMod(3, 7, modulus));
    EXPECT_EQ(0, AddUIntMod(4, 6, modulus));
    EXPECT_EQ(1, AddUIntMod(5, 6, modulus));
    EXPECT_EQ(2, AddUIntMod(6, 6, modulus));
  }

  {
    uint64_t modulus = 1ULL << 63;
    EXPECT_EQ(10, AddUIntMod(3, 7, modulus));
    EXPECT_EQ(0, AddUIntMod(modulus - 1, 1, modulus));
    EXPECT_EQ(1, AddUIntMod(modulus - 1, 2, modulus));
    EXPECT_EQ(modulus - 4, AddUIntMod(modulus - 1, modulus - 3, modulus));
  }
}

TEST(NumberTheory, SubUIntMod) {
  {
    uint64_t modulus = 2;
    EXPECT_EQ(1, SubUIntMod(1, 0, modulus));
    EXPECT_EQ(1, SubUIntMod(0, 1, modulus));
    EXPECT_EQ(0, SubUIntMod(1, 1, modulus));
  }

  {
    uint64_t modulus = 10;
    EXPECT_EQ(6, SubUIntMod(3, 7, modulus));
    EXPECT_EQ(8, SubUIntMod(4, 6, modulus));
    EXPECT_EQ(2, SubUIntMod(6, 4, modulus));
    EXPECT_EQ(0, SubUIntMod(6, 6, modulus));
  }

  {
    uint64_t modulus = 1ULL << 63;
    EXPECT_EQ(modulus - 4, SubUIntMod(3, 7, modulus));
    EXPECT_EQ(modulus - 2, SubUIntMod(modulus - 1, 1, modulus));
    EXPECT_EQ(3, SubUIntMod(2, modulus - 1, modulus));
    EXPECT_EQ(2, SubUIntMod(modulus - 1, modulus - 3, modulus));
  }
}

TEST(NumberTheory, DivideUInt128UInt64Lo) {
  EXPECT_EQ(0ULL, DivideUInt128UInt64Lo(0ULL, 0ULL, 2ULL));
  EXPECT_EQ(9460151ULL, DivideUInt128UInt64Lo(0ULL, 4294908658ULL, 454ULL));
  EXPECT_EQ(10ULL, DivideUInt128UInt64Lo(0ULL, 4294908658ULL, 429490865ULL));
  EXPECT_EQ(0xffffffffffffffffULL,
            DivideUInt128UInt64Lo(0ULL, 0xffffffffffffffffULL, 1ULL));
  EXPECT_EQ(1ULL, DivideUInt128UInt64Lo(0ULL, 0xfffffffULL, 0xfffffffULL));
  EXPECT_EQ(4294908659ULL,
            DivideUInt128UInt64Lo(4294908658ULL, 0xffffffffffffffffULL,
                                  0xffffffffffffffffULL));
}

TEST(NumberTheory, MSB) {
  EXPECT_EQ(60ULL, MSB(2305843009213689601));  // 2**61 - 4351
  EXPECT_EQ(59ULL, MSB(1152921504606844417));  // 2**60 - 2559
  EXPECT_EQ(59ULL, MSB(1152921504606844289));  // 2**60 - 2687
  EXPECT_EQ(40ULL, MSB((1ULL << 40) + 1));
  EXPECT_EQ(40ULL, MSB(1ULL << 40));
  EXPECT_EQ(39ULL, MSB((1ULL << 40) - 1));
  EXPECT_EQ(8ULL, MSB(256));
  EXPECT_EQ(0ULL, MSB(1));
}

TEST(NumberTheory, SetBit) {
  EXPECT_EQ(0b0001, SetBit(0b0000, 0, 1));
  EXPECT_EQ(0b0010, SetBit(0b0000, 1, 1));
  EXPECT_EQ(0b0100, SetBit(0b0000, 2, 1));
  EXPECT_EQ(0b1000, SetBit(0b0000, 3, 1));

  EXPECT_EQ(0b1110, SetBit(0b1111, 0, 0));
  EXPECT_EQ(0b1110, SetBit(0b1111, 1, 0));
  EXPECT_EQ(0b1011, SetBit(0b1111, 2, 0));
  EXPECT_EQ(0b0111, SetBit(0b1111, 3, 0));
}

}  // namespace hexl
}  // namespace intel
