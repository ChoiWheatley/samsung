#include "solution.hpp"
#include "gtest/gtest.h"
#include <algorithm>
#include <cstddef>
#include <gtest/gtest.h>
#include <limits>
#include <memory>
#include <random>
#include <vector>

using namespace std;
using sol2::CodeContainer;
constexpr size_t MAX = 100000;

struct Random {
  random_device seeder;
  const long seed;
  mt19937 engine;
  uniform_int_distribution<code_t> dist;

  Random()
      : seed{seeder.entropy() != 0.0 ? seeder() : time(nullptr)},
        engine{static_cast<mt19937::result_type>(seed)} {}
  auto next() -> code_t { return dist(engine); }
};

TEST(CONT, add1) {
  Random r{};
  CodeContainer cont{};
  vector<code_t> sample{};
  for (int i = 0; i < MAX; ++i) {
    sample.push_back(r.next());
  }
  int cnt = 0;
  for (code_t elem : sample) {
    cnt++;
    cont.add(elem);
  }
  vector<code_t> answer{};
  for (auto iter = cont.begin(); iter != cont.end(); iter = iter->next) {
    answer.push_back(iter->data);
  }
  ASSERT_EQ(sample, answer);
}

TEST(CONT, add_all1) {
  Random r{};
  CodeContainer cont{};
  vector<code_t> sample{};
  for (int i = 0; i < MAX; ++i) {
    sample.push_back(r.next());
  }
  for (code_t elem : sample) {
    cont.add(elem);
  }
  CodeContainer cont2{};
  cont2.add_all(cont);
  vector<code_t> answer{};
  for (auto iter = cont2.begin(); iter != cont2.end(); iter = iter->next) {
    answer.push_back(iter->data);
  }
  ASSERT_EQ(sample, answer);
}

TEST(CONT, insert1) {
  vector<code_t> sample({1, 2, 5, 6});
  CodeContainer cont1{};
  CodeContainer cont2{};
  for (code_t elem : sample) {
    cont1.add(elem);
  }
  ASSERT_EQ(sample.size(), cont1.size());
  cont2.add(3).add(4);
  cont1.insert_all(2, std::move(cont2));

  vector<code_t> answer({1, 2, 3, 4, 5, 6});
  auto iter = cont1.begin();
  ASSERT_EQ(answer.size(), cont1.size());
  for (const code_t &elem : answer) {
    ASSERT_EQ(elem, iter->data);
    iter = iter->next;
  }
}

TEST(CONT, del1) {
  vector<code_t> sample({1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5});
  vector<code_t> answer({1, 2, 3, 4, 5});
  CodeContainer cont{};
  for (auto elem : sample) {
    cont.add(elem);
  }
  cont.del(11, 4);
  cont.del(7, 3);
  cont.del(4, 2);
  cont.del(2, 1);

  ASSERT_EQ(answer.size(), cont.size());
  auto iter = cont.begin();
  for (auto elem : answer) {
    ASSERT_EQ(elem, iter->data);
    iter = iter->next;
  }
}

/** OK for raw pointers */
TEST(StackOverFlow, RawPointer) {

  Random r{};
  struct Node {
    code_t data;
    Node *next = nullptr;
    explicit Node(code_t data) : data(data){};
  };
  Node *head = new Node(0);
  Node *prev = head;
  for (int i = 1; i < MAX * 2; ++i) {
    prev->next = new Node(r.next());
    prev = prev->next;
  }
}

TEST(StackOverFlow, UniquePointer) {

  Random r{};
  struct Node {
    code_t data;
    unique_ptr<Node> next = nullptr;
    explicit Node(code_t data) : data{data} {};
  };
  auto head = make_unique<Node>(0);
  Node *prev = head.get();
  for (int i = 1; i < MAX; ++i) {
    prev->next = make_unique<Node>(r.next());
    prev = prev->next.get();
  }
}

TEST(StackOverFlow, SharedPointer) {

  Random r{};
  struct Node {
    code_t data;
    shared_ptr<Node> next = nullptr;
    explicit Node(code_t data) : data{data} {};
  };
  auto head = make_shared<Node>(0);
  auto prev = head;
  for (int i = 1; i < MAX; ++i) {
    prev->next = make_shared<Node>(r.next());
    prev = prev->next;
  }
}