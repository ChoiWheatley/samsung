#ifndef SOLUTION
#define SOLUTION

#include <random>
#include <utility>
static std::mt19937 engine{std::random_device{}()};
static std::uniform_int_distribution<unsigned int> generator{};

namespace sol1 {

template <typename Iter, class Less>
Iter partition(Iter begin, Iter end, Less const &less) {
  auto pivot = begin + generator(engine) % (end - begin);
  std::swap(*pivot, *(end - 1));
  pivot = end - 1;
  size_t count = 0;
  for (auto cur = begin; cur != pivot; ++cur) {
    if (less(*cur, *pivot)) {
      // move element to left
      std::swap(*cur, *(begin + count));
      count += 1;
    }
  }
  // move pivot to right place
  std::swap(*pivot, *(begin + count));
  return begin + count;
}

template <typename Iter, class Less>
void sort(Iter begin, Iter end, Less const &less) {
  if (end - begin <= 1) {
    return;
  }
  auto mid = sol1::partition(begin, end, less);
  sol1::sort(begin, mid, less);
  sol1::sort(mid + 1, end, less);
}

} // namespace sol1
#endif