#include "solution.hpp"
#include <cstdio>
#include <ios>
#include <iostream>
#include <vector>

int main(void) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::freopen("sample_input.txt", "r", stdin);

  size_t t = 0;
  std::cin >> t;

  for (size_t test_case = 1; test_case <= t; ++test_case) {
    size_t n = 0;
    std::cin >> n;
    auto cores = vector<vector<bool>>();
    for (size_t i = 0; i < n; ++i) {
      cores.emplace_back();
      for (size_t j = 0; j < n; ++j) {
        size_t elem;
        std::cin >> elem;
        cores[i].push_back(elem == 0 ? false : true);
      }
    }

    auto submit = solution(std::move(cores));
    std::cout << "#" << test_case << " " << submit << "\n";
  }
}