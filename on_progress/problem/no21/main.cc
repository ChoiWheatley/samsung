#include "solution.hpp"
#include <ios>
#include <iostream>

using namespace std;

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  size_t t;
  cin >> t;
  for (size_t tc = 1; tc <= t; ++tc) {
    vector<int> volume;
    vector<int> cost;
    int n;
    int k;
    cin >> n >> k;
    while (n-- > 0) {
      int v = 0;
      int c = 0;
      cin >> v >> c;
      volume.push_back(v);
      cost.push_back(c);
    }
    auto submit = solution(volume, cost, k);

    cout << "#" << tc << " " << submit << "\n";
  }
  return 0;
}