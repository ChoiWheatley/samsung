#include "solution.hpp"
#include <algorithm>
#include <functional>
#include <gtest/gtest.h>
#include <vector>
using std::vector;

TEST(Heap, Sol1) {
  init();
  auto ls = vector<int>{1, 9, 2, 8, 3, 7, 4, 6, 5, 5, 5, 5, 5};
  for (size_t i = 0; i < ls.size(); ++i) {
    addUser(i, ls[i]);
  }
  std::sort(ls.begin(), ls.end(), std::greater<int>());

  for (size_t i = 0; i < ls.size(); ++i) {
    ASSERT_EQ(ls[i], peek().income);
    pop();
  }
}