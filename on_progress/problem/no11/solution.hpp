#ifndef SOLUTION
#define SOLUTION

#include <algorithm>
#include <cstddef>
#include <vector>

using std::size_t;
using std::vector;
using mykey_t = size_t;

constexpr size_t MAX_VERTICES = 10000;

struct Node {
  const mykey_t key;
  vector<Node *> children{};
  Node *parent = nullptr;

  explicit Node(mykey_t key) : key{key} {}

  auto is_root() const -> bool { return parent == nullptr; }
  auto is_leaf() const -> bool {
    return std::all_of(children.begin(), children.end(),
                       [](Node const *child) { return child == nullptr; });
  }
  auto get_size() const -> size_t {
    size_t cnt = 1;
    for (Node const *child : children) {
      if (child != nullptr) {
        cnt += child->get_size(); // composite pattern
      }
    }
    return cnt;
  }
  auto get_parents() const -> vector<Node const *> {
    vector<Node const *> ret{};
    Node const *cur = this;
    while (cur != nullptr) {
      ret.push_back(cur);
      cur = cur->parent;
    }
    return ret;
  }
  auto operator==(const Node &o) const -> bool { return this->key == o.key; }
};

class BinTree {
public:
  explicit BinTree() = default;
  explicit BinTree(size_t vertices) : m_cache(vertices + 1, nullptr){};

  auto set_child(mykey_t parent, mykey_t child) -> void {
    Node *parent_ptr = get(parent);
    Node *child_ptr = get(child);
    child_ptr->parent = parent_ptr;
    parent_ptr->children.push_back(child_ptr);
  }

  auto operator[](mykey_t idx) -> Node const * { return get(idx); }

  auto common_ancestor(mykey_t k1, mykey_t k2) -> Node const * {
    auto const vec1 = get(k1)->get_parents();
    auto const vec2 = get(k2)->get_parents();
    for (Node const *i : vec1) {
      for (Node const *j : vec2) {
        if ((*i) == (*j)) {
          return i;
        }
      }
    }
    return nullptr;
  }

private:
  vector<Node *> m_cache{MAX_VERTICES + 1, nullptr};

  auto get(mykey_t idx) -> Node * {
    if (idx >= m_cache.size()) {
      m_cache.reserve(idx + 1); // preallocate enough memory
    }
    if (m_cache.at(idx) == nullptr) {
      m_cache.at(idx) = new Node(idx);
    }
    return m_cache.at(idx);
  }
};

#endif