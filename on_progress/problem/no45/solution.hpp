/**
부분합 기출변형, \Sum_{i=l}^{r-1}{a_i \by (-1)^{i-l}}
예를 들어 S = {1,2,3,4,5} 일 때
jagged_sum(0,4) = 1-2+3-4+5 = 3
*/
#ifndef SOLUTION
#define SOLUTION

#include <array>

using uint = unsigned int;
using cuint = const uint;
using elem_t = long long int;
using celem_t = const elem_t;

constexpr uint N = 100'000;
constexpr uint HEIGHT = 17; // log(N, 2)
constexpr uint LEN = (1 << (HEIGHT + 1));

constexpr uint _left(uint node) { return node << 1; }
constexpr uint _right(uint node) { return (node << 1) | 1; }

/**
[Fail]
미리 range [l, r-1]에 대한 세그먼트 트리를 구성해 놓았으나, query 시에
누구를 더해야 하고 누구를 빼야할지 알 수 없다는 치명적인 단점이 존재.
*/
namespace sol1 {

using Arr = std::array<elem_t, N>;

static Arr _tree;

struct nothing_contains_exception {};

template <typename T> struct Box {
  T value{};
  bool contains = false;
  constexpr explicit Box(T value) : value{value}, contains{true} {}
  constexpr explicit Box() = default;
  constexpr static auto empty() { return Box{}; }
  T &get() {
    if (!contains) {
      throw nothing_contains_exception{};
    }
    return value;
  }
};

/**Internal*/

/**add two child value*/
constexpr static elem_t _do_add(celem_t &left_child, celem_t &right_child,
                                cuint start, cuint end) {
  cuint mid = (start + end) / 2;
  if ((mid - start) % 2 == 0) {
    // even
    return left_child - right_child;
  } else {
    // odd
    return left_child + right_child;
  }
}

static Box<celem_t> _jagged_sum(Arr const &tree, cuint left, cuint right, //
                                uint node, uint start, uint end) {
  if (right < start || end < left) { // invalid range
    return Box<celem_t>::empty();
  }
  if (left <= start && end <= right) { // perfect range
    return Box<celem_t>(tree[node]);
  }
  // 두 노드에 걸쳐있는 경우
  uint mid = (start + end) / 2;
  auto left_child = _jagged_sum(tree, left, right, _left(node), start, mid);
  auto right_child = _jagged_sum(tree, left, right, _right(node), mid + 1, end);
  // merge
  if (left_child.contains && right_child.contains) {

    return Box<celem_t>(
        _do_add(left_child.get(), right_child.get(), start, end));
  } else if (!left_child.contains && !right_child.contains) {

    return Box<celem_t>::empty();
  } else {

    return left_child.contains ? left_child : right_child;
  }
}

/**
@breif: 재귀적으로 tree를 초기화.
@param:
  - data: 원본 배열
  - n: 원본 배열의 크기
  - node: tree의 노드의 인덱스
  - start: tree의 범위 시작 - inclusive
  - end: tree의 범위 끝 - inclusive
*/
static void _init(Arr const &data, Arr &tree, uint node, uint start, uint end) {
  if (start == end) { // leaf node
    tree[node] = data[start];
    return;
  }
  // recursive
  auto mid = (start + end) / 2;
  _init(data, tree, _left(node), start, mid);
  _init(data, tree, _right(node), mid + 1, end);
  // set current node
  tree[node] = _do_add(tree[_left(node)], tree[_right(node)], start, end);
}

/**
@breif: 재귀적으로 업데이트를 수행하며 연관 노드들을 같이 수정한다.
*/
static void _update(Arr &tree, cuint idx, celem_t value, uint node, //
                    uint start, uint end) {
  if (idx < start || end < idx) { // idx는 이 노드에 없다.
    return;
  }
  if (start == end) { // leaf node
    tree[node] = value;
    return;
  }
  uint mid = (start + end) / 2;

  // idx가 포함된 구간을 가지고 있는 자식노드만 순회하면 된다.
  _update(tree, idx, value, _left(node), start, mid);
  _update(tree, idx, value, _right(node), mid + 1, end);

  // 현재 노드에 가해질 변화 적용
  tree[node] = _do_add(tree[_left(node)], tree[_right(node)], start, end);
}

/**INTERFACES*/

/**data를 세그먼트 트리로 변환한다.*/
inline void init(Arr const &data, cuint n) { _init(data, _tree, 1, 0, n - 1); }

/**data[idx] := value */
inline void update(cuint idx, celem_t value, cuint n) {
  _update(_tree, idx, value, 1, 0, n - 1);
}

/**
@breif:
  [left, right-1] 범위의 i에 대하여 a_i를 번갈아가며 더하고 뺀 값을 출력한다.
*/
inline elem_t jagged_sum(cuint left_inclusive, cuint right_exclusive, cuint n) {
  return _jagged_sum(_tree, left_inclusive, right_exclusive - 1, 1, 0, n - 1)
      .get();
}

} // namespace sol1

