#ifndef SOLUTION
#define SOLUTION

using uint = unsigned int;
using cuint = const uint;
/**들어오는 배열의 최대 길이*/
constexpr uint N = 100'000;
/**전역적으로 만들어놓을 세그먼트 트리의 최대 높이*/
constexpr uint TREE_HEIGHT = 17; // ceil( log2(N) )
/**전역적으로 만들어놓을 세그먼트 트리의 최대 크기*/
constexpr uint TREE_SIZE = (1 << (TREE_HEIGHT + 1)) + 1;
constexpr bool g_less(uint lhs, uint rhs) { return lhs < rhs; }
constexpr bool g_greater(uint lhs, uint rhs) { return lhs > rhs; }

static uint g_mintree[TREE_SIZE];
static uint g_maxtree[TREE_SIZE];

constexpr uint g_left(uint idx) { return idx << 1; }
constexpr uint g_right(uint idx) { return (idx << 1) | 1; }

/**
@breif:
  재귀를 사용하여 tree를 초기화한다.

@param:
 - start: inclusive
 - end: inclusive
 - less_than: predicate
*/
template <class Less>
static void g_init(uint const data[N], uint tree[TREE_SIZE], uint node,
                   uint start, uint end, Less const &less_than) {
  if (start == end) {
    tree[node] = data[start];
    return;
  }
  uint mid = (start + end) / 2;
  // left
  g_init(data, tree, g_left(node), start, mid, less_than);
  // right
  g_init(data, tree, g_right(node), mid + 1, end, less_than);

  /**현재 노드에 가해질 변화 수정*/
  tree[node] = less_than(tree[g_left(node)], tree[g_right(node)])
                   ? tree[g_left(node)]
                   : tree[g_right(node)];
}

/**
@breif:
  idx 인덱스의 값을 value로 바꾼다. `data[idx] = value`
  이때 영향받는 모든 노드들을 갱신해야 한다.
*/
template <class Less>
static void g_set(uint tree[TREE_SIZE], uint node, uint start, uint end,
                  uint idx, uint value, Less const &less_than) {
  if (start == end) { // leaf
    tree[node] = value;
    return;
  }
  uint mid = (start + end) / 2;

  /**해당 인덱스가 포함된 범위들을 따라 sink-down */
  if (start <= idx && idx <= mid) {
    g_set(tree, g_left(node), start, mid, idx, value, less_than);
  } else {
    g_set(tree, g_right(node), mid + 1, end, idx, value, less_than);
  }

  /**현재 노드에 가해질 변화 수정*/
  tree[node] = less_than(tree[g_left(node)], tree[g_right(node)]) //
                   ? tree[g_left(node)]
                   : tree[g_right(node)];
}

struct null_pointer_exception {};

template <typename T> struct Box {
  T *value_ptr = nullptr;
  bool contains = false;
  constexpr explicit Box(T *ptr) : value_ptr{ptr}, contains{true} {}
  constexpr explicit Box() = default;
  constexpr static Box<T> empty() { return Box{}; }
  T &get() {
    if (contains) {
      return *value_ptr;
    } else {
      throw null_pointer_exception{};
    }
  }
  constexpr T &get_or_else(T &el) { return contains ? *value_ptr : el; }
};

/**
@breif:
  명시한 범위 내의 최대값 혹은 최소값을 리턴한다.

유효한 범위는 다음과 같다.
left <= start && end <= right
*/
template <class Less>
static Box<cuint> g_query(uint const tree[TREE_SIZE], uint node,       //
                          uint start, uint end, uint left, uint right, //
                          Less const &less_than) {
  // 유효하지 않은 범위
  if (right < start || end < left) {
    return Box<cuint>::empty();
  }
  // 유효한 범위
  if (left <= start && end <= right) {
    return Box<cuint>{&tree[node]};
  }
  // 두 노드에 걸쳐있는 경우
  uint mid = (start + end) / 2;
  Box<cuint> left_child =
      g_query(tree, g_left(node), start, mid, left, right, less_than);
  Box<cuint> right_child =
      g_query(tree, g_right(node), mid + 1, end, left, right, less_than);
  if (left_child.contains && right_child.contains) {
    return less_than(left_child.get(), right_child.get()) //
               ? left_child
               : right_child;
  }
  // 둘 다 유효하지 않은 경우
  if (!left_child.contains && !right_child.contains) {
    return Box<cuint>::empty();
  }
  // 적어도 하나라도 값이 유효하지 않은 경우
  return left_child.contains ? left_child : right_child;
}

inline void init(uint const data[N], uint n) {
  g_init(data, g_mintree, 1, 0, n - 1, &g_less);
  g_init(data, g_maxtree, 1, 0, n - 1, &g_greater);
}

inline void set(uint idx, uint value, uint n) {
  g_set(g_mintree, 1, 0, n - 1, idx, value, &g_less);
  g_set(g_maxtree, 1, 0, n - 1, idx, value, &g_greater);
}

inline uint max_between(uint left_inclusive, uint right_exclusive, uint n) {
  return g_query(g_maxtree, 1, 0, n - 1, //
                 left_inclusive, right_exclusive - 1, &g_greater)
      .get();
}

inline uint min_between(uint left_inclusive, uint right_exclusive, uint n) {
  return g_query(g_mintree, 1, 0, n - 1, //
                 left_inclusive, right_exclusive - 1, &g_less)
      .get();
}

#endif