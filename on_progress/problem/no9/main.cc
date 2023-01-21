#include "solution.hpp"
#include <cstdio>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::stringbuf;

int main(void) {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  // DEBUG
  freopen("input.txt", "r", stdin);

  constexpr size_t t = 10;
  for (size_t test_case = 1; test_case <= t; ++test_case) {

    int n;
    cin >> n;
    cin.ignore(); // ignore return char
    vector<char> bintree;
    while (n-- > 0) {
      std::string line;
      std::getline(cin, line);
      std::istringstream ss{line};
      int i;
      char c;
      ss >> i >> c;
      bintree.push_back(c);
    }
    bool submit = solution(bintree);
    cout << "#" << test_case << " " << (submit ? 1 : 0) << "\n";
  }

  return 0;
}