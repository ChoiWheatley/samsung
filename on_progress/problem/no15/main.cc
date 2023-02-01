#include "solution.hpp"
#include <cstdio>
#include <ios>
#include <iostream>
#include <vector>

using node::idx_t;
using std::cin;
using std::cout;
using std::vector;
using namespace sol2;

int main(void) {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  freopen("sample_input.txt", "r", stdin);

  size_t t;
  cin >> t;

  for (size_t tc = 1; tc <= t; ++tc) {

    size_t n;
    cin >> n;
    vector<node::idx_t> data{};

    n--;
    while (n-- > 0) {
      idx_t elem;
      cin >> elem;
      data.emplace_back(elem);
    }

    auto submit = solution(data);

    cout << "#" << tc << " " << submit << "\n";
  }
}