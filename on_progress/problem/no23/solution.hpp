#ifndef SOLUTION
#define SOLUTION

#include <array>
#include <cstddef>
using std::array;

enum class State { Ok, Err };

template <typename T> struct Result {
  T retval;
  State state;
};

template <typename T, class LessEq> class Heap {
public:
  constexpr static size_t MAX_N = 100'001;
  constexpr static size_t START = 1;
  constexpr static size_t parent(size_t idx) { return idx >> 1; }
  constexpr static size_t left(size_t idx) { return idx << 1; }
  constexpr static size_t right(size_t idx) { return (idx << 1) | 1; }

  explicit Heap() = default;

  auto insert(T item) noexcept -> bool {
    if (m_size >= MAX_N - 1) {
      return false;
    }

    m_size++;
    m_data[m_size] = item;

    // bubble up
    for (size_t idx = m_size;                                            //
         parent(idx) > 0 && m_less_eq(m_data[parent(idx)], m_data[idx]); //
         idx = parent(idx)) {
      std::swap(m_data[parent(idx)], m_data[idx]);
    }

    return true;
  }

  auto pop() noexcept -> bool {
    if (empty()) {
      return false;
    }

    m_data[START] = m_data[m_size];
    m_data[m_size] = T{};
    m_size--;

    for (size_t idx = START; left(idx) <= m_size;) {
      size_t child_idx = left(idx);

      if (left(idx) < m_size && // l,r 모두 확인해야함.
          m_less_eq(m_data[left(idx)], m_data[right(idx)])) {
        child_idx = right(idx);
      }

      // parent, child 확인해야함.
      if (m_less_eq(m_data[idx], m_data[child_idx])) {
        std::swap(m_data[idx], m_data[child_idx]);
      } else {
        break;
      }

      idx = child_idx;
    }

    return true;
  }

  auto peek() const noexcept -> Result<T> {
    if (empty()) {
      return Result<T>{T(), State::Err};
    }
    return Result<T>{m_data[START], State::Ok};
  }

  auto empty() const noexcept -> bool { return m_size == 0; }

private:
  array<T, MAX_N> m_data;
  size_t m_size = 0;
  LessEq m_less_eq{};
};

#endif