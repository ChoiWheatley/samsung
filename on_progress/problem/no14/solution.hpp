#ifndef SOLUTION
#define SOLUTION

#include <cstdint>
#include <queue>
#include <vector>
using std::int16_t;
using std::queue;
using std::vector;

namespace idx {

struct idx2d_t {
  int16_t r;
  int16_t c;
  constexpr idx2d_t(int16_t r = 0, int16_t c = 0) : r{r}, c{c} {}
};
constexpr static auto operator+(idx2d_t const &a, idx2d_t const &b) -> idx2d_t {
  int16_t r = a.r + b.r;
  int16_t c = a.c + b.c;
  return idx2d_t{r, c};
}
enum class Dir { N, NE, E, SE, S, SW, W, NW };
constexpr static auto directions8 = {Dir::N, Dir::NE, Dir::E, Dir::SE,
                                     Dir::S, Dir::SW, Dir::W, Dir::NW};
constexpr static auto directions4 = {
    Dir::N,
    Dir::E,
    Dir::S,
    Dir::W,
};
constexpr static auto direction(Dir d) {
  switch (d) {
  case Dir::N:
    return idx2d_t{-1, 0};
  case Dir::NE:
    return idx2d_t{-1, 1};
  case Dir::E:
    return idx2d_t{0, 1};
  case Dir::SE:
    return idx2d_t{1, 1};
  case Dir::S:
    return idx2d_t{1, 0};
  case Dir::SW:
    return idx2d_t{1, -1};
  case Dir::W:
    return idx2d_t{0, -1};
  case Dir::NW:
    return idx2d_t{-1, -1};
  }
}
constexpr static auto operator+(idx2d_t const &a, Dir d) -> idx2d_t {
  return a + direction(d);
}
constexpr static auto operator==(idx2d_t const &a, idx2d_t const &b) {
  return a.r == b.r && a.c == b.c;
}
static bool is_out_of_range(idx2d_t const &idx, size_t size) {
  return !(0 <= idx.r && idx.r < size && //
           0 <= idx.c && idx.c < size);
}
} // namespace idx
using namespace idx;

template <class T> class vec2d_const_ext {
public:
  auto operator[](idx2d_t idx) const { return tbl[idx.r][idx.c]; }
  explicit vec2d_const_ext(vector<vector<T>> const &tbl) : tbl{tbl} {}

  static auto wrap(vector<vector<T>> const &tbl) {
    return vec2d_const_ext{tbl};
  }

private:
  vector<vector<T>> const &tbl;
};
template <class T>
inline auto wrap(vector<vector<T>> const &tbl) -> vec2d_const_ext<T> {
  return vec2d_const_ext<T>(tbl);
}

/** pos 주위 8개의 셀에 지뢰의 개수를 리턴한다. */
inline auto count_mine(vector<vector<bool>> const &tbl, idx2d_t pos) {
  size_t cnt = 0;
  for (auto delta : directions8) {
    auto next = pos + delta;
    if (!is_out_of_range(next, tbl.size()) && wrap(tbl)[next]) {
      cnt++;
    }
  }
  return cnt;
}

inline auto is_mine(vector<vector<bool>> const &tbl, idx2d_t pos) {
  return wrap(tbl)[pos];
}

// bfs 순회 및 근처 모든 0들을 한 번에 visited로 만들어 버린다.
inline void bfs(vector<vector<bool>> const &tbl, vector<vector<bool>> &visited,
                idx2d_t start) {
  visited[start.r][start.c] = true;
  auto const n = tbl.size();
  auto q = queue<idx2d_t>{};
  q.push(start);

  while (!q.empty()) {

    auto elem = q.front();
    q.pop();
    for (auto delta : directions8) {
      auto next = elem + delta;
      if (is_out_of_range(next, n) || visited[next.r][next.c]) {
        continue;
      }
      visited[next.r][next.c] = true;
      if (!is_mine(tbl, next) && count_mine(tbl, next) == 0) {
        q.push(next);
      }
    }
  }
}

inline int solution(vector<vector<bool>> const &tbl) {

  auto const size = tbl.size();
  auto visited = vector<vector<bool>>(size, vector<bool>(size));
  int count = 0;

  // count == 0 인 좌표부터 bfs 돌리자.
  for (int16_t i = 0; i < size; ++i) {
    for (int16_t j = 0; j < size; ++j) {
      if (!is_mine(tbl, idx2d_t(i, j)) && count_mine(tbl, idx2d_t(i, j)) == 0 &&
          !visited[i][j]) {
        bfs(tbl, visited, idx2d_t(i, j));
        count++;
      }
      if (is_mine(tbl, idx2d_t(i, j))) {
        visited[i][j] = true;
      }
    }
  }
  // 그리고 나서 나머지 찌끄레기를 일일이 눌러보는 거지.
  for (int16_t i = 0; i < size; ++i) {
    for (int16_t j = 0; j < size; ++j) {
      if (visited[i][j] || is_mine(tbl, idx2d_t{i, j})) {
        continue;
      }
      visited[i][j] = true;
      count += 1;
    }
  }
  return count;
}

#endif