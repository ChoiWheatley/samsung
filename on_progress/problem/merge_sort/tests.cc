#include "merge_sort.hpp"
#include <algorithm>
#include <functional>
#include <gtest/gtest.h>

#include <iterator>
#include <vector>
using std::vector;

TEST(Sort, 1) {
  auto ls = vector<int>{4, 6, 8, 10, 3, 5, 7, 9};
  auto sorted = vector<int>();
  std::copy(ls.begin(), ls.end(), std::back_inserter(sorted));
  std::sort(sorted.begin(), sorted.end());
  merge_sort(ls.begin(), ls.end(), std::less<>());

  ASSERT_EQ(sorted, ls);
}