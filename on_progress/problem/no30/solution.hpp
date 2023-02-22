#ifndef SOLUTION
#define SOLUTION

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
using std::string;
using std::stringstream;
using std::vector;

namespace sol1 {

static vector<size_t> djb2(const string &key) {
  vector<size_t> hash = {5381};
  for (auto c : key) {
    hash.push_back(((*hash.crbegin() << 5) + *hash.crbegin()) + c);
  }
  return hash;
}

/**
@breif: 일렬로 만든 두 이차원 문자열 dream, sam으로부터 dream이 sam에 몇 번
나타나는지 알아내시오.
@param:
 - h: height of dream
 - w: width of dream
 - n: height of sam
 - m: width of sam
*/
inline int solution(int h, int w, int n, int m, //
                    string const &dream, string const &sam) {
  vector<size_t> dream_key = djb2(dream);
  vector<size_t> sam_key = djb2(sam);
  int cnt = 0;
  // i,j = start position
  for (int i = 0; i < n - h + 1; ++i) {
    for (int j = 0; j < m - w + 1; ++j) {
      stringstream concater;
      // append str into concater
      for (int row = 0; row < h; ++row) {
        int startidx = (i + row) * n + j;
        concater << sam.substr(startidx, w);
      }
      string subpicture = concater.str();
      if (dream_key == djb2(subpicture)) {
        cnt++;
      }
    }
  }
  return cnt;
}

} // namespace sol1

/**
Rabin Karp Algorithm
https://codingdog.tistory.com/entry/라빈-카프-알고리즘-그래도-비벼볼-만한-문제가-있다

1. 전처리:
 - 꿈그림은 라빈카프 해시함수로 전체 문자열에 대한 해시값을 저장 하자 => key
 - 샘그림은 누적합을 저장해놓는 이차원 배열에 보관하자.

2. size(꿈그림)=(h,w), size(샘그림) = (n,m)일 때,
  i = 0..n-h, j = 0..m-w 에 대하여
  Sum(start: (i,j), height: h, width: w) == key * B^{i*m+j}를 만족할 때에
count를 증가시킨다.
*/
namespace sol2 {

constexpr int64_t MOD = 1'000'000'007; // prime number
constexpr int64_t B = 2;               // 라빈카프 알고리즘의 제곱수

template <typename T> constexpr T mod(T x, T m) {
  auto r = x % m;
  if ((r < 0 && m > 0) || (r > 0 && m < 0)) {
    return r + m;
  }
  return r;
}

constexpr int64_t pow(int64_t base, int64_t exp) {
  int64_t ret = 1;
  for (int64_t i = 0; i < exp; ++i) {
    ret = mod((ret * base), MOD);
  }
  return ret;
}

template <typename T>
inline T get_or(vector<vector<T>> const &ls2d, int64_t row, int64_t col,
                T orthen = T{}) {
  if (row < 0 || ls2d.size() < row || //
      col < 0 || ls2d[row].size() < col) {
    return orthen;
  }
  return ls2d[row][col];
}

/**
@breif: 라빈카프 알고리즘의 결과를 리턴한다.
@param:
 - dim_col: 해시값을 만드는 데 동일한 디멘션을 가져야 동일한 구간에서
동등한 비교를 수행할 수 있다.
*/
inline vector<vector<int64_t>> rabin_karp_2d(vector<string> const &str2d,
                                             int64_t dim_col) {

  const auto n = str2d.size();
  const auto m = str2d[0].size();
  auto ret = vector<vector<int64_t>>(n, vector<int64_t>(m));

  for (int64_t i = 0; i < n; ++i) {
    for (int64_t j = 0; j < m; ++j) {
      ret[i][j] = mod((str2d[i][j] * pow(B, i * dim_col + j)), MOD);
    }
  }

  return ret;
}

/**
인자로 받은 이차원 배열을 누적배열로 변환한다.
*/
inline vector<vector<int64_t>> cumulative_sum(vector<vector<int64_t>> &&ls) {

  const auto n = ls.size();
  const auto m = ls[0].size();

  for (int64_t i = 0; i < n; ++i) {
    for (int64_t j = 0; j < m; ++j) {
      ls[i][j] = mod((ls[i][j] + get_or(ls, i, j - 1)), MOD);
      ls[i][j] = mod((ls[i][j] + get_or(ls, i - 1, j)), MOD);
      ls[i][j] = mod((ls[i][j] - get_or(ls, i - 1, j - 1)), MOD);
    }
  }
  return std::move(ls);
}

/**
(i1, j1) 부터 (i2, j2) 까지의 부분합을 계산한다.
*/
inline int64_t partial_sum(vector<vector<int64_t>> const &cumulated, //
                           int64_t i1, int64_t j1, int64_t i2, int64_t j2) {
  int64_t ret = cumulated[i2][j2];
  ret = mod((ret - get_or(cumulated, i2, j1 - 1)), MOD);
  ret = mod((ret - get_or(cumulated, i1 - 1, j2)), MOD);
  ret = mod((ret + get_or(cumulated, i1 - 1, j1 - 1)), MOD);
  return ret;
}

/**
@breif: 일렬로 만든 두 이차원 문자열 dream, sam으로부터 dream이 sam에 몇 번
나타나는지 알아내시오.
 - h: height of dream
 - w: width of dream
 - n: height of sam
 - m: width of sam
*/
inline int solution(vector<string> const &dream, vector<string> const &sam) {
  const auto h = dream.size();
  const auto w = dream[0].size();
  const auto n = sam.size();
  const auto m = sam[0].size();

  auto key1 = rabin_karp_2d(dream, m);
  auto key2 = rabin_karp_2d(sam, m);

  key1 = cumulative_sum(std::move(key1));
  key2 = cumulative_sum(std::move(key2));

  auto real_sum = key1[h - 1][w - 1];

  /**
  real_sum * pow(B, i*m+j) == fake_sum => cnt++
  */
  int cnt = 0;
  for (int i = 0; i <= n - h; ++i) {
    for (int j = 0; j <= m - w; ++j) {

      auto i2 = i + h - 1;
      auto j2 = j + w - 1;

      auto fake_sum = partial_sum(key2, i, j, i2, j2);
      auto lhs = mod(real_sum * pow(B, i * m + j), MOD);

      if (lhs == fake_sum) {
        cnt += 1;
      }
    }
  }
  return cnt;
}

} // namespace sol2

