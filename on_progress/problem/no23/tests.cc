#include "solution.hpp"
#include <algorithm>
#include <functional>
#include <gtest/gtest.h>
#include <vector>
using std::vector;

TEST(Heap, Sol1) {
  Heap<int, std::less<int>> heap{};
  vector<int> ls = {8, 8, 1, 4, 12, 5};
  for (auto e : ls) {
    heap.insert(e);
  }
  std::sort(ls.begin(), ls.end(), std::greater<int>());
  for (auto e : ls) {
    ASSERT_EQ(e, heap.peek().retval);
    heap.pop();
  }
}

using cont_t = int;
TEST(Heap, PopMax) {
  struct less_t {
    auto operator()(cont_t const &a, cont_t const &b) const { return a < b; }
  };
  Heap<cont_t, less_t> heap;
  std::vector<cont_t> ls = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
  for (auto e : ls) {
    heap.insert(cont_t(e));
  }
  std::sort(ls.begin(), ls.end(), std::greater<cont_t>());
  for (auto e : ls) {
    ASSERT_EQ(e, heap.peek().retval);
    heap.pop();
  }
}

TEST(Heap, PopMin) {
  struct greater_t {
    auto operator()(cont_t const &a, cont_t const &b) const { return a > b; }
  };
  Heap<cont_t, greater_t> heap;
  std::vector<cont_t> ls = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
  for (auto e : ls) {
    heap.insert(cont_t(e));
  }
  std::sort(ls.begin(), ls.end());
  for (auto e : ls) {
    ASSERT_EQ(e, heap.peek().retval);
    heap.pop();
  }
}
