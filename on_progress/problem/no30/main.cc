#include "solution.hpp"
#include <ios>
#include <iostream>
#include <sstream>
using std::cin;
using std::cout;
using std::ios;
using namespace sol3;

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
    vector<vector<i64>> dream(h, vector<i64>(w));
    vector<vector<i64>> sam(n, vector<i64>(m));
    for (int i = 0; i < h; ++i) {
      string line;
      cin >> line;
      for (int j = 0; j < w; ++j) {
        dream[i][j] = line[j];
      }
    }
    for (int i = 0; i < n; ++i) {
      string line;
      cin >> line;
      for (int j = 0; j < m; ++j) {
        sam[i][j] = line[j];
      }
    }

    auto answer = solution(dream, sam);
    cout << "#" << tc << " " << answer << "\n";
  }
  return 0;
}