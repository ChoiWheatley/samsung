#include "solution.hpp"
#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using std::string;

TEST(Sol, 1) {
  string bintree_str = "*/-8264";
  vector<char> bintree{bintree_str.begin(), bintree_str.end()};
  ASSERT_TRUE(solution(bintree));
}

TEST(Sol, 2) {
  string bintree_str = "*/-/26487";
  vector<char> bintree{bintree_str.begin(), bintree_str.end()};
  ASSERT_TRUE(solution(bintree));
}

TEST(Sol, 3) {
  string bintree_str = "*/-12648*";
  vector<char> bintree{bintree_str.begin(), bintree_str.end()};
  ASSERT_FALSE(solution(bintree));
}