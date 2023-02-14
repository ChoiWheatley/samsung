#include "solution.hpp"
#include <gtest/gtest.h>

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