#include "solution.hpp"
#include <algorithm>
#include <cmath>
#include <ios>
#include <iostream>
#include <limits>
#include <vector>

using std::abs;
using std::cin;
using std::cout;
using std::ios;
using std::vector;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  freopen("sample_input.txt", "r", stdin);

  int t = 0;
  cin >> t;

  for (int tc = 1; tc <= t; ++tc) {

    int n;
    int m;
    int c1;
    int c2;
    cin >> n >> m >> c1 >> c2;
    int dist_x = abs(c1 - c2);
    vector<int> cows;
    vector<int> horses;

    for (int i = 0; i < n; ++i) {
      int cow;
      cin >> cow;
      cows.push_back(cow);
    }
    // cow를 정렬하고 horse는 벡터에 넣지말고 바로 bin_search
    std::sort(cows.begin(), cows.end());

    int dist_z = std::numeric_limits<int>::max();
    int count = 0;

    auto evaluate = [&dist_z, &count](int dist) {
      if (dist < dist_z) {
        dist_z = dist;
        count = 1;
      } else if (dist == dist_z) {
        count += 1;
      }
    };

    for (int i = 0; i < m; ++i) {
      int horse;
      cin >> horse;

      // 어떤 말에 대하여 (말 <= 소) 조건을 만족시키는 첫번째 말을 고른다.
      // 그 말의 바로 이전 말과 비교하여 더 가까운 놈을 선택한다.
      auto cow_itr = first_true(cows.begin(), cows.end(),
                                [horse](auto itr) { return horse <= *itr; });
      if (cow_itr != cows.end()) {
        evaluate(abs(horse - *cow_itr));
      }
      if (cow_itr != cows.begin()) {
        evaluate(abs(horse - *(cow_itr - 1)));
      }
    }

    cout << "#" << tc << " " << dist_z + dist_x << " " << count << "\n";
  }
  return 0;
}