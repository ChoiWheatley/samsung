#include "solution.hpp"
#include <gtest/gtest.h>

using namespace std;

TEST(test, 1) {}

TEST(Sol, 1) {
  init();
  hire(16, 1, 5);
  hire(21, 1, 5);
  ASSERT_EQ(21, bestSoldier(1));
  fire(21);
  ASSERT_EQ(16, bestSoldier(1));
  hire(25, 1, 4);
  hire(30, 1, 2);
  updateTeam(1, 1);
  ASSERT_EQ(25, bestSoldier(1));
  updateTeam(1, 2);
  ASSERT_EQ(30, bestSoldier(1));
  updateSoldier(30, 2);
  ASSERT_EQ(25, bestSoldier(1));
  updateTeam(1, -4);
  hire(1, 1, 3);
  updateTeam(1, -1);
  ASSERT_EQ(1, bestSoldier(1));
  hire(100000, 5, 1);
  ASSERT_EQ(100000, bestSoldier(5));
}