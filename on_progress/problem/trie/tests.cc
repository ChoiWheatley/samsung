#include "trie.hpp"
#include <gtest/gtest.h>

TEST(Compile, Test) {
  Trie<> trie;
  ASSERT_TRUE(trie.insert("abc"));
  ASSERT_FALSE(trie.insert("abc"));
  ASSERT_TRUE(trie.search("abc"));
  ASSERT_FALSE(trie.search("choi"));
  ASSERT_FALSE(trie.search("ab"));
  trie.del("abc");
  ASSERT_FALSE(trie.search("abc"));
}