#include "solution.hpp"
#include <gtest/gtest.h>

TEST(Sol, 1) {
  Solution sol{5};
  elem_t submit = 0;
  submit = (submit + sol.add(1, 3)) % MOD;
  submit = (submit + sol.add(2, 6)) % MOD;
  submit = (submit + sol.add(8, 9)) % MOD;
  elem_t answer = 11;
  ASSERT_EQ(answer, submit);
}