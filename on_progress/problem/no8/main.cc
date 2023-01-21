#include "solution.hpp"
#include <cstdio>
#include <ios>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int main(void) {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  // DEBUG
  std::freopen("input.txt", "r", stdin);

  constexpr size_t t = 10;
  for (size_t test_case = 1; test_case <= t; ++test_case) {
    size_t n;
    cin >> n;
    vector<char> bin_tree;
    cin.ignore(); // return charactor ignore
    while (n-- > 0) {
      string line;
      std::getline(cin, line);
      std::istringstream stream{line};
      size_t idx;
      char c;
      stream >> idx >> c;
      bin_tree.push_back(c);
    }
    string submit = solution(std::move(bin_tree));
    std::cout << "#" << test_case << " " << submit << "\n";
  }

  return 0;
}