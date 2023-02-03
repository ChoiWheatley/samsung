#ifndef SOLUTION
#define SOLUTION

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <iterator>
#include <numeric>
#include <queue>
#include <set>
#include <sys/types.h>
#include <tuple>
#include <utility>
#include <vector>
using std::array;
using std::uint32_t;
using std::vector;

namespace node {

using idx_t = uint32_t;
constexpr size_t MAX_NODE = 100'000;

struct node_t {
  idx_t id = 0;
  int depth;
  node_t const *parent = nullptr;
  vector<node_t const *> children;

  node_t(idx_t id = 0, node_t const *parent = nullptr)
      : id{id}, depth{parent == nullptr ? 0 : parent->depth + 1}, //
        parent{parent} {}

  auto is_root() const { return parent == nullptr; }
  auto is_leaf() const { return children.empty(); }
  auto add_child(node_t const *child) { children.emplace_back(child); }
};

inline bool is_ancester(node_t const &ancester, node_t const &child) {
  if (child.depth <= ancester.depth) {
    return false;
  }
  auto *cur = child.parent;
  while (cur != nullptr) {
    if (cur == &ancester) {
      return true;
    }
    cur = cur->parent;
  }
  return false;
}

inline auto ancester(node_t const &n) -> vector<node_t const *> {
  auto ret = vector<node_t const *>{};
  auto *cur = n.parent;
  while (cur != nullptr) {
    ret.push_back(cur);
    cur = cur->parent;
  }
  return ret;
}

struct no_common_anceseter : std::exception {
  const char *what() const noexcept override {
    return "no common ancester has found";
  }
};

inline auto nearest_common_ancester(node_t const *n1, node_t const *n2)
    -> node_t const & {
  auto ancester1 = ancester(*n1);
  auto ancester2 = ancester(*n2);
  auto const size1 = ancester1.size();
  auto const size2 = ancester2.size();
  auto len = std::min(size1, size2);
  auto ret = ancester1[size1 - 1];
  for (size_t i = 1; i <= len; ++i) {
    if (ancester1[size1 - i]->id != ancester2[size2 - i]->id) {
      return *ancester1[size1 - (i - 1)];
    }
    ret = ancester1[size1 - i];
  }
  return *ret;
}

inline auto dist(node_t const &n1, node_t const &n2) {
  if (is_ancester(n1, n2)) {
    return n2.depth - n1.depth;
  } else if (is_ancester(n2, n1)) {
    return n1.depth - n2.depth;
  }
  auto const &nca = nearest_common_ancester(&n1, &n2);
  return (n1.depth - nca.depth) + (n2.depth - nca.depth);
}

} // namespace node

static array<node::node_t, node::MAX_NODE> mem_pool;
static auto new_node(node::idx_t id, node::node_t *parent) {

  node::node_t *ret = &mem_pool[id];
  ret->id = id;
  ret->parent = parent;
  ret->depth = parent->depth + 1;
  parent->add_child(ret);

  return ret;
}

