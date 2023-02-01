#ifndef SOLUTION
#define SOLUTION

#include <algorithm>
#include <array>
#include <cstdint>
#include <exception>
#include <iterator>
#include <queue>
#include <set>
#include <vector>
using std::array;
using std::set;
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

#endif