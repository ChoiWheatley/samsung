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
    vector<string> dream;
    vector<string> sam;
    for (int i = 0; i < h; ++i) {
      string line;
      cin >> line;
      dream.push_back(line);
    }
    for (int i = 0; i < n; ++i) {
      string line;
      cin >> line;
      sam.push_back(line);
    }

    auto answer = solution(dream, sam);
    cout << "#" << tc << " " << answer << "\n";
  }
  return 0;
}