#include "solution.hpp"
#include <functional>
#include <gtest/gtest.h>
#include <string>

TEST(Set, 1) {
  MySet<string, MyHasher> set;
  set.insert("aaa");
  set.insert("bbb");
  set.insert("ccc");

  ASSERT_EQ(3, set.size());

  ASSERT_TRUE(set.contains("aaa"));
  ASSERT_TRUE(set.contains("bbb"));
  ASSERT_TRUE(set.contains("ccc"));
  ASSERT_FALSE(set.contains("ddd"));
}

TEST(Set, 2) {
  MySet<string, MyHasher> set;
  set.insert("aaa");
  set.insert("aaa");
  set.insert("aaa");

  ASSERT_EQ(1, set.size());

  ASSERT_TRUE(set.contains("aaa"));
  ASSERT_FALSE(set.contains("bbb"));
  ASSERT_FALSE(set.contains("ccc"));
  ASSERT_FALSE(set.contains("ddd"));
}

TEST(Set, 3) {
  MySet<string, MyHasher> set;
  set.insert("aaa");
  set.insert("bbb");
  set.insert("ccc");

  ASSERT_EQ(3, set.size());

  set.remove("aaa");

  ASSERT_EQ(2, set.size());
  ASSERT_FALSE(set.contains("aaa"));
}

TEST(TwoSets, 1) {
  MySet<string, MyHasher> set1;
  MySet<string, MyHasher> set2;

  auto ls1 = {"ab", "a"};
  auto ls2 = {"a", "ac", "ba"};

  for (auto e : ls1) {
    set1.insert(e);
  }
  for (auto e : ls2) {
    set2.insert(e);
  }

  size_t cnt = 0;
  for (auto e : ls1) {
    if (set2.contains(e)) {
      cnt++;
    }
  }

  ASSERT_EQ(1, cnt);
}