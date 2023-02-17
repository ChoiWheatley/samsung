#include "solution.hpp"
#include <ios>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::ios;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  size_t t;
  cin >> t;

  for (size_t tc = 1; tc <= t; ++tc) {

    string str;
    string pat;
    cin >> str >> pat;

    size_t submit = solution(str, pat);

    cout << "#" << tc << " " << submit << "\n";
  }

  return 0;
}