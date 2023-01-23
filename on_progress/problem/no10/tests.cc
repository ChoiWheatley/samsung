#include "solution.hpp"
#include <gtest/gtest.h>

TEST(Add, 1) {
  BinTree<1> bintree;
  bintree.add(0, "1");
  ASSERT_EQ(1.0f, bintree.calc());
}

TEST(Add, 2) {
  BinTree<1000> bintree; // array의 크기는 별 상관이 없구나
  bintree.add(0, "1");
  ASSERT_EQ(1.0f, bintree.calc());
}

TEST(Add, 3) {
  BinTree<> bintree; // 그래서 그냥 default template argument 줘버림.
  bintree.add(0, "1");
  ASSERT_EQ(1.0f, bintree.calc());
}

TEST(Add, 4) {
  BinTree<> bintree;
  ASSERT_THROW(bintree.add(0, "*"), not_a_number);
}

TEST(Add, 5) {
  BinTree<> bintree;
  bintree.add(0, "*", 1, 2);
  bintree.add(1, "/", 3, 4);
  bintree.add(2, "3");
  bintree.add(3, "9");
  bintree.add(4, "-", 5, 6);
  bintree.add(5, "6");
  bintree.add(6, "4");
}

TEST(Calc, 1) {
  BinTree<> bintree;
  bintree.add(0, "*", 1, 2);
  bintree.add(1, "/", 3, 4);
  bintree.add(2, "3");
  bintree.add(3, "9");
  bintree.add(4, "-", 5, 6);
  bintree.add(5, "6");
  bintree.add(6, "4");

  float answer = (9.0 / (6.0 - 4.0)) * 3.0;
  ASSERT_FLOAT_EQ(answer, bintree.calc());
}