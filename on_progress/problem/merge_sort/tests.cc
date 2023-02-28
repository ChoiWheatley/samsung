#include "merge_sort.hpp"
#include <algorithm>
#include <functional>
#include <gtest/gtest.h>
#include <random.hpp>

#include <iterator>
#include <vector>
using std::vector;

TEST(Sort, 1) {
  auto ls = vector<int>{4, 6, 8, 10, 3, 5, 7, 9};
  auto sorted = vector<int>();
  std::copy(ls.begin(), ls.end(), std::back_inserter(sorted));
  std::sort(sorted.begin(), sorted.end());
  merge_sort(ls.begin(), ls.end(), std::less<>());

  ASSERT_EQ(sorted, ls);
}

constexpr size_t MAX_N = 100000;

TEST(Integrity, 1) {
  using elem_t = long long;

  Random<elem_t> rand;
  vector<elem_t> ls1;
  vector<elem_t> ls2;

  std::generate_n(std::back_inserter(ls1), MAX_N,
                  [&rand]() { return rand.next(); });
  std::copy(ls1.begin(), ls1.end(), std::back_inserter(ls2));

  merge_sort(ls1.begin(), ls1.end(), std::less<elem_t>());
  std::sort(ls2.begin(), ls2.end());

  ASSERT_EQ(ls2, ls1);
}

TEST(Timeout, Std) {
  using elem_t = long long;

  Random<elem_t> rand;
  vector<elem_t> ls1;

  std::generate_n(std::back_inserter(ls1), MAX_N,
                  [&rand]() { return rand.next(); });

  std::sort(ls1.begin(), ls1.end());
}

TEST(Timeout, My) {
  using elem_t = long long;

  Random<elem_t> rand;
  vector<elem_t> ls1;

  std::generate_n(std::back_inserter(ls1), MAX_N,
                  [&rand]() { return rand.next(); });

  merge_sort(ls1.begin(), ls1.end(), std::less<elem_t>());
}