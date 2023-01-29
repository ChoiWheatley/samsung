#ifndef SOLUTION
#define SOLUTION

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <map>
#include <tuple>
#include <utility>
#include <vector>

using std::pair;
using std::size_t;
using std::vector;
using bitset_t = size_t;

struct idx2d_t {
  constexpr idx2d_t(int r, int c) : r{r}, c{c} {}
  int r;
  int c;
};

static auto operator+(idx2d_t const &a, idx2d_t const &b) {
  return idx2d_t{a.r + b.r, a.c + b.c};
}

static auto operator+=(idx2d_t &origin, idx2d_t const &other) {
  origin.r += other.r;
  origin.c += other.c;
}

enum class Delta { E, W, S, N };

constexpr auto deltas = {Delta::E, Delta::W, Delta::S, Delta::N};

constexpr idx2d_t delta(Delta d) {
  switch (d) {
  case Delta::E:
    return idx2d_t(0, 1);
  case Delta::W:
    return idx2d_t(0, -1);
  case Delta::S:
    return idx2d_t(1, 0);
  case Delta::N:
    return idx2d_t(-1, 0);
  }
}

using edge_t = pair<idx2d_t, idx2d_t>;

inline bool operator==(idx2d_t const &a, idx2d_t const &b) {
  return a.r == b.r && a.c == b.c;
}

/** pqr 모두 linear한 상태에서 q가 p-r 세그먼트 위에 놓여져 있는지 판단*/
inline bool on_segment(idx2d_t const &p, idx2d_t const &q, idx2d_t const &r) {
  return q.c <= std::max(p.c, r.c) && std::min(p.c, r.c) <= q.c &&
         q.r <= std::max(p.r, r.r) && std::min(p.r, r.r) <= q.r;
}

enum class Orientation { COLLINEAR, CW, CCW };

/**
  d1 = (y2-y1)/(x2-x1)
  d2 = (y3-y2)/(x3-x2)
  if d1 > d2, orientation is CW
  if d1 < d2, orientation is CCW
  if d1 == d2, orientation is Collinear
*/
inline Orientation orientation(idx2d_t const &p1, idx2d_t const &p2,
                               idx2d_t const &p3) {
  auto d1 = (p2.r - p1.r) * (p3.c - p2.c);
  auto d2 = (p3.r - p2.r) * (p2.c - p1.c);
  if (d1 > d2)
    return Orientation::CW;
  if (d1 < d2)
    return Orientation::CCW;
  else
    return Orientation::COLLINEAR;
}

/**
  1. general case : orientation(p1,q1,p2) != orientation(p1,q1,q2) and
    orientation(p2,q2,p1) != orientation(p2,q2,q1)
  2. collinear case : orientation(p1,q1,p2) == orientation(p1,q1,q2) ==
    orientation(p2,q2,p1) = orientation(p2,q2,q1) == Collinear and
    x_project(p1,q1) intersects x_project(p2,q2) and
    y_project(p1,q1) intersects y_project(p2,q2)
*/
inline bool is_intersect(edge_t const &e1, edge_t const &e2) {

  auto ori1_1 = orientation(e1.first, e1.second, e2.first);
  auto ori1_2 = orientation(e1.first, e1.second, e2.second);
  auto ori2_1 = orientation(e2.first, e2.second, e1.first);
  auto ori2_2 = orientation(e2.first, e2.second, e1.second);
  // general case
  if (ori1_1 != ori1_2 && ori2_1 != ori2_2) {
    return true;
  }
  // e1.f----e2.f-----e1.s
  if (ori1_1 == Orientation::COLLINEAR &&
      on_segment(e1.first, e2.first, e1.second)) {
    return true;
  }
  // e1.f----e2.s-----e1.s
  if (ori1_2 == Orientation::COLLINEAR &&
      on_segment(e1.first, e2.second, e1.second)) {
    return true;
  }
  // e2.f----e1.f----e2.s
  if (ori2_2 == Orientation::COLLINEAR &&
      on_segment(e2.first, e1.first, e2.second)) {
    return true;
  }
  // e2.f----e1.s----e2.s
  if (ori2_2 == Orientation::COLLINEAR &&
      on_segment(e2.first, e1.second, e2.second)) {
    return true;
  }
  return false;
}

struct diagonal_exception : std::exception {
  const char *what() const noexcept override {
    return "two points cannot be diagonal";
  }
};

/** a와 b가 직선일때 둘 사이의 거리를 리턴한다. 이때 1을 뺀다. */
inline int distance(idx2d_t const &a, idx2d_t const &b) {
  if (a.c == b.c) { // vertical
    return std::abs(a.r - b.r) - 1;
  } else if (a.r == b.r) { // horizontal
    return std::abs(a.c - b.c) - 1;
  } else {
    throw diagonal_exception();
  }
}

