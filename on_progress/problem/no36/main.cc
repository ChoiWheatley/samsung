#include "solution.hpp"
#include <ios>
#include <iostream>

using std::cin;
using std::cout;
using std::ios;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  freopen("input.txt", "r", stdin);

  int t = 0;
  cin >> t;

  for (int tc = 1; tc <= t; ++tc) {

    u32 n = 0;
    u32 p = 0;
    u32 last_idx = 0;
    cin >> n >> p;

    // init bitset
    for (int i = 0; i < n; ++i) {
      u32 idx;
      cin >> idx;
      last_idx = (last_idx < idx) ? idx : last_idx;
    }

    auto submit = solution(n, p, last_idx);
    cout << "#" << tc << " " << submit << "\n";
  }
  return 0;
}