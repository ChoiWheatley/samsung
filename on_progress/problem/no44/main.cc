#include "solution.hpp"
#include <ios>
#include <iostream>

using std::cin;
using std::cout;
using std::ios;

enum class Inst { SET = 0, PRINT };

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  freopen("sample_in.txt", "r", stdin);

  size_t t = 0;
  cin >> t;

  for (size_t tc = 1; tc <= t; ++tc) {
    cout << "#" << tc << " ";

    uint n = 0;
    uint q = 0;
    cin >> n >> q;
    uint data[N] = {0};

    // init data
    for (uint i = 0; i < n; ++i) {
      cin >> data[i];
    }

    init(data, n);

    // queries
    for (uint i = 0; i < q; ++i) {
      int inst = -1;
      uint param1 = 0;
      uint param2 = 0;
      cin >> inst >> param1 >> param2;

      if (inst == int(Inst::SET)) {
        set(param1, param2, n);
      } else if (inst == int(Inst::PRINT)) {
        auto max = max_between(param1, param2, n);
        auto min = min_between(param1, param2, n);

        cout << max - min << " ";
      }
    }
    cout << "\n";
  }

  return 0;
}