/** delta 방향으로 전선을 그을 수 있다면 그을 전선의 배열을 리턴한다. */
static auto try_register(vector<vector<bool>> const &registered,
                         idx2d_t const &core_index, Delta d)
    -> vector<idx2d_t> {

  const auto N = registered.size();
  idx2d_t pos = core_index + delta(d);
  while (0 <= pos.c && pos.c < N && 0 <= pos.r && pos.r < N) {
    if (registered[pos.r][pos.c]) {
      return vector<idx2d_t>{};
    }
    pos += delta(d);
  }
  // do register
  auto ret = vector<idx2d_t>();
  pos = core_index + delta(d);
  while (0 <= pos.c && pos.c < N && 0 <= pos.r && pos.r < N) {
    ret.push_back(pos);
    pos += delta(d);
  }
  return ret;
}

constexpr size_t MAX_CABLE = 99999;

struct return_t {
  size_t max_core;
  size_t min_cable;
};

/**
# 전선 긋기 작업
  - 동서남북 방향으로 전선 설치가 가능한지 test 수행
  - 가능하다면 그 방향으로 전선설치 (register)
  - idx 하나 올려서 재귀
  - 설치했던 전선을 철회하고 다음 방향으로 마찬가지로
    설치 및 재귀
  - 재귀 결과 중 max_core 가 가장 큰 놈을 우선하고
    min_cable 값이 가장 작은 놈을 우선하여 하나를 고른다.
  - 가장 optimal한 결과에 내가 이번 스택에서 설치한 전선
    길이만큼을 더해서 리턴. (만약 설치 안했으면 그대로)

*/
static inline return_t solution_recur(vector<vector<bool>> &registered,
                                      vector<idx2d_t> const &core_indices,
                                      size_t idx) {
  if (idx >= core_indices.size()) {
    return return_t{0, 0};
  }
  size_t max_core = 0;
  size_t min_cable = 0;

  for (auto d : deltas) {
    auto vec = try_register(registered, core_indices[idx], d);
    if (!vec.empty()) {
      // do register
      for (auto const &i : vec) {
        registered[i.r][i.c] = true;
      }
      // do recursive call
      auto res = solution_recur(registered, core_indices, idx + 1);
      // undo register
      for (auto const &i : vec) {
        registered[i.r][i.c] = false;
      }

      // do compare
      res.max_core += 1;
      res.min_cable += vec.size();
      if (max_core < res.max_core) {
        max_core = res.max_core;
        min_cable = res.min_cable;
      } else if (max_core == res.max_core) {
        min_cable = std::min(min_cable, res.min_cable);
      } else /*max_core > res.max_core*/ {
        // 더 이상은 볼 필요도 없지 않을까?
        break;
      }
    }
  }

  // 전선을 설치하지 않고 재귀
  {
    auto res = solution_recur(registered, core_indices, idx + 1);
    if (max_core < res.max_core) {
      return res;
    }
  }

  return return_t{max_core, min_cable};
}

/**
  최대한 많은 코어에 전원을 제공할 수 있는 최소 길이의 전선을 구하는 문제.

  코어 하나당 최대 5가지 경우(동서남북, 안그음). 이때 반드시 가장자리에
  직선으로 그어야 한다. 다른 전선과 겹칠수는 없으며, 가장자리에 인접한 코어는
  이미 전원이 공급이 되어 있다고 가정한다.

  # 전처리
    - N * N 크기의 이차원 배열 생성
    - 전선을 연결할 수 없는 부분 (코어)는 register 처리
    - `idx2d_t` 타입 벡터와 `bool` 타입 벡터를 생성한다.
    - 가장자리와 붙어있는 코어는 제외한 나머지 코어의 인덱스를 벡터에 추가한다.
    - 재귀적으로 돌면서 각 인덱스에 해당하는 코어에 전선을 긋거나 긋지 않는
      식의 작업을 수행하며 max_core, min_cable의 길이를 구한다.
*/
inline int solution(vector<vector<bool>> &&cores) {

  const size_t N = cores.size();
  auto core_indices = vector<idx2d_t>();
  // 1..<(N-1) 인 이유는 가장자리 코어를 제외하기 위해서임.
  for (int i = 1; i < N - 1; ++i) {
    for (int j = 1; j < N - 1; ++j) {
      if (cores[i][j]) {
        core_indices.push_back(idx2d_t{i, j});
      }
    }
  }
  auto registered = std::move(cores);
  auto sol = solution_recur(registered, core_indices, 0);
  return static_cast<int>(sol.min_cable);
}

#endif