/**
이번엔 odd 인덱스와 even 인덱스들끼리 따로 sum을 갖는 세그먼트 트리를 만들어 풀
것이다.

Node:
  + sum_odd
  + sum_even

*/
namespace sol2 {

constexpr bool _even(uint n) { return n % 2 == 0; }
constexpr bool _odd(uint n) { return !_even(n); }

struct Node {
  elem_t sum_odd{};
  elem_t sum_even{};
  constexpr explicit Node(elem_t sum_odd, elem_t sum_even)
      : sum_odd{sum_odd}, sum_even{sum_even} {}
  constexpr Node() = default;
  constexpr static Node even(elem_t elem) { return Node(0, elem); }
  constexpr static Node odd(elem_t elem) { return Node(elem, 0); }
};
inline Node operator+(Node const &lhs, Node const &rhs) {
  return Node(lhs.sum_odd + rhs.sum_odd, lhs.sum_even + rhs.sum_even);
}
inline Node operator-(Node const &rhs) {
  return Node(-rhs.sum_odd, -rhs.sum_even);
}
inline Node operator-(Node const &lhs, Node const &rhs) { return lhs + (-rhs); }
inline bool operator==(Node const &lhs, Node const &rhs) {
  return lhs.sum_odd == rhs.sum_odd && lhs.sum_even == rhs.sum_even;
}

template <typename T> using Arr = std::array<T, LEN>;

static Arr<Node> _tree;

/**INTERNALS*/

/**
tree를 세그먼트 트리 구조로 초기화 한다.
*/
static void _init(std::array<elem_t, N> const &data, Arr<Node> &tree, uint node,
                  uint start, uint end) {
  if (start == end) { // leaf node
    tree[node] =
        _even(start) ? Node::even(data[start]) : Node::odd(data[start]);
    return;
  }
  auto mid = (start + end) / 2;
  _init(data, tree, _left(node), start, mid);
  _init(data, tree, _right(node), mid + 1, end);
  // merge two children
  tree[node] = tree[_left(node)] + tree[_right(node)];
}

static void _update(Arr<Node> &tree, cuint idx, celem_t value, uint node,
                    uint start, uint end) {
  if (idx < start || end < idx) { // wrong node
    return;
  }
  if (start == idx && end == idx) { // leaf node
    tree[node] = _even(start) ? Node::even(value) : Node::odd(value);
    return;
  }
  auto mid = (start + end) / 2;
  _update(tree, idx, value, _left(node), start, mid);
  _update(tree, idx, value, _right(node), mid + 1, end);
  // merge
  tree[node] = tree[_left(node)] + tree[_right(node)];
}

/**
여기에서는 단순히 노드들을 더한 결과를 리턴한다.
*/
static Node _sum(Arr<Node> const &tree, cuint left, cuint right, uint node,
                 uint start, uint end) {
  if (end < left || right < start) { // wrong node
    return Node(0, 0);
  }
  if (left <= start && end <= right) { // node inside the range
    return tree[node];
  }
  // overlapped range
  auto mid = (start + end) / 2;
  Node left_child = _sum(tree, left, right, _left(node), start, mid);
  Node right_child = _sum(tree, left, right, _right(node), mid + 1, end);
  return left_child + right_child;
}

/**INTERFACES*/

/**data를 세그먼트 트리로 변환한다.*/
inline void init(std::array<elem_t, N> const &data, cuint n) {
  _tree.fill(Node());
  _init(data, _tree, 1, 0, n - 1);
}

/**data[idx] := value */
inline void update(cuint idx, celem_t value, cuint n) {
  _update(_tree, idx, value, 1, 0, n - 1);
}

/**
@breif:
  [left, right-1] 범위의 i에 대하여 a_i를 번갈아가며 더하고 뺀 값을 출력한다.
*/
inline elem_t jagged_sum(cuint left_inclusive, cuint right_exclusive, cuint n) {
  Node sum = _sum(_tree, left_inclusive, right_exclusive - 1, 1, 0, n - 1);
  return _even(left_inclusive) ? sum.sum_even - sum.sum_odd
                               : sum.sum_odd - sum.sum_even;
}

} // namespace sol2
#endif