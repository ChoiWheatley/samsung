#include "solution.hpp"
#include <ios>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::ios;
using std::ios_base;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  size_t t = 0;
  cin >> t;

  for (size_t tc = 1; tc <= t; ++tc) {

    size_t n;
    size_t m;
    cin >> n >> m;

    MySet<string, MyHasher> set;

    for (size_t i = 0; i < n; ++i) {

      string word;
      cin >> word;
      set.insert(word);
    }

    size_t cnt = 0;
    for (size_t j = 0; j < m; ++j) {
      string word;
      cin >> word;
      if (set.contains(word)) {
        cnt++;
      }
    }

    cout << "#" << tc << " " << cnt << "\n";
  }

  return 0;
}