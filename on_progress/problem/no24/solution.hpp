#ifndef SOLUTION
#define SOLUTION

#include <array>
#include <initializer_list>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
constexpr int MAX_N = 100;
constexpr int MAX_INT = 99999999;

template <typename T, size_t Size = MAX_N> using Arr = std::array<T, Size>;
using std::queue;

struct idx_t {
  int r;
  int c;
  constexpr explicit idx_t(int r, int c) : r{r}, c{c} {}
};
constexpr auto operator+(idx_t const &lhs, idx_t const &rhs) {
  return idx_t{lhs.r + rhs.r, lhs.c + rhs.c};
}
std::string to_string(idx_t const &idx) {
  std::stringstream stream;
  stream << "(" << idx.r << "," << idx.c << ")";
  return stream.str();
}

static int N = 0;
/**visited를 대신하는 전역변수. [i][j]보다 작은 경우 pq에 넣는다.*/
static Arr<Arr<int>> g_costs{{{MAX_INT}}};
/**말 그대로 input데이터*/
static Arr<Arr<int>> g_data;
constexpr auto four_ways = {
    idx_t(-1, 0), // up
    idx_t(0, 1),  // right
    idx_t(1, 0),  // down
    idx_t(0, -1), // left
};
constexpr bool out_of_bounds(idx_t idx, int n) {
  return idx.r < 0 || n <= idx.r || idx.c < 0 || n <= idx.c;
}

static void init(int n, decltype(g_data) &&arr2d) {
  N = n;
  for (int i = 0; i < N; ++i) {
    g_costs[i].fill(MAX_INT);
  }
  g_costs[0][0] = 0;
  g_data = std::move(arr2d);
}

template <typename T> T &get(Arr<Arr<T>> &arr, idx_t index) {
  return arr[index.r][index.c];
}

inline int solution(int n, decltype(g_data) &&arr2d) {
  init(n, std::move(arr2d));
  auto q = queue<idx_t>();

  q.push(idx_t{0, 0});

  while (!q.empty()) {

    idx_t cur = q.front();
    q.pop();
    for (idx_t delta : four_ways) {
      if (out_of_bounds(delta + cur, n)) {
        continue;
      }
      auto next = delta + cur;
      int next_cost = get(g_costs, cur) + get(g_data, next);
      // not visited OR 더 적은 비용으로 갈 수 있는 경우
      if (get(g_costs, next) > next_cost) {
        get(g_costs, next) = next_cost;
        q.push(next);
      }
    }
  }

  return g_costs[n - 1][n - 1];
}

#endif