namespace sol1 {

template <class Consumer>
inline void do_bfs(node::node_t const *root,
                   Consumer const &do_something_with) {
  auto q = std::queue<node::node_t const *>{};
  auto const *cur = root;

  q.push(cur);

  while (!q.empty()) {

    cur = q.front();
    q.pop();
    do_something_with(cur);

    for (auto const *c : cur->children) {
      q.push(c);
    }
  }
}

/**
@param:
- data: 루트노드가 1번부터 시작, i-1번째 인덱스의 값은 i번 노드의 부모이다.
@return:
- BFS 순서에 따라 직접 순회할 때 지나게 되는 총 간선 수를 리턴한다.
 */
inline auto solution(vector<node::idx_t> const &data) -> size_t {
  for (size_t i = 0; i < node::MAX_NODE; ++i) {
    mem_pool[i].children.clear();
    mem_pool[i].parent = nullptr;
    mem_pool[i].depth = 0;
  }
  for (node::idx_t i = 0; i < data.size(); ++i) {
    auto e = data[i];
    auto parent_idx = e - 1;
    new_node(i + 1, &mem_pool[parent_idx]);
  }

  size_t cnt = 0;

  node::node_t const *prev = nullptr;
  do_bfs(&mem_pool[0], [&prev, &cnt](node::node_t const *child) {
    if (prev) {
      cnt += node::dist(*prev, *child);
    }
    prev = child;
  });
  return cnt;
}
} // namespace sol1
namespace sol2 {

inline auto solution(vector<node::idx_t> const &data) -> size_t {
  for (size_t i = 0; i < node::MAX_NODE; ++i) {
    mem_pool[i].children.clear();
    mem_pool[i].parent = nullptr;
    mem_pool[i].depth = 0;
  }
  for (node::idx_t i = 0; i < data.size(); ++i) {
    auto e = data[i];
    auto parent_idx = e - 1;
    new_node(i + 1, &mem_pool[parent_idx]);
  }

  size_t cnt = 0;

  // bfs
  auto q = std::queue<node::node_t const *>{};
  auto const *cur = &mem_pool[0];
  auto const *prev = cur;

  q.push(cur);

  while (!q.empty()) {

    cur = q.front();
    q.pop();
    if (cur->parent == nullptr)
      ;
    else if (cur->parent == prev) {
      // 아직 subtree 단위로 이동하는게 아님
      cnt += 1;
    } else if (cur->parent == prev->parent) {
      // 아직 subtree 단위로 이동하는게 아님
      cnt += 2;
    } else {
      // 다른 subtree로 이동
      cnt += node::dist(*cur, *prev);
    }

    for (auto const *c : cur->children) {
      q.push(c);
    }
    prev = cur;
  }

  return cnt;
}

} // namespace sol2

