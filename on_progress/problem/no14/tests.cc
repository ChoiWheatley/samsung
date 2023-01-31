#include "solution.hpp"
#include <cmath>
#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace std;

/**
- '.' = false
- '*' = true
*/
static auto to_vec(string const &str) -> vector<vector<bool>> {
  auto n = static_cast<size_t>(sqrt(str.size()));
  auto ret = vector<vector<bool>>(n, vector<bool>(n, false));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      char cur = str[i * n + j];
      if (cur == '.') {
        ret[i][j] = false;
      } else if (cur == '*') {
        ret[i][j] = true;
      }
    }
  }
  return ret;
}

TEST(Convert, 1) {
  string str = "*****"
               "....."
               "*.*.*"
               ".*.*."
               "***..";
  auto correct = vector<vector<bool>>{{true, true, true, true, true},
                                      {false, false, false, false, false},
                                      {true, false, true, false, true},
                                      {false, true, false, true, false},
                                      {true, true, true, false, false}};
  ASSERT_EQ(correct, to_vec(str));
}

TEST(Sol, 1) {
  string str = "..*"
               "..*"
               "**.";
  auto submit = solution(to_vec(str));
  auto correct = 2;
  ASSERT_EQ(correct, submit);
}

TEST(Sol, 2) {
  string str = "..*.."
               "..*.."
               ".*..*"
               ".*..."
               ".*...";
  auto submit = solution(to_vec(str));
  auto correct = 8;
  ASSERT_EQ(correct, submit);
}