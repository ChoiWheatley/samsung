#include "solution.hpp"
#include <cctype>
#include <cstdio>
#include <gtest/gtest.h>
#include <string>
#include <utility>
using std::string;

Arr<Arr<int>> str_to_arr2d(int n, string const &str) {
  Arr<Arr<int>> ret{{{0}}};
  int index = 0;
  for (char c : str) {
    if (!std::isdigit(c)) {
      continue;
    }
    ret[index / n][index % n] = c - '0';
    index++;
  }
  return ret;
}

TEST(Converter, 1) {
  string sample = "0100"
                  "1110"
                  "1011"
                  "1010";
  Arr<Arr<int>> answer = {
      {{0, 1, 0, 0}, {1, 1, 1, 0}, {1, 0, 1, 1}, {1, 0, 1, 0}}};
  auto submit = str_to_arr2d(4, sample);

  ASSERT_EQ(answer, submit);
}

TEST(Sol, 1) {
  string sample = "0100"
                  "1110"
                  "1011"
                  "1010";
  auto arr2d = str_to_arr2d(4, sample);
  int answer = 2;
  int submit = solution(4, std::move(arr2d));
  ASSERT_EQ(answer, submit);
}

TEST(Sol, 2) {
  string sample = "011001"
                  "010100"
                  "010011"
                  "101001"
                  "010101"
                  "111010";
  auto arr2d = str_to_arr2d(6, sample);
  int answer = 2;
  int submit = solution(6, std::move(arr2d));
  ASSERT_EQ(answer, submit);
}