#ifndef SOLUTION
#define SOLUTION

#include <array>
#include <cstddef>
#include <string>
using std::array;
using std::size_t;
using std::string;

constexpr size_t MAX_N = 100'000;

inline size_t djb2(string const &key) {
  size_t hash = 5381;
  for (auto const &c : key) {
    hash = ((hash << 5) + hash) + c; // hash * 33 + c
  }
  return hash;
}

struct MyHasher {
  size_t operator()(string const &key) const { return djb2(key); }
};

template <typename T> struct Bucket {
  T key{};
  Bucket *next = nullptr;
  constexpr explicit Bucket(T const &key) : key{key} {};
  constexpr Bucket() = default;
};

template <class Key, class Hash> class MySet {
  using key_t = Key;
  using node_t = Bucket<key_t>;
  using hasher_t = Hash;

public:
  static constexpr size_t TABLE_SIZE = 1 << 15;
  static constexpr size_t MASK = TABLE_SIZE - 1;

  explicit MySet() = default;

  /**key 중복시 원소의 값을 수정한다. 없으면 맨 뒤에 추가함.*/
  void insert(key_t const &key) {
    node_t *prev = find_prev_node(key);
    if (prev->next == nullptr) { // no elem found
      prev->next = new node_t(key);
      _size += 1;
    }
  }

  /**key에 해당하는 원소를 찾아 제거한다. 만약 원소가 없다면 아무일도 일어나지
   * 않는다.*/
  void remove(key_t const &key) {
    node_t *prev = find_prev_node(key);
    if (prev->next == nullptr) { // no elem found
      return;
    }
    node_t *byebye = prev->next;
    prev->next = prev->next->next;
    delete byebye;
    _size -= 1;
  }

  /**key 원소가 컨테이너 안에 존재하는지 여부를 리턴한다.*/
  bool contains(key_t const &key) {
    return find_prev_node(key)->next != nullptr;
  }

  /**현재 컨테이너의 원소 수를 리턴한다.*/
  size_t size() const { return _size; }

private:
  /**heads*/
  array<node_t, TABLE_SIZE> _tbl;

  size_t _size = 0;

  hasher_t _hasher{};

  /**key 원소의 바로 전 노드를 리턴하거나, 버킷의 가장 마지막 노드를 리턴한다.*/
  node_t *find_prev_node(key_t const &key) {

    node_t *cur = &_tbl[_hasher(key) & MASK];

    while (cur->next != nullptr && cur->next->key != key) {
      cur = cur->next;
    }
    return cur;
  }
};

#endif