#include "solution.hpp"
#include <gtest/gtest.h>
#include <vector>

/**
4 5
1 2
3 2
4 4
2 3
*/
TEST(Sol, 1) {
  int k = 5;
  vector<int> volume = {1, 3, 4, 2};
  vector<int> cost = {2, 2, 4, 3};
  int answer = 6;
  int submit = solution(volume, cost, k);
  ASSERT_EQ(answer, submit);
}

TEST(Sol, 2) {
  int k = 5;
  auto volume = {5, 1, 1, 1, 1, 1};
  auto cost = {1, 9, 9, 9, 9, 9};
  int answer = 45;
  int submit = solution(volume, cost, k);
  ASSERT_EQ(answer, submit);
}

TEST(Sol, 3) {
  int k = 5;
  auto volume = {1, 1, 1, 1, 1, 5};
  auto cost = {1, 1, 1, 1, 1, 0};
  int answer = 5;
  int submit = solution(volume, cost, k);
  ASSERT_EQ(submit, answer);
}