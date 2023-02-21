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

constexpr size_t MOD = 100'000'000'003; // prime number
constexpr size_t B = 2; // 라빈카프 알고리즘의 제곱수

constexpr size_t B_POW(size_t times) {
  size_t b = 1;
  while (times-- > 0) {
    b = (b * B) % MOD;
  }
  return b;
}

template <typename T>
inline T get_or(vector<vector<T>> const &ls2d, size_t row, size_t col,
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
inline vector<vector<size_t>> rabin_karp_2d(vector<string> const &str2d) {

  const auto n = str2d.size();
  const auto m = str2d[0].size();
  auto ret = vector<vector<size_t>>(n, vector<size_t>(m));

  size_t b = 1;
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      ret[i][j] = (str2d[i][j] * b) % MOD;
      b = (b * B) % MOD;
    }
  }

  return ret;
}

/**
인자로 받은 이차원 배열을 누적배열로 변환한다.
*/
inline vector<vector<size_t>> cumulative_sum(vector<vector<size_t>> &&ls) {

  const auto n = ls.size();
  const auto m = ls[0].size();

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      ls[i][j] = (ls[i][j] + get_or(ls, i, j - 1)) % MOD;
      ls[i][j] = (ls[i][j] + get_or(ls, i - 1, j)) % MOD;
      ls[i][j] = (ls[i][j] - get_or(ls, i - 1, j - 1)) % MOD;
    }
  }
  return std::move(ls);
}

/**
(i1, j1) 부터 (i2, j2) 까지의 부분합을 계산한다.
*/
inline size_t partial_sum(vector<vector<size_t>> const &cumulated, //
                          size_t i1, size_t j1, size_t i2, size_t j2) {
  size_t ret = 0;
  ret += cumulated[i2][j2];
  ret -= get_or(cumulated, i2, j1 - 1);
  ret -= get_or(cumulated, i1 - 1, j2);
  ret += get_or(cumulated, i1 - 1, j1 - 1);
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
  // namespace sol1
#endif