#ifndef SOLUTION
#define SOLUTION

#include <cstddef>
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
constexpr int64_t B = 31;              // 라빈카프 알고리즘의 제곱수

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
라빈카프 알고리즘의 결과를 리턴한다.
*/
inline vector<vector<int64_t>> rabin_karp_2d(vector<string> const &str2d) {

  const auto n = str2d.size();
  const auto m = str2d[0].size();
  auto ret = vector<vector<int64_t>>(n, vector<int64_t>(m));

  for (int64_t i = 0; i < n; ++i) {
    for (int64_t j = 0; j < m; ++j) {
      ret[i][j] = mod((str2d[i][j] * pow(B, i * m + j)), MOD);
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
@param:
 - h: height of dream
 - w: width of dream
 - n: height of sam
 - m: width of sam
*/
inline int solution(int h, int w, int n, int m, //
                    string const &dream, string const &sam) {}

} // namespace sol2
#endif