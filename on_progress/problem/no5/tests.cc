#include "solution.hpp"
#include <gtest/gtest.h>
#include <random.hpp>
#include <vector>

using namespace std;
using sol::MyContainer;

TEST(Add, 1) {
  MyContainer cont{};
  cont.add(1);
  ASSERT_EQ(1, cont.size());
  ASSERT_EQ(1, cont.begin()->data);

  cont.add(2);
  ASSERT_EQ(2, cont.size());
  auto iter = cont.begin();
  ASSERT_EQ(1, iter->data);
  ASSERT_EQ(2, iter->next->data);
  ASSERT_EQ(cont.end(), iter->next->next);
}

TEST(Insert, 1) {
  MyContainer cont{};
  vector<data_t> vec({1, 2, 3, 4, 5});
  for (auto e : vec) {
    cont.add(e);
  }
  ASSERT_EQ(vec.size(), cont.size());

  cont.insert_at(0, 0);
  vector<data_t> answer({0, 1, 2, 3, 4, 5});
  auto iter = cont.begin();
  for (auto e : answer) {
    ASSERT_EQ(e, iter->data);
    iter = iter->next;
  }

  cont.insert_at(5, 999);
  answer = vector<data_t>({0, 1, 2, 3, 4, 999, 5});
  iter = cont.begin();
  for (auto e : answer) {
    ASSERT_EQ(e, iter->data);
    iter = iter->next;
  }
}

TEST(Delete, 1) {
  MyContainer cont{};
  vector<data_t> vec({1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5});
  for (auto e : vec) {
    cont.add(e);
  }
  cont.delete_at(10);
  cont.delete_at(10);
  cont.delete_at(10);
  cont.delete_at(10);
  cont.delete_at(6);
  cont.delete_at(6);
  cont.delete_at(6);
  cont.delete_at(3);
  cont.delete_at(3);
  cont.delete_at(1);

  vector<data_t> answer({1, 2, 3, 4, 5});
  auto iter = cont.begin();
  for (auto e : answer) {
    ASSERT_EQ(e, iter->data);
    iter = iter->next;
  }
}

TEST(Change, 1) {
  MyContainer cont{};
  vector<data_t> vec({1, 999, 3, 999, 5});
  for (auto e : vec) {
    cont.add(e);
  }
  cont.change_at(1, 2);
  cont.change_at(3, 4);

  vector<data_t> answer({1, 2, 3, 4, 5});
  auto iter = cont.begin();
  for (auto e : answer) {
    ASSERT_EQ(e, iter->data);
    iter = iter->next;
  }
}