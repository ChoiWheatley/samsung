#include "solution.hpp"
#include <algorithm>
#include <cstddef>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::ios;
using std::string;
using std::vector;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  freopen("s_input.txt", "r", stdin);

  size_t t;
  cin >> t;
  for (size_t tc = 1; tc <= t; ++tc) {
    cout << "#" << tc << "\n";

    size_t n;
    cin >> n;
    vector<string> ls;

    for (size_t i = 0; i < n; ++i) {
      string word;
      cin >> word;
      ls.push_back(word);
    }

    sol1::sort(ls.begin(), ls.end(), [](auto a, auto b) {
      if (a.size() == b.size()) {
        // sort by string
        return a < b;
      }
      // sort by length
      return a.size() < b.size();
    });

    // make it unique
    auto end = std::unique(ls.begin(), ls.end());
    std::for_each(ls.begin(), end, [](auto elem) { cout << elem << "\n"; });
  }

  return 0;
}