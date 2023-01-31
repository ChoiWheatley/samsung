#ifndef SOLUTION
#define SOLUTION

constexpr static int MAX_SIZE = 10;
namespace idx2d {
struct idx2d_t {
  int y;
  int x;
  constexpr idx2d_t(int y, int x) : y{y}, x{x} {}
  constexpr idx2d_t() : y{0}, x{0} {}
};
enum class Dir { E, W, S, N };
constexpr auto direction(Dir d) -> idx2d_t {
  switch (d) {
  case Dir::E:
    return idx2d_t{0, 1};
  case Dir::W:
    return idx2d_t{0, -1};
  case Dir::S:
    return idx2d_t{1, 0};
  case Dir::N:
    return idx2d_t{-1, 0};
  }
}
constexpr auto operator+(idx2d_t const &a, idx2d_t const &b) -> idx2d_t {
  return idx2d_t{a.y + b.y, a.x + b.x};
}
constexpr auto operator+(idx2d_t const &a, Dir d) -> idx2d_t {
  return a + direction(d);
}
constexpr auto operator==(idx2d_t const &a, idx2d_t const &b) {
  return a.y == b.y && a.x == b.x;
}
constexpr Dir directions[] = {Dir::E, Dir::W, Dir::S, Dir::N};
} // namespace idx2d

using namespace idx2d;

struct idx_dist {
  idx2d_t idx{};
  int dist = 0;
  constexpr idx_dist() {}
  constexpr idx_dist(idx2d_t idx, int dist = 0) : idx{idx}, dist{dist} {}
};

static int g_map[MAX_SIZE][MAX_SIZE];
static int g_map_size = 0;

template <class T> class queue_t {
public:
  constexpr static int CAPACITY = MAX_SIZE * MAX_SIZE;
  bool empty() const { return start == end; }
  bool full() const { return ((end + 1) % CAPACITY) == start; }
  bool offer(T elem) {
    if (full())
      return false;
    m_queue[end] = elem;
    end = next_idx(end);
    return true;
  }
  T peek() const { return m_queue[start]; }
  bool pop() {
    if (empty())
      return false;
    m_queue[start] = T{};
    start = next_idx(start);
    return true;
  }

private:
  int next_idx(int idx) { return (idx + 1) % CAPACITY; }
  T m_queue[CAPACITY];
  int start;
  int end;
};

void bfs_init(int map_size, int map[10][10]) {
  g_map_size = map_size;
  for (int i = 0; i < MAX_SIZE; ++i) {
    for (int j = 0; j < MAX_SIZE; ++j) {
      g_map[i][j] = map[i][j];
    }
  }
}

int bfs(int x1, int y1, int x2, int y2) {
  auto start = idx2d_t{y1 - 1, x1 - 1};
  auto end = idx2d_t{y2 - 1, x2 - 1};
  auto queue = queue_t<idx_dist>{};
  queue.offer(idx_dist{start});
  bool visited[MAX_SIZE][MAX_SIZE] = {{false}};
  visited[start.y][start.x] = true;
  while (!queue.empty()) {

    auto elem = queue.peek();
    queue.pop();
    if (elem.idx == end) {
      return elem.dist;
    }
    // iterate directions and offer next element
    for (int i = 0; i < 4; ++i) {

      auto delta = directions[i];
      auto next = elem.idx + delta;
      if (0 <= next.y && next.y < g_map_size && //
          0 <= next.x && next.x < g_map_size && //
          !visited[next.y][next.x] && g_map[next.y][next.x] == 0) {
        visited[next.y][next.x] = true;
        queue.offer(idx_dist{next, elem.dist + 1});
      }
    }
  }
  return -1;
}

#endif
