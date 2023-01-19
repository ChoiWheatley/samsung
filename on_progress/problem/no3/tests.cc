#include "solution.hpp"
#include <algorithm>
#include <functional>
#include <gtest/gtest.h>
#include <random>

using namespace std;

TEST(SHORT, SIZE) { ASSERT_EQ(1, sizeof(char)); }

TEST(GEN, 1) {
  ASSERT_EQ(set<char>({0b0110, 0b0111, 0b1110, 0b1111}),
            case_generator([](char a) { return ((a & 0b0110) == 0b0110); }));
}

// TEST(GEN, 2)
// {
//     ASSERT_EQ(set<char>({0b0001, 0b0011, 0b0101, 0b0111, 0b1001, 0b1011,
//     0b1101, 0b1111}), case_generator((char)0b0001));
// }

TEST(GEN, 3) {
  const char yesterday = 0b0100;
  const char today = 0b0010;
  auto pred = [](char a) {
    return ((a & today) == today) && // 오늘 당번은 무조건 와야 하고
           ((a & yesterday) !=
            0b0000); // 어제 적어도 한 명은 오늘 다시 와야한다.
  };
  set<char> answer{0b0110, 0b0111, 0b1110, 0b1111};
  ASSERT_EQ(answer, case_generator(pred));
}

TEST(GEN, 4) {
  const char yesterday = 0b0101;
  const char today = 0b0010;
  auto pred = [](char a) {
    return ((a & today) == today) && // 오늘 당번은 무조건 와야 하고
           ((a & yesterday) !=
            0b0000); // 어제 적어도 한 명은 오늘 다시 와야한다.
  };
  set<char> answer{0b0011, 0b0110, 0b0111, 0b1011, 0b1110, 0b1111};
  ASSERT_EQ(answer, case_generator(pred));
}

TEST(GEN, 5) {
  const char yesterday = 0b0110;
  const char today = 0b0010;
  auto pred = [](char a) {
    return ((a & today) == today) && // 오늘 당번은 무조건 와야 하고
           ((a & yesterday) !=
            0b0000); // 어제 적어도 한 명은 오늘 다시 와야한다.
  };
  set<char> answer{0b0010, 0b0011, 0b0110, 0b0111,
                   0b1010, 0b1011, 0b1110, 0b1111};
  ASSERT_EQ(answer, case_generator(pred));
}

TEST(GEN, 6) {
  const char yesterday = 0b0111;
  const char today = 0b0010;
  auto pred = [](char a) {
    return ((a & today) == today) && // 오늘 당번은 무조건 와야 하고
           ((a & yesterday) !=
            0b0000); // 어제 적어도 한 명은 오늘 다시 와야한다.
  };
  set<char> answer{0b0010, 0b0011, 0b0110, 0b0111,
                   0b1010, 0b1011, 0b1110, 0b1111};
  ASSERT_EQ(answer, case_generator(pred));
}

TEST(GEN, 7) {
  const char yesterday = 0b1100;
  const char today = 0b0010;
  auto pred = [](char a) {
    return ((a & today) == today) && // 오늘 당번은 무조건 와야 하고
           ((a & yesterday) !=
            0b0000); // 어제 적어도 한 명은 오늘 다시 와야한다.
  };
  set<char> answer{0b0110, 0b0111, 0b1010, 0b1011, 0b1110, 0b1111};
  ASSERT_EQ(answer, case_generator(pred));
}

TEST(GEN, 8) {
  const char yesterday = 0b1101;
  const char today = 0b0010;
  auto pred = [](char a) {
    return ((a & today) == today) && // 오늘 당번은 무조건 와야 하고
           ((a & yesterday) !=
            0b0000); // 어제 적어도 한 명은 오늘 다시 와야한다.
  };
  set<char> answer{0b0011, 0b0110, 0b0111, 0b1010, 0b1011, 0b1110, 0b1111};
  ASSERT_EQ(answer, case_generator(pred));
}

TEST(GEN, 9) {
  const char yesterday = 0b1110;
  const char today = 0b0010;
  auto pred = [](char a) {
    return ((a & today) == today) && // 오늘 당번은 무조건 와야 하고
           ((a & yesterday) !=
            0b0000); // 어제 적어도 한 명은 오늘 다시 와야한다.
  };
  set<char> answer{0b0010, 0b0011, 0b0110, 0b0111,
                   0b1010, 0b1011, 0b1110, 0b1111};
  ASSERT_EQ(answer, case_generator(pred));
}

TEST(GEN, 10) {
  const char yesterday = 0b1111;
  const char today = 0b0010;
  auto pred = [](char a) {
    return ((a & today) == today) && // 오늘 당번은 무조건 와야 하고
           ((a & yesterday) !=
            0b0000); // 어제 적어도 한 명은 오늘 다시 와야한다.
  };
  set<char> answer{0b0010, 0b0011, 0b0110, 0b0111,
                   0b1010, 0b1011, 0b1110, 0b1111};
  ASSERT_EQ(answer, case_generator(pred));
}

TEST(SOL, 1) {
  const string test = "BC";
  uint64_t answer = 29;
  uint64_t submit = sol1::solution(test);
  ASSERT_EQ(answer, submit);
}

TEST(SOL, 1_1) {
  const string test = "BC";
  uint64_t answer = 29;
  uint64_t submit = sol2::solution(test);
  ASSERT_EQ(answer, submit);
}

TEST(SOL, 1_2) {
  const string test = "BC";
  uint64_t answer = 29;
  uint64_t submit = sol3::solution(test);
  ASSERT_EQ(answer, submit);
}

TEST(SOL, 2) {
  const string test = "ADCBBACDCBCBACBDCABDCBA";
  uint64_t answer = 88253169;
  uint64_t submit = sol2::solution(test);
  ASSERT_EQ(answer, submit);
}

TEST(SOL, 2_1) {
  const string test = "ADCBBACDCBCBACBDCABDCBA";
  uint64_t answer = 88253169;
  uint64_t submit = sol3::solution(test);
  ASSERT_EQ(answer, submit);
}

TEST(TIMEOUT, 1) {
  const int MAX = 100000;

  random_device seeder;
  const auto seed{seeder.entropy() == 0.0 ? seeder() : time(nullptr)};
  mt19937 engine{static_cast<mt19937::result_type>(seed)};
  uniform_int_distribution<char> dist('A', 'D');

  stringstream stream{};
  for (int i = 0; i < MAX; ++i) {
    stream << dist(engine);
  }
  sol2::solution(stream.str());
  // cout << stream.str() << "\n";
}

TEST(TIMEOUT, 1_1) {
  const int MAX = 100000;

  random_device seeder;
  const auto seed{seeder.entropy() == 0.0 ? seeder() : time(nullptr)};
  mt19937 engine{static_cast<mt19937::result_type>(seed)};
  uniform_int_distribution<char> dist('A', 'D');

  stringstream stream{};
  for (int i = 0; i < MAX; ++i) {
    stream << dist(engine);
  }
  sol3::solution(stream.str());
  // cout << stream.str() << "\n";
}