#ifndef HEAP
#define HEAP

#include <array>
#include <cstddef>
#include <exception>
#include <stdexcept>
#include <string>
using std::array;

template <class T, typename Less = std::less<T>> class Heap {

  static constexpr size_t parent(size_t idx) { return idx >> 1; }
  static constexpr size_t left(size_t idx) { return idx << 1; }
  static constexpr size_t right(size_t idx) { return (idx << 1) | 1; }

public:
  static constexpr size_t N = 101;
  static constexpr size_t START = 1;

  explicit Heap() = default;

  auto insert(T &&data) {
    if (m_top >= N - 1) {
      throw std::out_of_range{"heap is full(" + std::to_string(N) + " size)"};
    }
    // push to top
    m_top++;
    m_data.at(m_top) = std::move(data);

    // bubble up
    for (size_t idx = m_top; //
         parent(idx) > 0 &&  //
         m_less_than(m_data[parent(idx)], m_data[idx]);) {
      std::swap(m_data[parent(idx)], m_data[idx]);
      idx = parent(idx);
    }
  }

  auto peek() const {
    if (empty()) {
      throw std::out_of_range{"heap is empty"};
    }
    return m_data[START];
  }

  void pop() noexcept {

    if (empty())
      return;

    // push last element
    m_data[START] = std::move(m_data[m_top]);
    m_data[m_top] = T{};
    m_top--;

    for (size_t idx = 1; left(idx) <= m_top;) {
      size_t next_idx = 0;

      // find next index
      if (left(idx) == m_top) {
        next_idx = left(idx);
      } else {
        auto const &left_one = m_data[left(idx)];
        auto const &right_one = m_data[right(idx)];
        if (m_less_than(left_one, right_one)) {
          next_idx = right(idx);
        } else {
          next_idx = left(idx);
        }
      }

      // bubble down
      if (m_less_than(m_data[idx], m_data[next_idx])) {
        std::swap(m_data[idx], m_data[next_idx]);
      } else {
        break;
      }

      idx = next_idx;
    }
  }

  bool empty() const noexcept { return m_top == 0; }
  size_t size() const noexcept { return m_top; }

private:
  Less m_less_than{};
  /** 1부터 세는 거임 */
  array<T, N> m_data;
  size_t m_top = 0;
};

#endif