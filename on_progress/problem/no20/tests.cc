#include "solution.hpp"
#include <gtest/gtest.h>

using std::string;
using namespace sol2;

TEST(Sol, 1) {
  string s1 = "acaykp";
  string s2 = "capcak";
  size_t answer = 4;
  size_t submit = solution(std::move(s1), std::move(s2));
  ASSERT_EQ(answer, submit);
}

TEST(Sol, 2) {
  string s1 = "zcaykp";
  string s2 = "capcak";
  size_t answer = 3;
  size_t submit = solution(std::move(s1), std::move(s2));
  ASSERT_EQ(answer, submit);
}

TEST(Sol, 3) {
  string s1 = std::string(size_t(1000), 'a');
  string s2 = std::string(size_t(1000), 'b');
  size_t answer = 0;
  size_t submit = solution(std::move(s1), std::move(s2));
  ASSERT_EQ(answer, submit);
}

TEST(Sol, 4) {
  string gibberish = "bcdfghijklmnopqrstuvwxyz";
  string s1 = "a" + gibberish;
  string s2 = gibberish + "a";
  size_t answer = gibberish.size();
  size_t submit = solution(std::move(s1), std::move(s2));
  ASSERT_EQ(answer, submit);
}