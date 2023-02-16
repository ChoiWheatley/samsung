#include "solution.hpp"
#include <gtest/gtest.h>
#include <random.hpp>
#include <utility>

using namespace sol2;

TEST(Init, 1) {
  uint n = 5;
  std::array<elem_t, N> ls = {1, 2, 3, 4, 5};
  init(ls, n);
  Arr<Node> answer = {Node(),     Node(6, 9), Node(2, 4), Node(4, 5),
                      Node(2, 1), Node(0, 3), Node(4, 0), Node(0, 5),
                      Node(0, 1), Node(2, 0)};
  ASSERT_EQ(answer, _tree);
}

TEST(Update, 1) {
  uint n = 5;
  std::array<elem_t, N> ls = {1, 2, 3, 4, 5};
  init(ls, n);
  update(0, 100, n);
  Arr<Node> answer = {
      Node(),     Node(6, 108), Node(2, 103), Node(4, 5),   Node(2, 100),
      Node(0, 3), Node(4, 0),   Node(0, 5),   Node(0, 100), Node(2, 0),
  };
  ASSERT_EQ(answer, _tree);
}

TEST(Query, 1) {
  uint n = 5;
  std::array<elem_t, N> ls = {1, 2, 3, 4, 5};
  init(ls, n);

  using pair = std::pair<uint, uint>;

  pair rng = {0, 1};
  elem_t answer = 1;
  ASSERT_EQ(answer, jagged_sum(rng.first, rng.second, n));

  rng = {0, 2};
  answer = -1;
  ASSERT_EQ(answer, jagged_sum(rng.first, rng.second, n));

  rng = {0, 3};
  answer = 2;
  ASSERT_EQ(answer, jagged_sum(rng.first, rng.second, n));

  rng = {0, 4};
  answer = -2;
  ASSERT_EQ(answer, jagged_sum(rng.first, rng.second, n));

  rng = {0, 5};
  answer = 3;
  ASSERT_EQ(answer, jagged_sum(rng.first, rng.second, n));

  rng = {1, 2};
  answer = 2;
  ASSERT_EQ(answer, jagged_sum(rng.first, rng.second, n));

  rng = {1, 3};
  answer = -1;
  ASSERT_EQ(answer, jagged_sum(rng.first, rng.second, n));

  rng = {1, 4};
  answer = 3;
  ASSERT_EQ(answer, jagged_sum(rng.first, rng.second, n));

  rng = {1, 5};
  answer = -2;
  ASSERT_EQ(answer, jagged_sum(rng.first, rng.second, n));

  rng = {2, 3};
  answer = 3;
  ASSERT_EQ(answer, jagged_sum(rng.first, rng.second, n));

  rng = {2, 4};
  answer = -1;
  ASSERT_EQ(answer, jagged_sum(rng.first, rng.second, n));

  rng = {2, 5};
  answer = 4;
  ASSERT_EQ(answer, jagged_sum(rng.first, rng.second, n));

  rng = {3, 4};
  answer = 4;
  ASSERT_EQ(answer, jagged_sum(rng.first, rng.second, n));

  rng = {3, 5};
  answer = -1;
  ASSERT_EQ(answer, jagged_sum(rng.first, rng.second, n));
}

TEST(Exhuast, 1) {
  auto constexpr MAXN = 100'000;
  auto constexpr ELEM = 1'000'000'000;
  std::array<elem_t, MAXN> ls;
  ls.fill(ELEM);
  init(ls, MAXN);

  Random<elem_t> rand;
  for (uint i = 0; i < MAXN; ++i) {
    update(i, rand.next(), MAXN);
  }
}

TEST(Edge, 1) {
  std::array<elem_t, N> ls = {1, 2, 3, 4, 5};
  init(ls, 5);
  Arr<Node> answer = {Node(),     Node(6, 9), Node(2, 4), Node(4, 5),
                      Node(2, 1), Node(0, 3), Node(4, 0), Node(0, 5),
                      Node(0, 1), Node(2, 0)};
  ASSERT_EQ(answer, _tree);
  ls = {5, 4, 3, 2, 1};
  init(ls, 5);
  answer = {
      Node(),     Node(6, 9), Node(4, 8), Node(2, 1), Node(4, 5),
      Node(0, 3), Node(2, 0), Node(0, 1), Node(0, 5), Node(4, 0),
  };
  ASSERT_EQ(answer, _tree);
}