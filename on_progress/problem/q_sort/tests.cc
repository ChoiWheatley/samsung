#include "q_sort.hpp"
#include "random.hpp"
#include <algorithm>
#include <functional>
#include <gtest/gtest.h>

#include <iterator>
#include <vector>
using std::vector;

TEST(Sort, 1) {
  auto ls = vector<int>{4, 6, 8, 10, 3, 5, 7, 9};
  auto sorted = vector<int>();
  std::copy(ls.begin(), ls.end(), std::back_inserter(sorted));
  std::sort(sorted.begin(), sorted.end());
  q_sort::sort(ls.begin(), ls.end(), std::less<int>());

  ASSERT_EQ(sorted, ls);
}

TEST(Sort, 2) {
  constexpr size_t MAX_N = 90000;
  using elem_t = char;

  Random<elem_t> rand;
  auto ls = vector<elem_t>(MAX_N);
  for (auto &e : ls) {
    e = rand.next();
  }
  auto sorted = vector<elem_t>();
  std::copy(ls.begin(), ls.end(), std::back_inserter(sorted));
  std::sort(sorted.begin(), sorted.end());

  q_sort::sort(ls.begin(), ls.end(), std::less<elem_t>());

  ASSERT_EQ(sorted, ls);
}
TEST(Sort, Standard) {
  constexpr size_t MAX_N = 90000;
  using elem_t = char;

  Random<elem_t> rand;
  auto ls = vector<elem_t>(MAX_N);
  for (auto &e : ls) {
    e = rand.next();
  }
  std::sort(ls.begin(), ls.end(), std::less<elem_t>());
}
TEST(Sort, Q_Sort) {
  constexpr size_t MAX_N = 90000;
  using elem_t = char;

  Random<elem_t> rand;
  auto ls = vector<elem_t>(MAX_N);
  for (auto &e : ls) {
    e = rand.next();
  }
  q_sort::sort(ls.begin(), ls.end(), std::less<elem_t>());
}