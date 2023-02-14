#include "solution.hpp"
#include <array>
#include <gtest/gtest.h>
#include <random.hpp>
#include <utility>

using std::pair;
using uint_pair = pair<uint, uint>;

TEST(Init, 1) {
  uint const data[N] = {1, 2, 3, 4, 5};
  init(data, 5);
  uint const min_answer[10] = {0, 1, 1, 4, 1, 3, 4, 5, 1, 2};
  uint const max_answer[10] = {0, 5, 3, 5, 2, 3, 4, 5, 1, 2};
  for (size_t i = 1; i < 10; ++i) {
    ASSERT_EQ(min_answer[i], g_mintree[i]);
    ASSERT_EQ(max_answer[i], g_maxtree[i]);
  }
}

TEST(Set, 1) {
  uint n = 5;
  uint const data[N] = {1, 2, 3, 4, 5};
  init(data, n);
  set(0, 999, n);
  uint const min_answer[10] = {0, 2, 2, 4, 2, 3, 4, 5, 999, 2};
  uint const max_answer[10] = {0, 999, 999, 5, 999, 3, 4, 5, 999, 2};
  for (size_t i = 1; i < 10; ++i) {
    ASSERT_EQ(min_answer[i], g_mintree[i]) << "i : " << i;
    ASSERT_EQ(max_answer[i], g_maxtree[i]) << "i: " << i;
  }
}

TEST(Query, 1) {
  uint n = 5;
  uint const data[N] = {1, 2, 3, 4, 5};
  init(data, n);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i + 1; j <= n; ++j) {
      ASSERT_EQ(data[j - 1], max_between(i, j, n));
      ASSERT_EQ(data[i], min_between(i, j, n));
    }
  }
}

/**
1 0 5 => 4
1 1 4 => 2
0 2 9
1 0 5 => 8
1 1 4 => 7
*/
TEST(Sol, 1) {
  uint n = 5;
  uint const data[N] = {1, 2, 3, 4, 5};
  init(data, n);
  uint_pair range = {0, 5};
  uint max = max_between(range.first, range.second, n);
  uint min = min_between(range.first, range.second, n);
  ASSERT_EQ(4, max - min);
  range = {1, 4};
  max = max_between(range.first, range.second, n);
  min = min_between(range.first, range.second, n);
  ASSERT_EQ(2, max - min);
}

TEST(Exhaust, 1) {
  Random<uint> rand{};
  uint data[N] = {0};
  for (uint i = 0; i < N; ++i) {
    data[i] = rand.next();
  }
  init(data, N);
}