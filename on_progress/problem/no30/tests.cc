#include "solution.hpp"
#include <cstddef>
#include <gtest/gtest.h>
#include <random.hpp>
#include <sstream>
#include <sys/types.h>

using sol2::B;
using sol2::cumulative_sum;
using sol2::MOD;
using sol2::mod;
using sol2::partial_sum;
using sol2::pow;

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
  int h = 10;
  int w = 10;
  int n = 200;
  int m = 200;
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
  vector<string> str2d_2_2 = {"xx00", "xo00", "0000",
                              "0000"}; // from (2,2) to (3,3)

  auto cum = sol2::rabin_karp_2d(str2d);
  auto cum_2_2 = sol2::rabin_karp_2d(str2d_2_2);

  for (int64_t i = 0; i < 2; ++i) {
    for (int64_t j = 0; j < 2; ++j) {
      ASSERT_EQ(mod((str2d_2_2[i][j] * pow(B, i * 4 + j)), MOD),
                (cum_2_2[i][j]));
      ASSERT_EQ(mod((cum_2_2[i][j] * pow(B, 2 * 4 + 2)), MOD),
                cum[i + 2][j + 2]);
    }
  }

  int64_t real_sum = 0;
  int64_t fake_sum = 0;
  for (int64_t i = 0; i < 2; ++i) {
    for (int64_t j = 0; j < 2; ++j) {
      real_sum = mod((real_sum + cum_2_2[i][j]), MOD);
      fake_sum = mod((fake_sum + cum[i + 2][j + 2]), MOD);
    }
  }
  ASSERT_EQ(mod((real_sum * pow(B, 10)), MOD), fake_sum);

  cum = cumulative_sum(std::move(cum));
  cum_2_2 = cumulative_sum(std::move(cum_2_2));

  auto answer = cum_2_2[1][1];
  auto submit = partial_sum(cum, 2, 2, 3, 3);

  ASSERT_EQ(real_sum, answer);
  ASSERT_EQ(fake_sum, submit);

  answer = mod((answer * pow(B, 2 * 4 + 2)), MOD);

  ASSERT_EQ(answer, submit);
}

#include <random.hpp>

TEST(PartialSum, 2) {
  Random<int64_t> rand;
  const int64_t ROW = 100;
  const int64_t COL = 110;
  const int64_t i1 = ROW / 2 + (rand.next() % 10);
  const int64_t j1 = ROW / 2 + (rand.next() % 10);
  const int64_t i2 = ROW - (rand.next() % 10) - 1;
  const int64_t j2 = COL - (rand.next() % 10) - 1;

  auto ls = vector<vector<int64_t>>(ROW, vector<int64_t>(COL));

  for (int64_t i = 0; i < ROW; ++i) {
    for (int64_t j = 0; j < COL; ++j) {
      ls[i][j] = mod(rand.next(), MOD);
    }
  }
  int64_t answer = 0;
  for (int64_t i = i1; i <= i2; ++i) {
    for (int64_t j = j1; j <= j2; ++j) {
      answer = mod((answer + ls[i][j]), MOD);
    }
  }
  ls = sol2::cumulative_sum(std::move(ls));
  int64_t submit = sol2::partial_sum(ls, i1, j1, i2, j2);

  ASSERT_EQ(answer, submit);
}