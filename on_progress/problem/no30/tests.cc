#include "solution.hpp"
#include <algorithm>
#include <cstddef>
#include <gtest/gtest.h>
#include <iterator>
#include <random.hpp>
#include <sstream>
#include <sys/types.h>

TEST(Sol, 1) {
  int h = 2;
  int w = 2;
  int n = 3;
  int m = 3;
  string dream = "oooo";
  string sam = "ooooooooo";

  int correct = 4;
  int answer = sol1::solution(h, w, n, m, dream, sam);
  ASSERT_EQ(correct, answer);
}
TEST(Sol, 2) {
  int h = 4;
  int w = 4;
  int n = 10;
  int m = 10;
  string dream = "oxxo"
                 "xoox"
                 "xoox"
                 "oxxo";
  string sam = "xxxxxxoxxo"
               "oxxoooxoox"
               "xooxxxxoox"
               "xooxxxoxxo"
               "oxxoxxxxxx"
               "ooooxxxxxx"
               "xxxoxxoxxo"
               "oooxooxoox"
               "oooxooxoox"
               "xxxoxxoxxo";

  int correct = 4;
  int answer = sol1::solution(h, w, n, m, dream, sam);
  ASSERT_EQ(correct, answer);
}
TEST(Sol, 3) {
  int h = 1;
  int w = 1;
  int n = 1;
  int m = 1;
  string dream = "o";
  string sam = "o";

  int correct = 1;
  int answer = sol1::solution(h, w, n, m, dream, sam);
  ASSERT_EQ(correct, answer);
}
TEST(Sol, 4) {
  int h = 100;
  [[maybe_unused]] int w = 100;
  int n = 100;
  [[maybe_unused]] int m = 100;
  stringstream dream_str;
  stringstream sam_str;

  for (int i = 0; i < h; ++i) {
    dream_str << 'o';
    sam_str << 'o';
  }

  vector<string> dream;
  vector<string> sam;

  for (int i = 0; i < h; ++i) {
    dream.emplace_back(dream_str.str());
  }
  for (int i = 0; i < n; ++i) {
    sam.emplace_back(sam_str.str());
  }

  int correct = 1;
  int answer = sol2::solution(dream, sam);
  ASSERT_EQ(correct, answer);
}
TEST(Exhaust, 1) {
  int h = 10;
  int w = 10;
  int n = 100;
  int m = 100;
  vector<string> dream;
  vector<string> sam;
  Random<u_char> rand;

  for (int i = 0; i < h; ++i) {
    stringstream dream_str;
    for (int j = 0; j < w; ++j) {
      dream_str << (rand.next() % 2 == 0 ? "o" : "x");
    }
    dream.emplace_back(dream_str.str());
  }

  for (int i = 0; i < n; ++i) {
    stringstream sam_str;
    for (int j = 0; j < m; ++j) {
      sam_str << (rand.next() % 2 == 0 ? "o" : "x");
    }
    sam.emplace_back(sam_str.str());
  }

  sol2::solution(dream, sam);
}
TEST(Exhaust, 2) {
  Random<u_char> rand;
  int h = 100;
  int w = 100;
  vector<string> ls;

  for (int i = 0; i < h; ++i) {
    stringstream str;
    for (int j = 0; j < w; ++j) {
      str << (rand.next() & 1 ? "x" : "o");
    }
    ls.emplace_back(str.str());
  }
  sol2::rabin_karp_2d(ls, w);
}
TEST(Exhaust, 3) {

  using namespace sol3;

  Random<u_char> rand;
  int h = 2000;
  int w = 2000;
  vector<vector<i64>> ls(h, vector<i64>(w));

  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      ls[i][j] = (rand.next() & 1);
    }
  }
  sol3::rabin_karp(ls, w);
}
TEST(Exhaust, 4) {
  int h = 2000;
  int w = 2000;
  int n = 2000;
  int m = 2000;
  vector<string> dream;
  vector<string> sam;
  Random<u_char> rand;

  for (int i = 0; i < h; ++i) {
    stringstream dream_str;
    for (int j = 0; j < w; ++j) {
      dream_str << (rand.next() % 2 == 0 ? "o" : "x");
    }
    dream.emplace_back(dream_str.str());
  }

  for (int i = 0; i < n; ++i) {
    stringstream sam_str;
    for (int j = 0; j < m; ++j) {
      sam_str << (rand.next() % 2 == 0 ? "o" : "x");
    }
    sam.emplace_back(sam_str.str());
  }

  sol3::solution(dream, sam);
}
TEST(Exhaust, CumulativeSum) {

  using namespace sol3;

  Random<char> rand;
  int h = 2000;
  int w = 2000;
  vector<vector<i64>> ls(h, vector<i64>(w));

  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      ls[i][j] = rand.next();
    }
  }
  // sol3::rabin_karp(ls, w);
  sol3::cumulative_sum(ls);
}

