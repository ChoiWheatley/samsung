#include "heap.hpp"
#include <algorithm>
#include <functional>
#include <gtest/gtest.h>
#include <vector>
using cont_t = int;

TEST(Heap, Insert) {

  Heap<cont_t> heap;
  auto ls = {1, 4, 2, 6, 3, 8, 5, 10};
  for (auto e : ls) {
    heap.insert(cont_t(e));
  }
}

TEST(Heap, MinHeap) {

  struct bigger_than_t {
    auto operator()(cont_t const &lhs, cont_t const &rhs) const {
      return lhs > rhs;
    }
  };
  Heap<cont_t, bigger_than_t> min_heap;
  auto ls = {1, 4, 2, 6, 3, 8, 5, 10};
  for (auto e : ls) {
    min_heap.insert(cont_t(e));
  }
}

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
    ASSERT_EQ(e, heap.peek());
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
    ASSERT_EQ(e, heap.peek());
    heap.pop();
  }
}
