#ifndef SOLUTION
#define SOLUTION

#include <algorithm>
#include <array>
#include <cstddef>
#include <vector>

using std::array;
using std::size_t;
using std::vector;

class unknown_character {};

constexpr array<char, 4> operators = {'+', '-', '*', '/'};

static inline bool is_digit(char c) { return '0' <= c && c <= '9'; };
static inline bool is_operator(char c) {
  return std::any_of(operators.begin(), operators.end(),
                     [c](char e) { return e == c; });
}

static bool is_expr_recur(const vector<char> &bintree, size_t idx) {
  if (idx >= bintree.size()) {
    return true;
  }
  char c = bintree.at(idx);
  if (is_digit(c)) { // must be a leaf node
    return idx * 2 + 1 >= bintree.size();
  } else if (is_operator(c)) {
    return (is_expr_recur(bintree, idx * 2 + 1)) &&
           (is_expr_recur(bintree, idx * 2 + 2));
  } else {
    throw unknown_character{};
  }
}

/** 완전이진트리 형식으로 저장되어 있는 expression이 유효한지 판단한다.
    예를 들어 1+2+3은 유효하지만 1++23 이라던가 +23- 같은 expression
    은 유효하지 않다.
 */
inline bool solution(const vector<char> &bintree) {
  return is_expr_recur(bintree, 0);
}
#endif