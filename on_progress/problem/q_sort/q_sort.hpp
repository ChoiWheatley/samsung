#ifndef Q_SORT
#define Q_SORT

#include <algorithm>
#include <cstddef>
#include <optional>
#include <random.hpp>
#include <vector>

using std::vector;

static std::mt19937 engine(std::random_device{}());
static std::uniform_int_distribution<ptrdiff_t> generator(0, PTRDIFF_MAX);

namespace q_sort {
template <typename T, class Less>
inline size_t partition(vector<T> &ls, size_t begin, size_t end,
                        Less const &less) {
  auto p = begin + generator(engine) % (end - begin);
  std::swap(ls[end - 1], ls[p]);
  auto pivot = ls[end - 1];
  size_t count = 0; // pivot 보다 작은 원소의 개수
  for (size_t idx = begin; idx < end - 1; ++idx) {
    if (less(ls[idx], pivot)) {
      std::swap(ls[begin + count], ls[idx]);
      count += 1;
    }
  }
  std::swap(ls[end - 1], ls[begin + count]);
  return begin + count;
}

template <typename T, class Less>
inline void sort(vector<T> &ls, size_t begin, size_t end, Less const &less) {
  if (end - begin <= 1) {
    return;
  }
  size_t mid = partition(ls, begin, end, less);
  sort(ls, begin, mid, less);
  sort(ls, mid + 1, end, less);
}

} // namespace q_sort

/**
블로그 글에 적힌 코드 그대로 가져옴*/
namespace q_sort_int {

inline int *partition(int *begin, int *end) {
  std::iter_swap(begin + generator(engine) % (end - begin), end - 1);
  const int pivot = *--end;
  int *i = begin;
  while (begin != end) {
    if (*begin < pivot) {
      std::iter_swap(i++, begin);
    }
    ++begin;
  }
  return i;
}

inline void quick_sort(int *const begin, int *const end) {
  if (end - begin <= 1)
    return;
  int *const mid = partition(begin, end);
  quick_sort(begin, mid);
  quick_sort(mid, end);
}

} // namespace q_sort_int

#endif