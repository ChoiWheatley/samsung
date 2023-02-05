#include "solution.hpp"
#include <gtest/gtest.h>

TEST(Bin, 1) {
  auto submit = lis_with_bin_search::lis //
      ({8, 2, 4, 3, 6, 11, 7, 10, 14, 5});
  auto answer = 6;
  ASSERT_EQ(answer, submit);
}

TEST(Bin, 2) {
  auto submit = lis_with_bin_search::lis //
      ({2, 10, 6, 14, 1, 9, 15, 13});
  auto answer = 4;
  ASSERT_EQ(answer, submit);
}

TEST(List, 1) {
  auto submit = lis_with_list::lis //
      ({8, 2, 4, 3, 6, 11, 7, 10, 14, 5});
  auto answer = 6;
  ASSERT_EQ(answer, submit.size());
}

TEST(List, 2) {
  auto submit = lis_with_list::lis //
      ({2, 10, 6, 14, 1, 9, 15, 13});
  auto answer = 4;
  ASSERT_EQ(answer, submit.size());
}
