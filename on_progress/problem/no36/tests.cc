#include "solution.hpp"
#include <gtest/gtest.h>
#include <vector>

using std::vector;

TEST(Bitset, 1) {
  vector<int> bits;
  for (u32 i = 0; i <= MAX_DAY; ++i) {
    if (i % 2 == 1) {
      // 홀수인 인덱스만 전부 True
      bitset::set(i);
    }
  }
  for (int i = 0; i <= MAX_DAY; ++i) {
    if (i % 2 == 0) {
      ASSERT_FALSE(bitset::check(i));
    } else {
      ASSERT_TRUE(bitset::check(i));
    }
  }
}
TEST(Bitset, 2) {
  vector<int> bits;
  for (u32 i = 0; i <= MAX_DAY; ++i) {
    bitset::set(i);
  }

  for (u32 i = 0; i <= MAX_DAY; ++i) {
    if (i % 2 == 0) {
      // 짝수인 인덱스만 전부 False
      bitset::reset(i);
    }
  }

  for (int i = 0; i <= MAX_DAY; ++i) {
    if (i % 2 == 0) {
      ASSERT_FALSE(bitset::check(i));
    } else {
      ASSERT_TRUE(bitset::check(i));
    }
  }
}

TEST(Sol, 1) {
  auto check = {3, 5, 6, 10, 11};
  for (auto e : check) {
    bitset::set(e);
  }
  auto p = 2;
  auto answer = 5;
  auto submit = sol1::solution(int(check.size()), p, *(check.end() - 1));
  ASSERT_EQ(answer, submit);
}
TEST(Sol, 2) {
  auto check = {42, 420};
  for (auto e : check) {
    bitset::set(e);
  }
  auto p = 10;
  auto answer = 11;
  auto submit = sol1::solution(int(check.size()), p, *(check.end() - 1));
  ASSERT_EQ(answer, submit);
}

TEST(Sol2, 1) {
  auto check = vector<u32>{3, 5, 6, 10, 11};
  for (auto e : check) {
    bitset::set(e);
  }
  auto p = 2;
  auto answer = 5;
  auto submit = sol2::solution(check, p);
  ASSERT_EQ(answer, submit);
}
TEST(Sol2, 2) {
  auto check = vector<u32>{42, 420};
  for (auto e : check) {
    bitset::set(e);
  }
  auto p = 10;
  auto answer = 11;
  auto submit = sol2::solution(check, p);
  ASSERT_EQ(answer, submit);
}
TEST(Sol2, 3) {
  auto check = vector<u32>{1, 100, 101, 102};
  auto p = 2;
  auto answer = 5;
  auto submit = sol2::solution(check, p);
  ASSERT_EQ(answer, submit);
}
TEST(Timeout, 1) {
  auto check = {1u, MAX_DAY};
  for (auto e : check) {
    bitset::set(e);
  }
  auto p = MAX_P;
  auto answer = p + 1;
  auto submit = sol1::solution(int(MAX_N), p, *(check.end() - 1));
  ASSERT_EQ(answer, submit);
}
TEST(Timeout2, 1) {
  auto check = vector<u32>{1u, MAX_DAY};
  for (auto e : check) {
    bitset::set(e);
  }
  auto p = MAX_P;
  auto answer = p + 1;
  auto submit = sol2::solution(check, p);
  ASSERT_EQ(answer, submit);
}