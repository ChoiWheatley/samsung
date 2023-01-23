#include "solution.hpp"
#include <algorithm>
#include <array>
#include <cstdio>
#include <cstring>
#include <ios>
#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::getline;
using std::istringstream;
using std::stoi;
using std::string;
using std::vector;

int main(void) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  // DEBUG
  freopen("input.txt", "r", stdin);

  constexpr size_t t = 10;
  for (size_t test_case = 1; test_case <= t; ++test_case) {

    size_t n = 0;
    cin >> n;
    cin.ignore();
    BinTree<> tree{};

    while (n-- > 0) {
      string line{};
      getline(cin, line, '\n');
      // DEBUG
      // cerr << "line: \"" << line << "\"\n";
      istringstream stream{line};
      string token{};
      vector<string> tokens{};
      while (getline(stream, token, ' ')) {
        tokens.push_back(token);
      }
      if (tokens.size() == 4) {
        int idx = stoi(tokens[0]);
        int left_idx = stoi(tokens[2]);
        int right_idx = stoi(tokens[3]);

        tree.add(idx, tokens[1], left_idx, right_idx);
      } else if (tokens.size() == 2) {

        tree.add(stoi(tokens[0]), tokens[1]);
      }
    }

    float submit = tree.calc();
    cout << "#" << test_case << " " << static_cast<int>(submit) << "\n";
  }

  return 0;
}