#ifndef Q_SORT
#define Q_SORT

#include <algorithm>
#include <cstddef>
#include <optional>
#include <random.hpp>

namespace q_sort {

template <typename Iter, class Less>
Iter partition(Iter begin, Iter end, Less const &less) {
  Random<size_t> rand;
  auto pivot = begin + (rand.next() % (end - begin));
  // make pivot to the last element
  std::iter_swap(pivot, end - 1);
  pivot = end - 1;
  auto i = begin; // pivot보다 작은 놈들의 수라고 생각해도 좋음.
  for (auto j = begin; j != pivot; ++j) {
    if (less(*j, *pivot)) {
      // pivot보다 작은 놈은 왼쪽으로 보내요
      std::iter_swap(i, j);
      i++;
    }
  }
  std::iter_swap(i, pivot);
  return i;
}

template <typename Iter, class Less>
void sort(Iter begin, Iter end, Less const &less) {

  if (end - begin <= 1) {
    return;
  }
  auto mid = q_sort::partition(begin, end, less); // conquer
  // divide
  q_sort::sort(begin, mid, less);
  q_sort::sort(mid + 1, end, less);
}

} // namespace q_sort

#endif