#include "solution.hpp"
#include <algorithm>
#include <cstddef>
#include <functional>
#include <gtest/gtest.h>
#include <iterator>
#include <memory>
#include <random.hpp>
#include <string>
#include <vector>

using std::string;
using std::vector;

TEST(Test, 1) {
  vector<string> ls = {"hello", "my", "name", "is", "choi", "wheatley"};
  vector<string> ls2{ls};
  std::sort(ls.begin(), ls.end());
  sol1::sort(ls2.begin(), ls2.end(), std::less<string>{});
  ASSERT_EQ(ls, ls2);
}

constexpr size_t MAX_N = 200000;

TEST(Timeout, 1) {
  vector<int> ls;
  vector<int> ls2;
  std::generate_n(std::back_inserter(ls), MAX_N, std::bind(generator, engine));
  std::generate_n(std::back_inserter(ls2), MAX_N, std::bind(generator, engine));
  std::sort(ls.begin(), ls.end());
  sol1::sort(ls2.begin(), ls2.end(), std::less<int>{});
  ASSERT_EQ(ls, ls2);
}

TEST(Sol, 1) {
  vector<string> ls = {
      "my", "name", "is", "ho", "seok",
  };
  vector<string> sorted = {
      "ho", "is", "my", "name", "seok",
  };
  sol1::sort(ls.begin(), ls.end(),
             [](auto a, auto b) { return a.size() < b.size(); });
  sol1::sort(ls.begin(), ls.end(), std::less<string>());
  vector<string> collected;
  std::unique(ls.begin(), ls.end());
  ASSERT_EQ(sorted, ls);
}

TEST(Sol, 2) {
  vector<string> ls = {
      "s", "a", "m", "s", "u", "n", "g", "j", "j", "a", "n", "g",
  };
  vector<string> sorted = {
      "a", "g", "j", "m", "n", "s", "u",
  };
  sol1::sort(ls.begin(), ls.end(),
             [](auto a, auto b) { return a.size() < b.size(); });
  sol1::sort(ls.begin(), ls.end(), std::less<string>());
  vector<string> collected;
  std::unique_copy(ls.begin(), ls.end(), std::back_inserter(collected));
  ASSERT_EQ(sorted, collected);
}