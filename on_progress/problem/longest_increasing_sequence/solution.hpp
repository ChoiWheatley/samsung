/**
https://www.notion.so/choiwheatley/LIS-d61b26f5619a4ea1b0412155535ec812
*/
#ifndef SOLUTION
#define SOLUTION

#include <algorithm>
#include <array>
#include <iterator>
#include <vector>
using std::array;
using std::vector;
constexpr size_t MAX_CACHE = 1000;

namespace lis_with_bin_search {
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

namespace lis_with_list {

// X[i] : 입력으로 주어진 수열
// M[k] : 수열 X의 길이 k인 부분수열 중에서 마지막 인덱스의
// 값이 가장 작은 값을 저장. 값이지 인덱스가 아님.
// P[i] : X[i]가 바라보고 있는 M 배열의 인덱스
inline vector<int> lis(const vector<int> &X) {
  array<size_t, MAX_CACHE + 1> M;
  array<size_t, MAX_CACHE> P;
  int L = 0;
  int newL = 0;

  M.fill(0);
  P.fill(0);
  for (size_t i = 0; i < X.size(); ++i) {
    int lo = 1;
    int hi = L;
    int mid = 1;
    // find lower bound using binary search
    while (lo <= hi) {
      mid = (lo + hi) / 2;
      if (M[mid] < X[i])
        lo = mid + 1;
      else
        hi = mid - 1;
    }
    // after binary search, lo gets 1 greater
    // than L

    // M replace (or append) new value X[i]
    // and P keeps tracking on M's index
    newL = lo;
    M[newL] = X[i];
    P[i] = newL;

    // when append we have to set hi value
    if (newL > L)
      L = newL;
  }

  // backtracking to get LIS
  // we only care when M gets appended!
  vector<int> ret(L);
  int r = L - 1;
  for (int i = (int)X.size() - 1; i >= 0; --i) {
    if (L == P[i]) {
      ret[r] = X[i];
      L--;
      r--;
    }
  }

  return ret;
}

} // namespace lis_with_list
#endif