/**
https://www.notion.so/choiwheatley/LIS-d61b26f5619a4ea1b0412155535ec812
*/
#ifndef SOLUTION
#define SOLUTION

#include <array>
#include <vector>
using std::array;
using std::vector;

namespace lis_with_bin_search {

constexpr size_t MAX_CACHE = 1000;
/**
@brief: cache[i] : 길이 i짜리 LIS의 가장 작은 수열.
cache배열은 값 자체를 갖고있는 것이 아닌, seq의 인덱스를 가지고 있다.
seq[cache[0..N]] 배열을 계속해서 정렬된 상태로 만들어두면 로그시간에 탐색이
가능해진다.*/
static array<size_t, MAX_CACHE> cache;

inline int lis(const vector<int> &seq) {
  int L = 0;
  int newL = 0;
  cache.fill(0);

  // cache[0]은 사용하지 않는다는 것을 염두하세요.
  for (size_t i = 0; i < seq.size(); i++) {
    // seq[i] > seq[cache[j]]를 만족하는 가장 큰 j를 찾는다.
    int lo = 1;
    int hi = L;
    while (lo <= hi) {
      int mid = (lo + hi) / 2;
      if (seq[i] > seq[cache[mid]])
        lo = mid + 1;
      else
        hi = mid - 1;
    }
    newL = lo;
    cache[newL] = i;
    if (newL > L)
      L = newL;
  }

  return L;
}
} // namespace lis_with_bin_search
#endif