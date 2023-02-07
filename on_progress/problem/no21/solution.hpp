/**
0-1 knapsack
N개의 물건(부피와 가치를 갖는다.)과 K만큼의 부피를 넣을 수 있는 가방이 있을 때
넘치지 않고 물건을 담아 그 가치의 합을 최대화 하고자 한다.
*/

#ifndef SOLUTION
#define SOLUTION
#include <bits/stdc++.h>
#include <sys/select.h>

using namespace std;
constexpr size_t MAX_ITEM = 100;
constexpr size_t MAX_VOLUME = 1000;

/**memo[i][j] = i번째 아이템들을 활용하여 j부피 이내에 담을 수 있는 최고가격*/
static array<array<int, MAX_VOLUME + 1>, MAX_ITEM + 1> memo;

inline auto solution(vector<int> const &volume, vector<int> const &cost,
                     int capacity) {
  assert(volume.size() == cost.size());
  auto const N = volume.size();
  // init
  for (size_t i = 0; i <= MAX_ITEM; ++i) {
    memo[i][0] = 0;
  }
  for (size_t j = 0; j <= MAX_VOLUME; ++j) {
    memo[0][j] = 0;
  }

  // do dp
  for (size_t i = 1; i <= N; ++i) {
    for (size_t j = 1; j <= capacity; ++j) {
      auto cur_volume = volume[i - 1];
      auto cur_cost = cost[i - 1];
      if (cur_volume > j) {
        memo[i][j] = memo[i - 1][j];
      } else {
        auto select = cur_cost + memo[i - 1][j - cur_volume];
        auto prev = memo[i - 1][j];
        memo[i][j] = std::max(select, prev);
      }
    }
  }
  return memo[N][capacity];
}

#endif