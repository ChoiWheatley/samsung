#ifndef SOLUTION
#define SOLUTION

#include <algorithm>
#include <cstddef>
#include <tuple>
#include <utility>

using std::pair;
using std::size_t;

struct idx2d_t {
  int r;
  int c;
};

using edge_t = pair<idx2d_t, idx2d_t>;

inline bool operator==(idx2d_t const &a, idx2d_t const &b) {
  return a.r == b.r && a.c == b.c;
}

/** q가 p-r 세그먼트 위에 놓여져 있는지 판단*/
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

#endif