#include "solution.hpp"
#include <cstddef>
#include <cstdio>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

using std::vector;

int main(void) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  freopen("input.txt", "r", stdin);

  size_t t;
  std::cin >> t;

  for (size_t tc = 1; tc < t; ++tc) {

    size_t n;
    std::cin >> n;
    auto tbl = vector<vector<bool>>(n, vector<bool>(n, false));

    for (size_t i = 0; i <= n; ++i) {
      std::string str;
      std::cin >> str;
      for (size_t j = 0; j < n; ++j) {
        char c = str[j];
        if (c == '.') {
          tbl[i][j] = false;
        } else if (c == '*') {
          tbl[i][j] = true;
        }
      }
    }

    auto submit = solution(tbl);
    std::cout << "#" << tc << " " << submit << "\n";
  }
}