TEST(Exhaust, MapToInt) {

  using namespace sol3;

  int h = 2000;
  int w = 2000;
  int n = 2000;
  int m = 2000;
  vector<string> dream;
  vector<string> sam;
  Random<u_char> rand;

  for (int i = 0; i < h; ++i) {
    stringstream dream_str;
    for (int j = 0; j < w; ++j) {
      dream_str << (rand.next() % 2 == 0 ? "o" : "x");
    }
    dream.emplace_back(dream_str.str());
  }

  for (int i = 0; i < n; ++i) {
    stringstream sam_str;
    for (int j = 0; j < m; ++j) {
      sam_str << (rand.next() % 2 == 0 ? "o" : "x");
    }
    sam.emplace_back(sam_str.str());
  }
  map_to_int(dream);
  map_to_int(sam);
}

TEST(Exhaust, AsciiMap) {

  using namespace sol3;
  int h = 2000;
  int w = 2000;
  Random<char> rand;
  for (int i = 0; i < h * w; ++i) {
    ascii_map(rand.next());
  }
}
TEST(Exhaust, PartialSum) {

  using namespace sol3;

  Random<char> rand;
  int h = 1000;
  int w = 1000;
  int n = 2000;
  int m = 2000;
  vector<vector<i64>> ls(n, vector<i64>(m));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      ls[i][j] = rand.next();
    }
  }

  for (int i = 0; i <= n - h; ++i) {
    for (int j = 0; j <= m - w; ++j) {
      partial_sum(ls, i, j, i + h - 1, j + w - 1);
    }
  }
}

TEST(Exhaust, 5) {

  using namespace sol3;

  Random<char> rand;
  int h = 2000;
  int w = 2000;
  vector<vector<i64>> dream(h, vector<i64>(w));
  vector<vector<i64>> sam(h, vector<i64>(w));

  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      dream[i][j] = rand.next() & 1;
      sam[i][j] = rand.next() & 1;
    }
  }
  solution(dream, sam);
}

TEST(RK, 1) {
  vector<string> str2d1 = {"oxox", "oooo", "xxxx", "xoxo"};
  vector<string> str2d2 = {"oxox", "oooo", "xxxx", "xoxx"};

  auto cum1 = sol2::rabin_karp_2d(str2d1, 4);
  auto cum2 = sol2::rabin_karp_2d(str2d2, 4);

  ASSERT_NE(cum1, cum2);
}

TEST(PartialSum, 1) {

  using namespace sol2;

  vector<string> str2d = {"oxox", "oooo", "xxxx", "xoxo"};
  vector<string> str2d_2_2 = {"xx00", "xo00", "0000",
                              "0000"}; // from (2,2) to (3,3)

  auto cum = sol2::rabin_karp_2d(str2d, 4);
  auto cum_2_2 = sol2::rabin_karp_2d(str2d_2_2, 4);

  for (int64_t i = 0; i < 2; ++i) {
    for (int64_t j = 0; j < 2; ++j) {
      ASSERT_EQ(mod((str2d_2_2[i][j] * sol2::pow(B, i * 4 + j)), MOD),
                (cum_2_2[i][j]));
      ASSERT_EQ(mod((cum_2_2[i][j] * sol2::pow(B, 2 * 4 + 2)), MOD),
                (cum[i + 2][j + 2]));
    }
  }

  int64_t real_sum = 0;
  int64_t fake_sum = 0;
  for (int64_t i = 0; i < 2; ++i) {
    for (int64_t j = 0; j < 2; ++j) {
      real_sum = mod((real_sum + cum_2_2[i][j]), MOD);
      fake_sum = mod((fake_sum + cum[i + 2][j + 2]), MOD);
    }
  }
  ASSERT_EQ(mod((real_sum * sol2::pow(B, 10)), MOD), fake_sum);

  cum = cumulative_sum(std::move(cum));
  cum_2_2 = cumulative_sum(std::move(cum_2_2));

  auto answer = cum_2_2[1][1];
  auto submit = partial_sum(cum, 2, 2, 3, 3);

  ASSERT_EQ(real_sum, answer);
  ASSERT_EQ(fake_sum, submit);

  answer = mod((answer * sol2::pow(B, 2 * 4 + 2)), MOD);

  ASSERT_EQ(answer, submit);
}

#include <random.hpp>

