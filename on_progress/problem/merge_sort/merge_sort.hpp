#ifndef MERGE_SORT
#define MERGE_SORT

#include <functional>
#include <iterator>
#include <vector>
using std::vector;

template <typename Iter, class Less = std::less<>>
void merge(Iter begin, Iter end, Less const &less) {

  using value_type = typename std::iterator_traits<Iter>::value_type;

  auto temp = vector<value_type>{};
  auto mid = begin + (end - begin) / 2;
  auto l = begin;
  auto r = mid;
  while (l != mid && r != end) {
    if (less(*l, *r)) {
      temp.push_back(*l);
      l++;
    } else {
      temp.push_back(*r);
      r++;
    }
  }
  while (l != mid) {
    temp.push_back(*l);
    l++;
  }
  while (r != end) {
    temp.push_back(*r);
    r++;
  }
  // paste it into original
  for (auto itr = begin; itr != end; ++itr) {
    *itr = temp[itr - begin];
  }
}

template <typename Iter, class Less>
void merge_sort(Iter begin, Iter end, Less const &less) {
  if (begin == end) {
    return;
  }
  auto mid = begin + (end - begin) / 2;
  merge_sort(begin, mid, less);
  merge_sort(mid + 1, end, less);
  merge(begin, end, less);
}

#endif