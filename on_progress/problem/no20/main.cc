#include "solution.hpp"
#include <ios>
#include <iostream>

using namespace std;
using namespace sol2;

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  size_t t = 0;
  cin >> t;
  for (size_t tc = 1; tc <= t; ++tc) {
    string s1;
    string s2;
    cin >> s1 >> s2;
    auto submit = solution(std::move(s1), std::move(s2));

    cout << "#" << tc << " " << submit << "\n";
  }
  return 0;
}