/**
https://www.youtube.com/watch?v=dOAxrhAUIhA
Binary Lifting 기법을 활용하여 O(logN) 안에 빠르게 k-th ancester of n 을 찾아낼
수 있다. 파라메트릭 서치를 활용해 lca(lowest common ancester)를 찾을 수 있다.
*/
namespace sol3 {

using node::idx_t;
using node::MAX_NODE;
constexpr size_t LOG = 20; // log2(100'000)의 근사
/** 전처리에만 사용되는 임시벡터. 각 버텍스와 연결된 인접 노드의 개수를
 * 저장한다. */
static array<idx_t, MAX_NODE> g_outdegree;
/** 전처리에 초기화되는 벡터. i번째 버텍스는 vector[ prefix[i] : prefix[i+1] ]
 * 와 연결되어있다. */
static array<idx_t, MAX_NODE + 1> g_prefix;
/** 2d 리스트를 일렬로 길게 연결한 모양. 정점마다의 위치는 prefix가 기억한다 */
static vector<idx_t> g_vertices;
/** up[v][j] = 2^j-th ancester of v*/
static array<array<idx_t, LOG>, MAX_NODE> g_up;
static array<size_t, MAX_NODE> g_depth;

static auto get_children_idx(idx_t id)
    -> std::pair<size_t /*begin*/, size_t /*end*/> {
  return std::make_pair(g_prefix.at(id), g_prefix.at(id + 1));
}

/** 넣은 순서대로 출력하기 위해선 순서를 end부터 읽어야 한다. */
template <class Consumer>
static auto foreach_children(idx_t id, Consumer const &consumer) {
  size_t begin;
  size_t end;
  std::tie(begin, end) = get_children_idx(id);
  while (begin != end) {
    consumer(g_vertices[end - 1]);
    end -= 1;
  }
}

static auto edge_of(vector<idx_t> const &edges, idx_t i) {
  return std::make_pair(edges.at(i), i + 1);
}

static auto init_vertices(vector<idx_t> const &edges) {
  g_prefix.fill(0);
  g_outdegree.fill(0);

  g_vertices = vector<idx_t>(edges.size());
  for (auto const &e : edges) {
    g_outdegree[e] += 1; // 부모 e에 연결된 인접노드 하나 추가
  }
  std::partial_sum(g_outdegree.begin(), g_outdegree.end(),
                   g_prefix.begin() + 1);

  for (idx_t idx = 0; idx < edges.size(); ++idx) {
    idx_t e1;
    idx_t e2;
    std::tie(e1, e2) = edge_of(edges, idx);
    // add child
    size_t vertex_idx = g_prefix.at(e1) + (--g_outdegree.at(e1));
    g_vertices.at(vertex_idx) = e2;
  }
}

/** preprocessing of Binary Lifting */
static auto init_up(vector<idx_t> const &edges) {

  g_up.fill({0});

  for (idx_t idx = 0; idx < edges.size(); ++idx) {
    idx_t e1;
    idx_t e2;
    std::tie(e1, e2) = edge_of(edges, idx);

    g_up[e2][0] = e1;
    g_depth[e2] = g_depth[e1] + 1;

    for (size_t j = 1; j < LOG; ++j) {
      /**나의 2^j 번째 조상은 나의 2^{j-1}번째 조상의 2^{j-1}번째 조상과 같다.
      참고로 루트 이후의 조상은 전부 루트로 향한다. 0이 루트거든.*/
      g_up[e2][j] = g_up[g_up[e2][j - 1]][j - 1];
    }
  }
}

template <class Consumer>
static void do_bfs(Consumer const &do_something_with) {
  auto q = std::queue<idx_t>{};
  q.push(0); // root

  while (!q.empty()) {

    auto cur = q.front();
    q.pop();
    do_something_with(cur);

    foreach_children(cur, [&q](idx_t id) { q.push(id); });
  }
}

static idx_t parent(idx_t node) { return g_up[node][0]; }

static idx_t find_lca(idx_t i1, idx_t i2) {

  if (g_depth[i1] < g_depth[i2]) {
    std::swap(i1, i2);
  }
  /** depth를 일치시켜주기 위한 작업
  k가 2의 제곱수가 아니더라도 몇 번 나눠서 가면 된다.*/
  auto const k = g_depth[i1] - g_depth[i2];
  for (int exp = LOG - 1; exp >= 0; --exp) {
    if (k & (1 << exp)) {
      i1 = g_up[i1][exp];
    }
  }
  if (i1 == i2)
    return i1;

  /** 파라메트릭 서치를 통해 lca 바로 아래의 노드까지 이동. */
  for (int exp = LOG - 1; exp >= 0; --exp) {
    if (g_up[i1][exp] != g_up[i2][exp]) {
      i1 = g_up[i1][exp];
      i2 = g_up[i2][exp];
    }
  }
  return parent(i1);
}

static size_t distance(idx_t i1, idx_t i2) {
  if (g_depth[i1] < g_depth[i2]) {
    std::swap(i1, i2);
  }
  /** subtree 간 전환이 이루어지지 않는 경우 */
  if (parent(i1) == i2) {
    return 1;
  } else if (parent(i1) == parent(i2)) {
    return 2;
  }

  /** subtree 간 전환이 이루어지는 경우: LCA를 찾아 두 depth 차이를 더한다. */
  idx_t const lca = find_lca(i1, i2);
  return (g_depth[i1] - g_depth[lca]) + (g_depth[i2] - g_depth[lca]);
}

/**
i-1 번째 인덱스 (1 <= i < MAX_NODE)의 값은 i의 부모의 인덱스를 가리킨다.
루트노드는 부모가 없으므로 생략되었다.
*/
inline auto adapted_solution(vector<idx_t> const &edges) -> size_t {
  init_vertices(edges);
  init_up(edges);
  idx_t prev = 0;
  size_t distance = 0;
  do_bfs([&prev, &distance](idx_t id) {
    if (prev != id) {
      distance += sol3::distance(prev, id);
    }
    prev = id;
  });
  return distance;
}

/**
문제 입력조건을 나에게 맞는 방식으로 변경
- 1부터 시작하는 인덱싱을 0부터 시작하는 것으로 변경.
*/
inline auto solution(vector<node::idx_t> &data) -> size_t {

  std::transform(data.begin(), data.end(), data.begin(),
                 [](auto e) { return e - 1; });
  return adapted_solution(data);
}
} // namespace sol3

#endif