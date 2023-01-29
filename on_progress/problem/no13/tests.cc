#include "solution.hpp"
#include <cmath>
#include <gtest/gtest.h>
#include <random.hpp>
#include <sstream>
#include <string>

constexpr bool T = true;
constexpr bool F = false;

TEST(Intersect, 1) {
  edge_t e1 = {{1, 0}, {1, 3}};
  edge_t e2 = {{0, 2}, {5, 2}};
  ASSERT_TRUE(is_intersect(e1, e2));
  e1 = {{3, 0}, {3, 6}};
  ASSERT_TRUE(is_intersect(e1, e2));
  e1 = {{6, 0}, {6, 2}};
  ASSERT_FALSE(is_intersect(e1, e2));
  e1 = {{0, 3}, {2, 3}};
  e2 = {{1, 3}, {2, 3}};
  ASSERT_TRUE(is_intersect(e1, e2));
}

/**
0110
1001
0010
*/
static auto text_to_vec2d(std::string const &text) -> vector<vector<bool>> {
  size_t n = static_cast<size_t>(std::sqrt(text.size()));
  auto stream = std::stringstream{text};
  auto ret = vector<vector<bool>>{};
  for (int i = 0; i < n; ++i) {
    ret.emplace_back();
    for (int j = 0; j < n; ++j) {
      int c = stream.get();
      if (c == '0' || c == '1') {
        ret[i].push_back(c == '0' ? false : true);
      }
    }
  }
  return ret;
}

TEST(Convert, 1) {
  auto str = "0010000"
             "0010000"
             "0000010"
             "0000000"
             "1101000"
             "0100000"
             "0000000";
  auto answer = vector<vector<bool>>{
      {F, F, T, F, F, F, F}, {F, F, T, F, F, F, F}, {F, F, F, F, F, T, F},
      {F, F, F, F, F, F, F}, {T, T, F, T, F, F, F}, {F, T, F, F, F, F, F},
      {F, F, F, F, F, F, F}};
  ASSERT_EQ(answer, text_to_vec2d(str));
}

TEST(Sol, 1) {
  auto cores = vector<vector<bool>>{
      {F, F, T, F, F, F, F}, {F, F, T, F, F, F, F}, {F, F, F, F, F, T, F},
      {F, F, F, F, F, F, F}, {T, T, F, T, F, F, F}, {F, T, F, F, F, F, F},
      {F, F, F, F, F, F, F}};
  ASSERT_EQ(12, solution(std::move(cores)));
}

TEST(Sol, 2) {
  auto str = "11111"
             "11001"
             "00011"
             "00011"
             "10111";
  auto answer = 6;
  auto submit = solution(text_to_vec2d(str));
  ASSERT_EQ(answer, submit);
}

TEST(Sol, 3) {
  auto str = "000000000"
             "001000001"
             "100000000"
             "000100000"
             "010000000"
             "000000100"
             "000100000"
             "000000010"
             "000000001";
  auto answer = 10;
  auto submit = solution(text_to_vec2d(str));
  ASSERT_EQ(answer, submit);
}

TEST(Sol, 4) {
  auto str = "00100000000"
             "00000000000"
             "00000000001"
             "00010000100"
             "01011000100"
             "00000000000"
             "00000001000"
             "00000000000"
             "00000000100"
             "00000010000"
             "00000000000";
  auto answer = 24;
  auto submit = solution(text_to_vec2d(str));
  ASSERT_EQ(answer, submit);
}

TEST(Sol, 5) {
  auto str = "10011"
             "00011"
             "10001"
             "11101"
             "11111";
  auto answer = 6;
  auto submit = solution(text_to_vec2d(str));
  ASSERT_EQ(answer, submit);
}

TEST(Sol, 6) {
  auto str = "11101"
             "11000"
             "11000"
             "10011"
             "11111";
  auto answer = 6;
  auto submit = solution(text_to_vec2d(str));
  ASSERT_EQ(answer, submit);
}

TEST(Sol, 7) {
  auto str = "000101110"
             "100100000"
             "100100000"
             "100000111"
             "000010000"
             "111000001"
             "000001001"
             "000001001"
             "011101000";
  auto answer = 40;
  auto submit = solution(text_to_vec2d(str));
  ASSERT_EQ(answer, submit);
}

TEST(Sol, 8) {
  auto str = "00000"
             "01110"
             "01110"
             "01110"
             "00000";
  auto answer = 8;
  auto submit = solution(text_to_vec2d(str));
  ASSERT_EQ(answer, submit);
}

TEST(Sol, 9) {
  auto str = "111111111"
             "100010000"
             "001000010"
             "100010000"
             "110110000"
             "100000100"
             "101000001"
             "100010100"
             "101000000";
  auto answer = 27;
  auto submit = solution(text_to_vec2d(str));
  ASSERT_EQ(answer, submit);
}

TEST(Timeout, 1) {
  Random<short> r{};
  constexpr size_t n = 12;
  auto cores = vector<vector<bool>>();
  for (size_t i = 0; i < n; ++i) {
    cores.emplace_back();
    for (size_t j = 0; j < n; ++j) {
      cores[i].push_back(r.next() % 2 == 0);
    }
  }
  solution(std::move(cores));
}