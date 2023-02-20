#include "solution.hpp"
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
  int answer = solution(h, w, n, m, dream, sam);
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
  int answer = solution(h, w, n, m, dream, sam);
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
  int answer = solution(h, w, n, m, dream, sam);
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
  int answer = solution(h, w, n, m, dream.str(), sam.str());
  ASSERT_EQ(correct, answer);
}
TEST(Exhaust, 1) {
  int h = 10;
  int w = 10;
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
  solution(h, w, n, m, dream.str(), sam.str());
}