TEST(PartialSum, 2) {

  using namespace sol2;

  Random<int64_t> rand;
  const int64_t ROW = 100;
  const int64_t COL = 110;
  const int64_t i1 = ROW / 2 + (rand.next() % 10);
  const int64_t j1 = ROW / 2 + (rand.next() % 10);
  const int64_t i2 = ROW - (rand.next() % 10) - 1;
  const int64_t j2 = COL - (rand.next() % 10) - 1;

  auto ls = vector<vector<int64_t>>(ROW, vector<int64_t>(COL));

  for (int64_t i = 0; i < ROW; ++i) {
    for (int64_t j = 0; j < COL; ++j) {
      ls[i][j] = mod(rand.next(), MOD);
    }
  }
  int64_t answer = 0;
  for (int64_t i = i1; i <= i2; ++i) {
    for (int64_t j = j1; j <= j2; ++j) {
      answer = mod((answer + ls[i][j]), MOD);
    }
  }
  ls = sol2::cumulative_sum(std::move(ls));
  int64_t submit = sol2::partial_sum(ls, i1, j1, i2, j2);

  ASSERT_EQ(answer, submit);
}

TEST(Sol2, 1) {

  using namespace sol2;

  vector<string> dream = {"oo", "oo"};
  vector<string> sam = {"ooo", "ooo", "ooo"};

  int answer = 4;

  int submit = solution(dream, sam);

  ASSERT_EQ(answer, submit);
}
TEST(Sol2, 2) {

  using namespace sol2;

  vector<string> dream = {"oxxo", "xoox", "xoox", "oxxo"};
  vector<string> sam = {"xxxxxxoxxo", "oxxoooxoox", "xooxxxxoox", "xooxxxoxxo",
                        "oxxoxxxxxx", "ooooxxxxxx", "xxxoxxoxxo", "oooxooxoox",
                        "oooxooxoox", "xxxoxxoxxo"};

  int correct = 4;
  int answer = solution(dream, sam);
  ASSERT_EQ(correct, answer);
}

TEST(Transform, 1) {
  vector<int> before = {1, 2, 3, 4, 5};
  vector<int> after;
  std::transform(before.begin(), before.end(), std::back_inserter(after),
                 [](int e) { return e * e; });
  ASSERT_EQ(vector<int>({1, 4, 9, 16, 25}), after);
}

TEST(Sol3, 1) {

  using namespace sol3;

  vector<string> dream = {"oo", "oo"};
  vector<string> sam = {"ooo", "ooo", "ooo"};

  int answer = 4;

  int submit = solution(dream, sam);

  ASSERT_EQ(answer, submit);
}
TEST(Sol3, 2) {

  using namespace sol3;

  vector<string> dream = {"oxxo", "xoox", "xoox", "oxxo"};
  vector<string> sam = {"xxxxxxoxxo", "oxxoooxoox", "xooxxxxoox", "xooxxxoxxo",
                        "oxxoxxxxxx", "ooooxxxxxx", "xxxoxxoxxo", "oooxooxoox",
                        "oooxooxoox", "xxxoxxoxxo"};

  int correct = 4;
  int answer = solution(dream, sam);
  ASSERT_EQ(correct, answer);
}
TEST(Sol3, 3) {

  using namespace sol3;

  const size_t h = 4;
  const size_t w = 4;
  const size_t n = 5;
  const size_t m = 5;

  vector<string> dream;
  vector<string> sam;

  auto str_small = string(w, 'o');
  auto str_big = string(m, 'o');
  for (size_t i = 0; i < h; ++i) {
    dream.push_back(str_small);
  }
  for (size_t i = 0; i < n; ++i) {
    sam.push_back(str_big);
  }

  int correct = (n - w + 1) * (m - h + 1);
  int answer = solution(dream, sam);
  ASSERT_EQ(correct, answer);
}

TEST(Overflow, 1) {

  using namespace sol3;

  unsigned int i = 1 << 31;
  i = i << 1;
  ASSERT_EQ(0x00000000, i);
  i = 1 << 31;
  i = i * 2;
  ASSERT_EQ(0x00000000, i);
}
TEST(Underflow, 1) {

  unsigned int i = 0;
  i = i - 1;
  ASSERT_EQ(0xffffffff, i);
}

TEST(Integrity, 1) {
  int h = 50;
  int w = 50;
  int n = 100;
  int m = 100;
  vector<string> dream;
  vector<string> sam;
  Random<u_char> rand;

  for (int i = 0; i < h; ++i) {
    stringstream dream_str;
    for (int j = 0; j < w; ++j) {
      dream_str << (rand.next() % 2 == 0 ? "o" : "x");
    }
    dream.emplace_back(dream_str.str());
  }

  for (int i = 0; i < n; ++i) {
    stringstream sam_str;
    for (int j = 0; j < m; ++j) {
      sam_str << (rand.next() % 2 == 0 ? "o" : "x");
    }
    sam.emplace_back(sam_str.str());
  }

  auto answer = sol2::solution(dream, sam);
  auto submit = sol3::solution(dream, sam);

  ASSERT_EQ(answer, submit);
}