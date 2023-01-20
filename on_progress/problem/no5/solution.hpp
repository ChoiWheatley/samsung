#ifndef SOL
#define SOL

#include <cinttypes>

using data_t = uint32_t;
using std::size_t;

namespace sol {

constexpr size_t MAX_NODE = 10000;

struct Node {
  data_t data;
  Node *next;
};

static Node node_pool[MAX_NODE];

static size_t node_top = 0;

static Node *get_node(data_t data) {
  Node *ret = node_pool + node_top;
  ret->data = data;
  node_top += 1;
  return ret;
}

class MyContainer {
public:
  /** x번 인덱스 **앞에** data를 추가하고 한 칸씩 뒤로 이동한다. */
  void insert_at(size_t x, data_t data) {
    auto cur = begin();
    auto prev = m_head;
    size_t cnt = 0;
    for (; cnt < x && cur != end(); cur = cur->next) {
      prev = cur;
      cnt++;
    }
    if (cnt == x) {
      prev->next = get_node(data);
      prev->next->next = cur;
    }
  }

  /** x번 인덱스 자리를 지우고 한 칸씩 앞으로 이동한다. */
  void delete_at(size_t x) {
    auto cur = begin();
    auto prev = m_head;
    size_t cnt = 0;
    for (; cnt < x && cur != end(); cur = cur->next) {
      prev = cur;
      cnt++;
    }
    if (cnt == x) {
      prev->next = cur->next;
      cur->next = nullptr;
      // cur 유실
    }
  }

  /** x번 인덱스 자리를 data로 변경한다. */
  void change_at(size_t x, data_t data) {
    auto cur = begin();
    size_t cnt = 0;
    for (; cnt < x && cur != end(); cur = cur->next) {
      cnt++;
    }
    if (cnt == x) {
      cur->data = data;
    }
  }

  /** 리스트 맨 뒤에 data를 추가한다. */
  void add(data_t data) {
    Node *newbie = get_node(data);
    newbie->next = end();
    m_last->next = newbie;
    m_last = newbie;
  }

  size_t size() {
    auto cur = begin();
    size_t cnt = 0;
    while (cur != end()) {
      cur = cur->next;
      cnt++;
    }
    return cnt;
  }

  Node *begin() { return m_head->next; }
  Node *end() { return m_end; }

  MyContainer() { m_head->next = m_last->next = m_end; }

private:
  Node *m_head = get_node(0);
  Node *m_end = get_node(999); // 이번엔 end를 단순 nullptr로 두지 말아볼까?
  Node *m_last = m_head; // m_last는 next가 m_end임.
};

} // namespace sol

#endif