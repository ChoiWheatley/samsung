#include "solution.hpp"
#include <gtest/gtest.h>

TEST(SOL, 1)
{
    ASSERT_EQ(false, solution(4, 0));
}

TEST(SOL, 2)
{
    ASSERT_EQ(false, solution(4, 30));
}

TEST(SOL, 3)
{
    ASSERT_EQ(true, solution(4, 47));
}

TEST(SOL, 4)
{
    ASSERT_EQ(true, solution(5, 31));
}

TEST(SOL, 5)
{
    ASSERT_EQ(false, solution(5, 62));
}
