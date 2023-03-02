#include "solution.hpp"
#include <algorithm>
#include <cmath>
#include <gtest/gtest.h>
#include <utility>
#include <vector>

using std::abs;
using std::make_pair;
using std::vector;

TEST(BinSearch, UpperBound) {
  vector<int> sorted = {1, 3, 5, 5, 5, 7, 9};
  int key = 5;
  auto upper_b = first_true(sorted.begin(), sorted.end(),
                            [key](auto e) { return key < *e; });
  auto real_upper_b = std::upper_bound(sorted.begin(), sorted.end(), key);
  ASSERT_EQ(real_upper_b, upper_b);
}

TEST(BinSearch, LowerBound) {
  vector<int> sorted = {1, 3, 5, 5, 5, 7, 9};
  int key = 5;
  auto lower_b = first_true(sorted.begin(), sorted.end(),
                            [key](auto e) { return key <= *e; });
  auto real_lower_b = std::lower_bound(sorted.begin(), sorted.end(), key);
  ASSERT_EQ(real_lower_b, lower_b);
}

TEST(Sol, 1) {
  vector<int> cows = {3, 0, 6};
  vector<int> horses = {-2, 5, 4, 2};
  const int c1 = 1;
  const int c2 = -3;
  const int dist_x = abs(c1 - c2);
  auto result = solution(cows, horses);
  auto answer = make_pair(5, 3);
  auto submit = make_pair(result.first + dist_x, result.second);
  ASSERT_EQ(answer, submit);
}
TEST(Sol, 2) {
  vector<int> cows = {-4, -10, -2, 0, -1};
  vector<int> horses = {
      3, 18, 0, 1, 5,
  };
  const int c1 = 1;
  const int c2 = 2;
  const int dist_x = abs(c1 - c2);
  auto result = solution(cows, horses);
  auto answer = make_pair(1, 1);
  auto submit = make_pair(result.first + dist_x, result.second);
  ASSERT_EQ(answer, submit);
}