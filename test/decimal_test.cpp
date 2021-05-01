#include "gtest/gtest.h"

#include "decimal.h"

using namespace dec;

TEST(Decimal, StringCtor0) {
    auto d = Decimal("0");

    ASSERT_EQ(0L, d.mantissa());
    ASSERT_EQ(0, d.exponent());
}

TEST(Decimal, A2) {
    auto d = Decimal("2");
    ASSERT_EQ(2L, d.mantissa());
    ASSERT_EQ(0, d.exponent());
}

TEST(Decimal, SimpleAsPi) {
    auto d = Decimal("3.14159265358979");

    ASSERT_EQ(314159265358979L, d.mantissa());
    ASSERT_EQ(-14, d.exponent());
}

TEST(Decimal, Ten10) {
    auto d = Decimal("10000.10");
    ASSERT_EQ(100001, d.mantissa());
    ASSERT_EQ(-1, d.exponent());
}

TEST(Decimal, Minus5) {
    auto d = Decimal("00000.00001");
    ASSERT_EQ(1, d.mantissa());
    ASSERT_EQ(-5, d.exponent());
}

TEST(Decimal, Normalized5) {
    auto d = Decimal("0.0001");
    ASSERT_EQ(10, d.normalize(-5));
}

TEST(Decimal, TwoPTwo) {
    auto d = Decimal("2");
    
    auto f = d + d;

    ASSERT_EQ(4, f.mantissa());
}

TEST(Decimal, TenPlusHundred) {
    auto q = Decimal("0.01");
    auto r = Decimal("0.001");
    auto result = q + r;

    ASSERT_EQ(11, result.mantissa());
    ASSERT_EQ(-3, result.exponent());
}

TEST(Decimal, OverlappingAdd) {
    auto q = Decimal("0.01");
    auto r = Decimal("0.011");
    auto result = q + r;

    ASSERT_EQ(21, result.mantissa());
    ASSERT_EQ(-3, result.exponent());
}

TEST(Decimal, x22) {
    auto q = Decimal("2");
    auto twox = q * q;

    ASSERT_EQ(Decimal("4"), twox);
}

TEST(Decimal, x001) {
    auto q = Decimal("0.001");
    auto twox = q * q;

    ASSERT_EQ(1, twox.mantissa());
    ASSERT_EQ(-6, twox.exponent());
}

TEST(Decimal, VWAP) {
    Decimal numerator("0"), denominator("0");
    for(int i=0; i<400; i++) {
        numerator += Decimal("11000") * Decimal("0.233");
        denominator += Decimal("0.233");
    }
    auto vwap = numerator / denominator;
    ASSERT_EQ(11, vwap.mantissa());
    ASSERT_EQ(0, vwap.exponent());
}
