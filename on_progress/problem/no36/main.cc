#include "solution.hpp"
#include <ios>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::ios;
using std::vector;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  freopen("input.txt", "r", stdin);

  int t = 0;
  cin >> t;

  for (int tc = 1; tc <= t; ++tc) {

    vector<u32> days;
    u32 n = 0;
    u32 p = 0;
    cin >> n >> p;

    for (int i = 0; i < n; ++i) {
      u32 day;
      cin >> day;
      days.push_back(day);
    }

    auto submit = sol2::solution(days, p);
    cout << "#" << tc << " " << submit << "\n";
  }
  return 0;
}