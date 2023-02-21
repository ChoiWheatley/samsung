#include "solution.hpp"
#include <ios>
#include <iostream>
#include <sstream>
using std::cin;
using std::cout;
using std::ios;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  size_t t = 0;
  cin >> t;
  for (size_t tc = 1; tc <= t; ++tc) {
    int h;
    int w;
    int n;
    int m;
    cin >> h >> w >> n >> m;
    stringstream dream;
    stringstream sam;
    for (int i = 0; i < h; ++i) {
      string line;
      cin >> line;
      dream << line;
    }
    for (int i = 0; i < n; ++i) {
      string line;
      cin >> line;
      sam << line;
    }

    auto answer = sol1::solution(h, w, n, m, dream.str(), sam.str());
    cout << "#" << tc << " " << answer << "\n";
  }
  return 0;
}