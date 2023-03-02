#ifndef SOLUTION
#define SOLUTION

#include <algorithm>
#include <cmath>
#include <limits>
#include <utility>
#include <vector>
using std::abs;
using std::pair;
using std::vector;

/**
F-...-F-F-F-T-T-T-...-T
            ^
*/
template <typename T, class Predicate>
inline T first_true(T begin, T end, Predicate const &pred) {

  T l = begin;
  T r = end;
  while (l < r) {
    T mid = l + (r - l) / 2;
    if (pred(mid)) {
      // next range is [l, mid)
      r = mid;
    } else {
      // next range is [mid + 1, r)
      l = mid + 1;
    }
  }
  return l;
}

/**
@return:
 - first: 가장 가까운 쌍의 거리
 - second: 그러한 거리를 갖는 쌍의 개수
*/
inline pair<int, int> solution(vector<int> const &cows, vector<int> &horses) {
  //
  std::sort(horses.begin(), horses.end());

  int min_dist = std::numeric_limits<int>::max();
  int count = 0;

  auto evaluate = [&min_dist, &count](int dist) {
    if (dist < min_dist) {
      min_dist = dist;
      count = 1;
    } else if (dist == min_dist) {
      count += 1;
    }
  };

  for (auto const &cow : cows) {
    // 어떤 소에 대하여 (소 <= 말) 조건을 만족시키는 첫번째 말을 고른다.
    // 그 말의 바로 이전 말과 비교하여 더 가까운 놈을 선택한다.
    auto horse_itr = first_true(horses.begin(), horses.end(),
                                [cow](auto itr) { return cow <= *itr; });
    if (horse_itr != horses.end()) {
      evaluate(abs(cow - *horse_itr));
    }
    if (horse_itr != horses.begin()) {
      evaluate(abs(cow - *(horse_itr - 1)));
    }
  }

  return std::make_pair(min_dist, count);
}

#endif