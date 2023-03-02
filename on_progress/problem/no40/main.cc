#include "solution.hpp"
#include <cmath>
#include <ios>
#include <iostream>

using std::abs;
using std::cin;
using std::cout;
using std::ios;

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
    for (int i = 0; i < m; ++i) {
      int horse;
      cin >> horse;
      horses.push_back(horse);
    }

    auto result = solution(cows, horses);

    cout << "#" << tc << " " << result.first + dist_x << " " << result.second
         << "\n";
  }
  return 0;
}