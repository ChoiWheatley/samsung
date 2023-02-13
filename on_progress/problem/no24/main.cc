#include "solution.hpp"
#include <cstdio>
#include <ios>
#include <iostream>
#include <string>

int main(void) {

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  freopen("input.txt", "r", stdin);

  size_t t = 0;
  std::cin >> t;

  for (size_t tc = 1; tc <= t; ++tc) {

    size_t n = 0;
    std::cin >> n;
    Arr<Arr<int>> arr2d;

    for (size_t r = 0; r < n; ++r) {
      std::string line;
      std::cin >> line;

      for (size_t c = 0; c < n; ++c) {
        arr2d[r][c] = line[c] - '0';
      }
    }

    int submit = solution(n, std::move(arr2d));
    std::cout << "#" << tc << " " << submit << "\n";
  }

  return 0;
}