/**
Rabin-Karp with Base = 2, MOD = 1 << 64
 - pow 연산은 비트시프트 만으로 달성이 가능하다.
 - mod 연산을 할 필요가 없다. uint64의 범위 자체가 버킷사이즈가 된다.
문제 조건에 의해 'o'과 'x' 두개의 문자만 주어지기 때문에 각각 1과 2로
사상시켜 문제를 풀 수 있다.
*/
namespace sol3 {
using i64 = int64_t;

constexpr i64 MOD = 1'000'000'007; // prime number

constexpr i64 ascii_map(char code) {
  switch (code) {
  case 'o':
    return 1 << 0;
  case 'x':
    return 1 << 1;
  default:
    exit(2);
  }
}
template <typename T> constexpr T mod(T x, T m = MOD) {
  auto r = x % m;
  if ((r < 0 && m > 0) || (r > 0 && m < 0)) {
    return r + m;
  }
  return r;
}
constexpr i64 pow2(size_t exp) {
  i64 ret = 1;
  for (size_t i = 0; i < exp; ++i) {
    ret = mod(ret << 1);
  }
  return ret;
}
template <typename T>
constexpr T get_or(vector<vector<T>> const &ls2d, i64 row, i64 col,
                   T orthen = T{}) {
  if (row < 0 || ls2d.size() < row || //
      col < 0 || ls2d[row].size() < col) {
    return orthen;
  }
  return ls2d[row][col];
}

/**
@breif:
 -  라빈-카프 해시를 수행하고, ls를 갱신한다.
@param:
 - dim_col: 두 이차원 배열을 해싱으로 비교하기 위하여 같은 차원에 두어야 한다.
*/
inline void rabin_karp(vector<vector<i64>> &ls, i64 dim_col) {

  const auto row = ls.size();
  const auto col = ls[0].size();

  for (size_t i = 0; i < row; ++i) {
    for (size_t j = 0; j < col; ++j) {
      auto &cur = ls[i][j];
      cur = mod(cur * pow2(i * dim_col + j));
    }
  }
}

/**
@breif:
 - 인자로 받은 이차원 배열을 누적배열로 변환하여 ls를 갱신한다.
cumulate(i, j): (0,0)부터 (i,j) 인덱스까지의 원소들을 모두 더한 값
*/
inline void cumulative_sum(vector<vector<i64>> &ls) {

  const auto row = ls.size();
  const auto col = ls[0].size();

  for (size_t i = 0; i < row; ++i) {
    for (size_t j = 0; j < col; ++j) {

      auto &cur = ls[i][j];
      cur = mod(cur + get_or(ls, i - 1, j));
      cur = mod(cur + get_or(ls, i, j - 1));
      cur = mod(cur - get_or(ls, i - 1, j - 1));
    }
  }
}

/**
@breif:
 - (i1, j1) 부터 (i2, j2) 까지의 부분합을 계산한다.
*/
inline i64 partial_sum(vector<vector<i64>> const &cumulated, //
                       i64 i1, i64 j1, i64 i2, i64 j2) {

  i64 result = cumulated[i2][j2];
  result = mod(result - get_or(cumulated, i1 - 1, j2));
  result = mod(result - get_or(cumulated, i2, j1 - 1));
  result = mod(result + get_or(cumulated, i1 - 1, j1 - 1));
  return result;
}

inline int solution(vector<string> const &dream, vector<string> const &sam) {

  const auto row_dream = dream.size();
  const auto col_dream = dream[0].size();
  const auto row_sam = sam.size();
  const auto col_sam = sam[0].size();
  assert(row_dream <= row_sam && col_dream <= col_sam);

  vector<vector<i64>> dream_mapped;
  vector<vector<i64>> sam_mapped;

  // init part
  auto init_unary = [](string const &line) {
    vector<i64> temporary;
    std::transform(line.cbegin(), line.cend(), //
                   std::back_inserter(temporary), &ascii_map);
    return temporary;
  };
  std::transform(dream.cbegin(), dream.cend(), //
                 std::back_inserter(dream_mapped), init_unary);
  std::transform(sam.cbegin(), sam.cend(), //
                 std::back_inserter(sam_mapped), init_unary);

  // rabin-karp part
  auto dimension = col_sam;
  rabin_karp(dream_mapped, dimension);
  rabin_karp(sam_mapped, dimension);

  // accumulate part
  cumulative_sum(dream_mapped);
  cumulative_sum(sam_mapped);

  // diff part
  int cnt = 0;
  auto key = dream_mapped[row_dream - 1][col_dream - 1];
  for (auto i = 0; i <= row_sam - row_dream; ++i) {
    for (auto j = 0; j <= col_sam - col_dream; ++j) {

      auto i2 = i + row_dream - 1;
      auto j2 = j + col_dream - 1;
      auto fake_key = partial_sum(sam_mapped, i, j, i2, j2);
      auto real_key = mod(key * pow2(i * dimension + j));

      if (real_key == fake_key) {
        cnt++;
      }
    }
  }
  return cnt;
}

} // namespace sol3

#endif