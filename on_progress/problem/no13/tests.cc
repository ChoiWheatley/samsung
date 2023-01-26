#include "solution.hpp"
#include <gtest/gtest.h>

TEST(Intersect, 1) {
  edge_t e1 = {{1, 0}, {1, 3}};
  edge_t e2 = {{0, 2}, {5, 2}};
  ASSERT_TRUE(is_intersect(e1, e2));
  e1 = {{3, 0}, {3, 6}};
  ASSERT_TRUE(is_intersect(e1, e2));
  e1 = {{6, 0}, {6, 2}};
  ASSERT_FALSE(is_intersect(e1, e2));
  e1 = {{0, 3}, {2, 3}};
  e2 = {{1, 3}, {2, 3}};
  ASSERT_TRUE(is_intersect(e1, e2));
}