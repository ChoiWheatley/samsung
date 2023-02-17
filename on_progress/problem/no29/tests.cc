#include "solution.hpp"
#include <gtest/gtest.h>

using std::string;

/**
ababa
aba
*/
TEST(Sol, 1) {
  string str = "ababa";
  string pat = "aba";
  size_t answer = 2;
  ASSERT_EQ(answer, solution(str, pat));
}

/**
abracadabra
ab
*/
TEST(Sol, 2) {
  string str = "abracadabra";
  string pat = "ab";
  size_t answer = 2;
  ASSERT_EQ(answer, solution(str, pat));
}