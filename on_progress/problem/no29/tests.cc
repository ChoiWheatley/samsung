#include "solution.hpp"
#include <cstddef>
#include <cstdint>
#include <gtest/gtest.h>
#include <random.hpp>
#include <sstream>

using std::string;
using std::stringstream;

/**
ababa
aba
*/
TEST(Sol, 1) {
  using namespace sol1;

  string str = "ababa";
  string pat = "aba";
  size_t answer = 2;
  ASSERT_EQ(answer, solution(str, pat));
}

/**
abracadabra
ab
*/
TEST(Sol, 2) {
  using namespace sol1;

  string str = "abracadabra";
  string pat = "ab";
  size_t answer = 2;
  ASSERT_EQ(answer, solution(str, pat));
} /**
 ababa
 aba
 */
TEST(Sol2, 1) {
  using namespace sol2;

  string str = "ababa";
  string pat = "aba";
  size_t answer = 2;
  ASSERT_EQ(answer, solution(str, pat));
}

/**
abracadabra
ab
*/
TEST(Sol2, 2) {
  using namespace sol2;

  string str = "abracadabra";
  string pat = "ab";
  size_t answer = 2;
  ASSERT_EQ(answer, solution(str, pat));
}

TEST(Integrity, 1) {

  Random<unsigned char> rand;
  constexpr size_t STR_LEN = 500'000;
  constexpr size_t PAT_LEN = 10000 / 10;

  const size_t pat_len = PAT_LEN;

  stringstream str;
  stringstream pat;

  for (size_t i = 0; i < STR_LEN; ++i) {
    str << rand.next();
  }
  for (size_t i = 0; i < pat_len; ++i) {
    pat << rand.next();
  }

  auto answer = sol1::solution(str.str(), pat.str());
  auto submit = sol2::solution(str.str(), pat.str());

  ASSERT_EQ(answer, submit);
}

TEST(Timeout, 1) {

  constexpr size_t STR_LEN = 500'000;

  stringstream str;
  string pat = "a";

  for (size_t i = 0; i < STR_LEN; ++i) {
    str << 'a';
  }

  auto answer = sol1::solution(str.str(), pat);
  auto submit = sol2::solution(str.str(), pat);

  ASSERT_EQ(answer, submit);
}