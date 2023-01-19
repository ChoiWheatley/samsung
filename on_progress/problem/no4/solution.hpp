#ifndef SOL
#define SOL

#include <cinttypes>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;
using std::size_t;
using code_t = std::uint32_t;

namespace sol1 {

struct Node {
  const code_t data;
  shared_ptr<Node> next;
  explicit Node(code_t data) : data{data} {}
};

class CodeContainer {
public:
  /** x의 위치 바로 다음부터 s를 삽입한다. 이때 x는 1부터 센다. */
  CodeContainer &insert_all(size_t x, CodeContainer &&s) {
    auto cur = m_head;
    size_t cnt = 0;
    while (cnt < x && cur->next != end()) {
      cur = cur->next;
      cnt++;
    }
    // x 까지 도달하였던, last까지 도달하였던 s 삽입.
    shared_ptr<Node> right = cur->next;
    cur->next = s.begin();
    if (right->next == nullptr) {
      m_last = s.m_last;
    } else {
      s.m_last->next = right;
    }
    return *this;
  }

  /** x 위치 바로 다음부터 y개의 숫자를 삭제한다. */
  CodeContainer &del(size_t x, size_t y) {
    shared_ptr<Node> cur_x = m_head;
    size_t cnt_x = 0;
    while (cnt_x < x && cur_x->next != end()) {
      cur_x = cur_x->next;
      cnt_x++;
    }
    if (cnt_x == x) {
      size_t cnt_y = 0;
      shared_ptr<Node> cur_y = cur_x;
      while (cnt_y < y && cur_y->next != end()) {
        cur_y = cur_y->next;
        cnt_y++;
      }
      // cur_x 위치 다음부터 cur_y 까지 삭제한다.
      // 레퍼런스를 잃은 자식들은 알아서 소멸할 거임.
      // TODO: valgrind 리소스 누수 체크
      cur_x->next = cur_y->next;
    }
    return *this;
  }

  /** 맨 뒤에 o를 붙인다. */
  CodeContainer &add_all(CodeContainer &&o) {
    m_last->next = o.m_head->next;
    m_last = o.m_last;
    return *this;
  }

  /** 맨 뒤에 data 노드를 하나 붙인다. */
  CodeContainer &add(code_t data) {
    m_last->next = make_shared<Node>(data);
    m_last = m_last->next;
    return *this;
  }

  size_t size() const {
    auto cur = begin();
    int cnt = 0;
    while (cur != end()) {
      cur = cur->next;
      cnt++;
    }
    return cnt;
  }

  auto begin() const -> shared_ptr<Node> { return m_head->next; }
  auto end() const -> shared_ptr<Node> { return m_last->next; }

private:
  shared_ptr<Node> m_head = make_shared<Node>(0);
  shared_ptr<Node> m_last = m_head;
};

} // namespace sol1

#endif