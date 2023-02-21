#include "solution.hpp"
#include <cstddef>
#include <gtest/gtest.h>
#include <random.hpp>
#include <sstream>
#include <sys/types.h>

TEST(Sol, 1) {
  int h = 2;
  int w = 2;
  int n = 3;
  int m = 3;
  string dream = "oooo";
  string sam = "ooooooooo";

  int correct = 4;
  int answer = sol1::solution(h, w, n, m, dream, sam);
  ASSERT_EQ(correct, answer);
}
TEST(Sol, 2) {
  int h = 4;
  int w = 4;
  int n = 10;
  int m = 10;
  string dream = "oxxo"
                 "xoox"
                 "xoox"
                 "oxxo";
  string sam = "xxxxxxoxxo"
               "oxxoooxoox"
               "xooxxxxoox"
               "xooxxxoxxo"
               "oxxoxxxxxx"
               "ooooxxxxxx"
               "xxxoxxoxxo"
               "oooxooxoox"
               "oooxooxoox"
               "xxxoxxoxxo";

  int correct = 4;
  int answer = sol1::solution(h, w, n, m, dream, sam);
  ASSERT_EQ(correct, answer);
}
TEST(Sol, 3) {
  int h = 1;
  int w = 1;
  int n = 1;
  int m = 1;
  string dream = "o";
  string sam = "o";

  int correct = 1;
  int answer = sol1::solution(h, w, n, m, dream, sam);
  ASSERT_EQ(correct, answer);
}
TEST(Sol, 4) {
  int h = 2000;
  int w = 2000;
  int n = 2000;
  int m = 2000;
  stringstream dream;
  stringstream sam;

  for (int i = 0; i < h * w; ++i) {
    dream << 'o';
    sam << 'o';
  }

  int correct = 1;
  int answer = sol1::solution(h, w, n, m, dream.str(), sam.str());
  ASSERT_EQ(correct, answer);
}
TEST(Exhaust, 1) {
  int h = 100;
  int w = 100;
  int n = 2000;
  int m = 2000;
  stringstream dream;
  stringstream sam;
  Random<u_char> rand;

  for (int i = 0; i < h * w; ++i) {
    dream << (rand.next() % 2 == 0 ? "o" : "x");
  }
  for (int i = 0; i < n * m; ++i) {
    sam << (rand.next() % 2 == 0 ? "o" : "x");
  }
  sol1::solution(h, w, n, m, dream.str(), sam.str());
}

TEST(RK, 1) {
  vector<string> str2d1 = {"oxox", "oooo", "xxxx", "xoxo"};
  vector<string> str2d2 = {"oxox", "oooo", "xxxx", "xoxx"};

  auto cum1 = sol2::rabin_karp_2d(str2d1);
  auto cum2 = sol2::rabin_karp_2d(str2d2);

  ASSERT_NE(cum1, cum2);
}

TEST(PartialSum, 1) {
  vector<string> str2d = {"oxox", "oooo", "xxxx", "xoxo"};
  vector<string> str2d_2_2 = {"xx00", "xo00"}; // from (2,2) to (3,3)

  auto cum = sol2::rabin_karp_2d(str2d);
  auto cum_2_2 = sol2::rabin_karp_2d(str2d_2_2);

  for (size_t i = 0; i < 2; ++i) {
    for (size_t j = 0; j < 2; ++j) {
      ASSERT_EQ(cum_2_2[i][j] * sol2::B_POW(2 * 4 + 2), cum[i + 2][j + 2]);
    }
  }

  cum = sol2::cumulative_sum(std::move(cum));
  cum_2_2 = sol2::cumulative_sum(std::move(cum_2_2));

  auto correct = cum_2_2[1][1];
  auto answer = sol2::partial_sum(cum, 2, 2, 3, 3);
  correct = (correct * sol2::B_POW(2 * 4 + 2)) % sol2::MOD;

  ASSERT_EQ(correct, answer);
}

#include <random.hpp>

TEST(PartialSum, 2) {
  Random<u_int16_t> rand;
  const size_t ROW = 100;
  const size_t COL = 110;
  const size_t i1 = ROW / 2 + (rand.next() % 10);
  const size_t j1 = ROW / 2 + (rand.next() % 10);
  const size_t i2 = ROW - (rand.next() % 10) - 1;
  const size_t j2 = COL - (rand.next() % 10) - 1;
  auto ls = vector<vector<size_t>>(ROW, vector<size_t>(COL));
  for (size_t i = 0; i < ROW; ++i) {
    for (size_t j = 0; j < COL; ++j) {
      ls[i][j] = rand.next() % sol2::MOD;
    }
  }
  size_t correct = 0;
  for (size_t i = i1; i <= i2; ++i) {
    for (size_t j = j1; j <= j2; ++j) {
      correct = (correct + ls[i][j]) % sol2::MOD;
    }
  }
  ls = sol2::cumulative_sum(std::move(ls));
  size_t answer = sol2::partial_sum(ls, i1, j1, i2, j2);

  ASSERT_EQ(correct, answer);
}