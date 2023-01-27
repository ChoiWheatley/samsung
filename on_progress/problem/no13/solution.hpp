#ifndef SOLUTION
#define SOLUTION

#include <algorithm>
#include <array>
#include <cstddef>
#include <exception>
#include <tuple>
#include <utility>
#include <vector>

using std::pair;
using std::size_t;
using std::vector;
using bitset_t = size_t;

struct idx2d_t {
  int r;
  int c;
};

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

/**
  최대한 많은 코어에 전원을 제공할 수 있는 최소 길이의 전선을 구하는 문제.

  코어 하나당 최대 4번의 edge를 그릴 수 있다(동서남북). 이때 반드시 가장자리에
  직선으로 그어야 한다. 다른 전선과 겹칠수는 없으며, 가장자리에 인접한 코어는
  이미 전원이 공급이 되어 있다고 가정한다.
*/
inline int solution(vector<vector<bool>> const &cores) {
  const size_t N = cores.size();
  auto bounded_mat = vector<vector<bool>>(N + 1, vector<bool>(N + 1));
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      bounded_mat[i + 1][j + 1] = cores[i][j];
    }
  }
}

#endif