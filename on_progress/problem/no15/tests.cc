#include "solution.hpp"
#include <gtest/gtest.h>
#include <random.hpp>
#include <vector>

using namespace std;
using namespace node;

using namespace sol3;

TEST(Ancester, 1) {
  node_t root{};
  node_t n1{1, &root};
  node_t n2{2, &root};
  node_t n3{3, &n1};
  node_t n4{4, &n1};
  node_t n5{5, &n2};
  node_t n6{6, &n2};

  auto anc6_correct = vector<node_t const *>{&n2, &root};
  auto anc6_answer = ancester(n6);

  ASSERT_EQ(anc6_correct, anc6_answer);
}

TEST(Dist, 1) {
  node_t root{};
  node_t n1{1, &root};
  node_t n2{2, &root};
  node_t n3{3, &n1};
  node_t n4{4, &n1};
  node_t n5{5, &n2};
  node_t n6{6, &n2};

  auto d3_6 = 4;
  auto d3_6_answer = dist(n3, n6);

  ASSERT_EQ(d3_6, d3_6_answer);
}

TEST(NCA, 1) {
  node_t root{};
  node_t n1{1, &root};
  node_t n2{2, &root};
  node_t n3{3, &n1};
  n1.add_child(&n3);
  node_t n4{4, &n1};
  n1.add_child(&n4);
  node_t n5{5, &n2};
  n2.add_child(&n5);
  node_t n6{6, &n2};
  n2.add_child(&n6);

  auto const *param1 = &n3;
  auto const *param2 = &n4;
  node_t const *nca_answer = &n1;
  node_t const &nca_submit = nearest_common_ancester(param1, param2);
  ASSERT_EQ(nca_answer->id, nca_submit.id);
}

TEST(Sol, 1) {
  auto data = vector<idx_t>{1, 1, 2};
  auto answer = 6;
  auto submit = solution(data);
  ASSERT_EQ(answer, submit);
}
TEST(Sol, 2) {
  auto data = vector<idx_t>{1, 1, 3};
  auto answer = 4;
  auto submit = solution(data);
  ASSERT_EQ(answer, submit);
}
TEST(Sol, 3) {
  auto data = vector<idx_t>{1, 1, 3, 3, 2, 4, 1, 3, 2, 9};
  auto answer = 25;
  auto submit = solution(data);
  ASSERT_EQ(answer, submit);
}

TEST(Timeout, 1) {
  Random<uint32_t> r{};
  auto data = vector<idx_t>{};
  for (size_t i = 2; i < node::MAX_NODE; ++i) {
    data.emplace_back((r.next() % (i - 1)) + 1);
  }
  solution(data);
}
/**
0
 ├─1
 └─2
    ├─3
    └─4
       ├─5
       └─6
*/
TEST(Timeout, 2) {

  auto data = vector<idx_t>{1};
  for (size_t i = 2; i < MAX_NODE; i += 2) {
    data.emplace_back(i);
    data.emplace_back(i);
  }
  solution(data);
}
/**
TEST2인데 두 개를 동시에 가지고 있는 모양
*/
TEST(Timeout, 3) {

  constexpr auto HALF_MAX = 43'000;
  auto data = vector<idx_t>{1};
  for (size_t i = 2; i < HALF_MAX; i += 2) {
    data.emplace_back(i);
    data.emplace_back(i);
  }
  data.emplace_back(1);
  for (size_t i = 1; i < HALF_MAX; i += 2) {
    data.emplace_back(HALF_MAX + i);
    data.emplace_back(HALF_MAX + i);
  }
  solution(data);
}