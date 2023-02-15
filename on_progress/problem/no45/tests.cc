#include "solution.hpp"
#include <gtest/gtest.h>
#include <utility>

TEST(Init, 1) {
  uint n = 5;
  Arr ls = {1, 2, 3, 4, 5};
  init(ls, n);
  Arr answer = {0, 3, 2, -1, -1, 3, 4, 5, 1, 2};
  ASSERT_EQ(answer, _tree);
}

TEST(Update, 1) {
  uint n = 5;
  Arr ls = {1, 2, 3, 4, 5};
  init(ls, n);
  update(0, 100, n);
  Arr answer = {0, 102, 101, -1, 98, 3, 4, 5, 100, 2};
  ASSERT_EQ(answer, _tree);
}

TEST(Query, 1) {
  uint n = 5;
  Arr ls = {1, 2, 3, 4, 5};
  init(ls, n);
  using pair = std::pair<uint, uint>;
  pair rng = {0, 3};
  elem_t answer = 2;
  ASSERT_EQ(answer, jagged_sum(rng.first, rng.second, n));
}