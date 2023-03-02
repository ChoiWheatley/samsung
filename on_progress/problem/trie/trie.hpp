#ifndef TRIE
#define TRIE

#include <array>
#include <cstddef>
#include <memory>
#include <string>
using std::array;
using std::make_unique;
using std::string;
using std::unique_ptr;
using u8 = unsigned char;

template <char FromRange = 'a', char ToRange = 'z'> class Trie {

  static_assert(FromRange < ToRange, "FromRange must be smaller than ToRange");
  constexpr static char OFFSET = FromRange;
  constexpr static char RANGE_SIZE = ToRange - FromRange + 1;
  constexpr static u8 idxof(char real_c) { return real_c - OFFSET; }

  class Node;

  using NodePtr = unique_ptr<Node>;

  class Node {

    array<NodePtr, RANGE_SIZE> m_children;
    u8 m_size = 0;
    bool m_end_of_word = false;

  public:
    constexpr explicit Node() = default;
    Node *child_at(char idx) { return m_children[idx].get(); }
    Node const *child_at_const(char idx) const { return m_children[idx].get(); }
    bool add_child(char idx) {
      if (m_children[idx]) {
        return false;
      }
      m_children[idx] = make_unique<Node>();
      m_size++;
      return true;
    }
    bool del_child(char idx) {
      if (m_size == 0 || !m_children[idx]) {
        return false;
      }
      m_children[idx].reset();
      m_size--;
      return true;
    }
    bool empty() const { return m_size == 0; }
    bool get_end_of_word() const { return m_end_of_word; }
    bool &end_of_word() { return m_end_of_word; }
  };

  Node root;

  /**
  @return: 참인 경우 현재 노드까지 재귀적으로 제거한다.
  */
  bool delete_recursively(Node *cur, string const &word, char idx) {

    if (idx == word.size()) {

      if (!cur->get_end_of_word()) {
        return false;
      }
      cur->end_of_word() = false;
      // if there are no other children, then plz kill this node
      return cur->empty();
    }

    char ch = word[idx];
    Node *node = cur->child_at(idxof(ch));
    if (!node) {
      return false;
    }

    bool should_delete_current_node = delete_recursively(node, word, idx + 1);
    if (should_delete_current_node) {

      cur->del_child(idxof(ch));
      // if there are no other children, then plz kill this node
      return cur->empty();
    }
    return false;
  }

public:
  explicit Trie() = default;

  auto insert(string const &word) -> bool {

    Node *cur = &root;
    for (char const &c : word) {

      if (!cur->child_at(idxof(c))) {
        cur->add_child(idxof(c));
      }
      cur = cur->child_at(idxof(c));
    }
    if (cur->end_of_word()) { // already exists
      return false;
    }
    cur->end_of_word() = true;
    return true;
  }

  auto search(string const &word) const -> bool {

    Node const *cur = &root;
    for (char const &c : word) {

      auto idx = idxof(c);
      if (!cur->child_at_const(idx)) {
        return false;
      }
      cur = cur->child_at_const(idx);
    }
    return cur->get_end_of_word();
  }

  void del(string const &word) { delete_recursively(&root, word, 0); }
};

#endif