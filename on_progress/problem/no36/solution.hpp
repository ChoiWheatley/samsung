#ifndef SOLUTION
#define SOLUTION

#include <algorithm>
#include <array>
#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>
using std::array;
using u32 = uint32_t;

constexpr u32 MAX_DAY = 1'000'000;
constexpr u32 MAX_N = 200'000;
constexpr u32 MAX_P = 200'000;

namespace bitset {

constexpr u32 BITS = sizeof(u32) * 8;
constexpr u32 MAX_BUCKETS = MAX_DAY / BITS;

static array<u32, MAX_BUCKETS + 1> _bitset;

inline void init() { _bitset.fill(0); }
inline bool check(u32 idx) {
  auto bucket = idx / BITS;
  auto bit = idx % BITS;
  return (_bitset[bucket] >> bit) & 1;
}
/**set bit to true*/
inline void set(u32 idx) {
  auto bucket = idx / BITS;
  auto bit = idx % BITS;
  _bitset[bucket] |= (1 << bit);
}
/**set bit to false*/
inline void reset(u32 idx) {
  auto bucket = idx / BITS;
  auto bit = idx % BITS;
  _bitset[bucket] &= ~(1 << bit); // X & 0b111111011111
}

} // namespace bitset

/**
@breif:
  False -- True 구간의 첫번째 True를 찾아줘요.
@param:
 - begin: inclusive
 - end: exclusive
 - pred: predicate, 이를 사용하여 first_true도, first_false도 가능.
*/
template <class Predicate>
inline int first_true(int begin, int end, Predicate const &pred) {
  auto l = begin;
  auto r = end;
  while (l != r) {
    auto m = l + (r - l) / 2; // overflow 방지
    if (pred(m)) {
      // 구간 [m, r) 을 볼 필요 없으니 다음 구간은 [l, m)이다.
      r = m;
    } else {
      // 구간 [l, m + 1)를 볼 필요 없으니 다음 구간은 [m+1, r)이다.
      l = m + 1;
    }
  }
  return l;
}

/**
@breif:
  True -- False 구간의 첫번째 False를 찾아줘요.
*/
template <class Predicate>
inline int first_false(int begin, int end, Predicate const &pred) {
  auto pred_inversed = [&pred](auto i) { return !pred(i); };
  return first_true(begin, end, pred_inversed);
}

namespace sol1 {

/**
@notice: bitset 초기화 진행 후 호출하세요!

@breif: 영어공부를 한 날 이외에 p개의 날짜에 체크를 했을 때, 영어공부를 매일매일
했던 연속 기간의 최장일수를 구하여라.

스트릭(연속기간)의 길이를 L이라 할때, L의 길이를 최장으로 만드는 문제는 최적화
문제이다. 하지만 파라메트릭 서치를 활용하면 "스트릭을 L로 만들 수 있는지"
라는 결정 문제로 바뀌게 된다.

True -- False 문제이므로 first_false를 찾은 뒤에 -1 하면 마지막 True를 찾을
수 있다.
*/
inline int solution(u32 n, u32 p, u32 last_day) {
  // 길이 length 의 스트릭을 달성할 수 있나요?
  auto pred = [p, last_day](int length) {
    // window[0:length - 1] 안에 비어있는 check의 개수
    int window = 0;
    for (int i = 0; i < length; ++i) { // init window
      window += bitset::check(i) ? 0 : 1;
    }
    // slide window
    for (int i = 1; i <= last_day - length; ++i) {
      if (window <= p) {
        return true;
      }
      window -= bitset::check(i - 1) ? 0 : 1;          // left delete
      window += bitset::check(i + length - 1) ? 0 : 1; // right add
    }
    return false;
  };
  return first_false(1, n + p, pred) - 1;
}

} // namespace sol1

namespace sol2 {

using std::vector;

/**
@breif:
  length 길이에 스트릭을 만들 수 있나요?
 sliding 과정을 효율적으로 하기 위해 set bit들 간의 거리를
 사용한다.

@param:
 - delta: days각 원소들 간에 차를 들고있다.
*/
inline bool _predicate(vector<u32> const &delta, u32 p, int length) {

  if (p >= length - 1) {
    // 처음과 끝
    return true;
  }
  // 중간
  for (auto begin = delta.begin(); begin != delta.end(); ++begin) {

    int streak = 1;
    u32 sum = 0; // delta sum
    for (auto itr = begin; itr != delta.end(); ++itr) {

      auto const &elem = *itr;

      sum += elem - 1;
      if (sum > p) {
        break;
      }
      streak += elem;
      if (streak + (p - sum) >= length) {
        return true;
      }
    }
  }
  return false;
}

/**
@breif:
  bitset을 내부적으로 호출하기 때문에 굳이 init 할 필요 없게됨.
@param:
 - days: 정렬된 상태를 보장하는 영어공부를 실시한 날짜들
 - p: 추가적으로 영어공부를 했다고 뻥칠 수 있는 날들의 개수
*/
inline int solution(vector<u32> const &days, u32 p) {

  bitset::init();
  for (auto e : days) {
    bitset::set(e);
  }

  vector<u32> delta;
  for (size_t i = 0; i < days.size() - 1; ++i) {
    delta.emplace_back(days[i + 1] - days[i]);
  }

  return first_false( //
             1, u32(days.size()) + p,
             [&delta, &p](auto length) {
               return _predicate(delta, p, length);
             }) -
         1;
}

} // namespace sol2

#endif