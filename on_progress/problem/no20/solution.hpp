/**
최대공통부분수열 (Longest Common Sequence)는 두 수열이 주어질 때 공통적인
부분수열 중 가장 긴 수열을 찾는다.

이 문제는 수열을 알파벳 소문자만을 활용한 문자열로 정의한다. 따라서 두 알파벳
소문자로 이뤄진 문자열이 주어졌을 때 가장 긴 공통부분수열 (공통부분문자열이
아님을 유의)의 길이를 찾아 리턴하면 된다.
*/

#ifndef SOLUTION
#define SOLUTION
#include <algorithm>
#include <array>
#include <string>

using std::array;
using std::string;
constexpr size_t MAX_LEN = 1'000;

namespace sol1 {
constexpr size_t MAX_LEN = 1'000;
/**S1의 i번째 인덱스까지의 LCS*/
static array<size_t, MAX_LEN * 2> memo;
/**S2의 탐색을 시작할 인덱스*/
static array<size_t, MAX_LEN * 2> begin;

inline auto solution(string &&s1, string &&s2) -> size_t {
  size_t best = 0;
  for (size_t start_idx = 0; start_idx < s1.size(); ++start_idx) {
    size_t memo_prev = 0;
    for (size_t i = start_idx; i < s1.size(); ++i) {
      memo[i] = memo_prev;
      for (size_t j = begin[i]; j < s2.size(); ++j) {
        if (s1[i] == s2[j]) {
          begin[i + 1] = j + 1;
          memo[i] += 1;
          memo_prev = memo[i];
          break;
        }
      }
    }
    best = std::max(best, memo[s1.size() - 1]);
  }
  return best;
}
} // namespace sol1

namespace sol2 {

/**S1의 i개, S2의 j개 LCS의 길이*/
static array<array<size_t, MAX_LEN + 1>, MAX_LEN + 1> memo;

inline auto solution(string &&s1, string &&s2) -> size_t {
  size_t best = 0;
  for (size_t i = 1; i <= s1.size(); ++i) {
    for (size_t j = 1; j <= s2.size(); ++j) {
      if (s1[i - 1] == s2[j - 1]) {
        memo[i][j] = memo[i - 1][j - 1] + 1;
      } else {
        memo[i][j] = std::max(memo[i - 1][j], memo[i][j - 1]);
      }
      best = memo[i][j];
    }
  }
  return best;
}
} // namespace sol2

#endif
