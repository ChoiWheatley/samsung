#include "solution.hpp"
#include <gtest/gtest.h>

TEST(Init, 1) {
  uint n = 5;
  Arr ls = {1, 2, 3, 4, 5};
  init(ls, n);
  Arr answer = {0, 3, 2, -1, -1, 3, 4, 5, 1, 2};
  ASSERT_EQ(answer, _tree);
}