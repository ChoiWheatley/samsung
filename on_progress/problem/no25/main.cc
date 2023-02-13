#include "solution.hpp"
#include <ios>
#include <iostream>
using std::cin;
using std::cout;
using std::ios;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // freopen("sample_input-5.txt", "r", stdin);

  size_t t = 0;
  cin >> t;

  for (size_t tc = 1; tc <= t; ++tc) {

    size_t n = 0;
    elem_t mid = 0;
    cin >> n >> mid;

    auto sol = Solution{mid};
    unsigned int submit = 0;

    while (n-- > 0) {
      elem_t a = 0;
      elem_t b = 0;
      cin >> a >> b;
      submit = (submit + sol.add(a, b)) % MOD;
    }

    cout << "#" << tc << " " << submit << "\n";
  }

  return 0;
}