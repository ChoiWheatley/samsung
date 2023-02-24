#ifndef SOLUTION
#define SOLUTION

#include <array>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <string>
using std::array;
using std::string;
using uint = unsigned int;

constexpr size_t MAX_STR = 500'000;
constexpr size_t MAX_PAT = 100'000;

/**
KMP
*/
namespace sol1 {

static array<uint, MAX_PAT> _fail;

static array<uint, MAX_PAT> &create_fail(string const &pat) {
  _fail.fill(0);
  size_t j = 0;
  for (size_t i = 1; i < pat.size(); ++i) {
    while (j > 0 && pat[i] != pat[j]) {
      // 글자 불일치시, 가장 마지막으로 일치했던 순간의 접두어로 이동한다.
      j = _fail[j - 1];
    }
    if (pat[i] == pat[j]) {
      // 글자 일치!
      j++;
      _fail[i] = j;
    }
  }
  return _fail;
}

template <class Consumer>
static void do_compare(string const &str, string const &pat,
                       array<uint, MAX_PAT> const &fail,
                       Consumer const &on_equal) {
  size_t j = 0;
  for (size_t i = 0; i < str.size(); ++i) {
    while (j > 0 && str[i] != pat[j]) {
      j = fail[j - 1];
    }
    if (str[i] != pat[j])
      continue;
    // 글자 일치
    j++;
    if (j == pat.size()) {
      // 단어 일치시, 일치하기 시작하는 인덱스를 인자로 콜백함수를 호출한다.
      on_equal(i - pat.size() + 1);
    }
  }
}

/**
@breif:
원본 문자열 str에 특정 단어 pat이 등장하는 횟수를 구하자!
전략: KMP
*/
inline size_t solution(string const &str, string const &pat) {
  auto const &fail = create_fail(pat);
  size_t cnt = 0;
  do_compare(str, pat, fail, [&cnt](size_t) { cnt++; });
  return cnt;
}

} // namespace sol1

/**
Rabin-Karp
*/
namespace sol2 {

using i64 = int64_t;

constexpr i64 MOD = 1000000007;
constexpr i64 BASE = 31;
constexpr i64 _mod(i64 value) {
  auto rem = value % MOD;
  if ((rem < 0 && MOD > 0) || (rem > 0 && MOD < 0)) {
    rem += MOD;
  }
  return rem;
}

inline i64 solution(string const &str, string const &pat) {

  // init H(pat)
  i64 key = 0;
  i64 base = 1;
  for (char c : pat) {
    key = _mod(key + (c * base));
    base = _mod(base * BASE);
  }

  // Rolling hash (Rabin fingerprint)
  base = 1;
  i64 fingerprint = 0;
  for (size_t i = 0; i < pat.size(); ++i) { // init fingerprint
    fingerprint = _mod(fingerprint + (str[i] * base));
    base = _mod(base * BASE);
  }
  // do compare
  size_t cnt = 0;
  i64 l_base = 1;
  i64 r_base = base;
  for (size_t i = 0; i <= str.size() - pat.size(); ++i) {
    auto key_shifted = _mod(key * l_base);
    if (key_shifted == fingerprint) {
      cnt++;
    }
    fingerprint = _mod(fingerprint - (str[i] * l_base));
    fingerprint = _mod(fingerprint + (str[i + pat.size()] * r_base));
    l_base = _mod(l_base * BASE);
    r_base = _mod(r_base * BASE);
  }
  return cnt;
}
} // namespace sol2

#endif