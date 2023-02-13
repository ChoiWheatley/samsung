#ifndef SOLUTION
#define SOLUTION

/**
maloc.h 를 제외한 헤더파일 임포트 금지
 - 문제: 수입이 가장 큰 user 10명의 uID를 수입에 대하여 내림차순으로 구하세용
    - 오직 10명만 보면 된다 => HEAP으로 접근
    - 수입이 동일하면 uID가 작은 유저의 우선순위가 높다.
*/

/**최대 10만명이므로 .text 영역에 메모리 할당이 거의 필수.*/
constexpr int START = 1;
constexpr int MAX_USER = 100'000 + START; // 1부터 셀거임

constexpr int parent(int idx) { return idx >> 1; }
constexpr int left(int idx) { return idx << 1; }
constexpr int right(int idx) { return (idx << 1) | 1; }

struct User {
  int uID;
  int income;
};
static auto operator<(User const &lhs, User const &rhs) {
  if (lhs.income == rhs.income) {
    // 수입이 동일하면 uID가 작은 유저의 우선순위가 높다.
    return lhs.uID > rhs.uID;
  }
  return lhs.income < rhs.income;
}
static void swap(User &a, User &b) noexcept {
  User tmp = a;
  a = b;
  b = tmp;
}

static User g_maxheap[MAX_USER];
static int g_size = 0;

inline static bool empty() { return g_size == 0; }

void init() { g_size = 0; }

void addUser(int uID, int income) {
  g_size++;
  g_maxheap[g_size].uID = uID;
  g_maxheap[g_size].income = income;

  // bubble up
  for (int idx = g_size;                                           //
       parent(idx) > 0 && g_maxheap[parent(idx)] < g_maxheap[idx]; //
       idx = parent(idx)) {
    swap(g_maxheap[parent(idx)], g_maxheap[idx]);
  }
}

User const &peek() noexcept { return g_maxheap[START]; }

inline void pop() {
  if (empty()) {
    return;
  }
  swap(g_maxheap[START], g_maxheap[g_size]);
  g_size--;

  // bubble down
  for (int idx = START; left(idx) <= g_size;) {
    // 1. left == size => left
    // 2. right >= size => max_idx(arr[left], arr[right])
    int child_idx = left(idx);

    // left VS right
    if (left(idx) < g_size && g_maxheap[left(idx)] < g_maxheap[right(idx)]) {
      child_idx = right(idx);
    }

    // parent VS child
    if (g_maxheap[idx] < g_maxheap[child_idx]) {
      swap(g_maxheap[child_idx], g_maxheap[idx]);
    } else {
      break;
    }

    idx = child_idx;
  }
}

int getTop10(int result[10]) {
  int size = 10 < g_size ? 10 : g_size;

  User cache[10];

  for (int i = 0; i < size; ++i) {
    cache[i] = peek();
    result[i] = cache[i].uID;
    pop();
  }

  for (int i = 0; i < size; ++i) {
    addUser(cache[i].uID, cache[i].income);
  }

  return size;
}

#endif