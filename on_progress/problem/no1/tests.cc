#include "solution.hpp"
#include <gtest/gtest.h>
#include <vector>

TEST(BIG_INTEGER, test1)
{
    BigInteger bigInteger{0};
    ASSERT_EQ(std::vector<int>{}, bigInteger.as_vector());
}
TEST(BIG_INTEGER, test2)
{
    BigInteger bigInteger{100};
    ASSERT_EQ(std::vector<int>({0, 0, 1}), bigInteger.as_vector());
}

TEST(BIG_INTEGER, test3)
{
    BigInteger bigInteger{123456789};
    ASSERT_EQ(std::vector<int>({9, 8, 7, 6, 5, 4, 3, 2, 1}), bigInteger.as_vector());
}
TEST(BIG_INTEGER, test4)
{
    BigInteger bigInteger{12345};
    bigInteger = bigInteger.mult(2);
    ASSERT_EQ(std::vector<int>({0, 9, 6, 4, 2}), bigInteger.as_vector());
}
TEST(BIG_INTEGER, test5)
{
    // over int_max
    BigInteger bigInteger{(1 << 31) - 1}; // 2^31 - 1 = 2147483647 = intmax
                                          // 2^32 - 2 = 4294967294 is bigger than intmax
    bigInteger = bigInteger.mult(2);
    ASSERT_EQ(std::vector<int>({4, 9, 2, 7, 6, 9, 4, 9, 2, 4}), bigInteger.as_vector());
}
TEST(BIG_INTEGER, test6)
{
    BigInteger bigInteger{5};
    ASSERT_EQ(std::vector<int>({0, 1}), bigInteger.mult(2).as_vector());
}
TEST(BIG_INTEGER, add1)
{
    BigInteger bigInteger{1};
    bigInteger = bigInteger.add(BigInteger{1});
    ASSERT_EQ(std::vector<int>({2}), bigInteger.as_vector());
}
TEST(BIG_INTEGER, add2)
{
    BigInteger bigInteger{9};
    bigInteger = bigInteger.add(BigInteger{1});
    ASSERT_EQ(std::vector<int>({0, 1}), bigInteger.as_vector());
}

TEST(BIG_INTEGER, add3)
{
    BigInteger bigInteger{9};
    bigInteger += bigInteger;
    ASSERT_EQ(std::vector<int>({8, 1}), bigInteger.as_vector());
}

TEST(BIG_INTEGER, string)
{
    BigInteger bigInteger{12345};
    ASSERT_EQ("12345", BigInteger::to_string(bigInteger));
}

TEST(BIG_INTEGER, string2)
{
    BigInteger bigInteger{1};
    ASSERT_EQ("1", BigInteger::to_string(bigInteger));
}

TEST(BIG_INTEGER, string3)
{
    BigInteger bigInteger{10};
    ASSERT_EQ("10", bigInteger.to_string());
}

TEST(BIG_INTEGER, string4)
{
    BigInteger bigInteger{1};
    ASSERT_EQ("100", (bigInteger + BigInteger{99}).to_string());
}

TEST(SOL, 1)
{
    ASSERT_EQ("10", solve(1));
}

TEST(SOL, 2)
{
    ASSERT_EQ("90", solve(2));
}

TEST(SOL, 3)
{
    ASSERT_EQ("110", solve(11));
}

TEST(SOL, 4)
{
    ASSERT_EQ("6475", solve(1295));
}

TEST(SOL, 5)
{
    ASSERT_EQ("5076", solve(1692));
}

__attribute__((noinline, used)) static std::string
to_string(const std::vector<int> &ls)
{
    std::string ret = "";
    for (const int &e : ls)
    {
        ret.append(std::to_string(e) + " ");
    }
    return ret;
}