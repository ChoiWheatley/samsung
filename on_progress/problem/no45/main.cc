#include "solution.hpp"
#include <ios>
#include <iostream>

using std::cin;
using std::cout;
using std::ios;

using namespace sol2;

enum class Inst : uint { UPDATE = 0, SUM };

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  freopen("sample_in.txt", "r", stdin);

  uint t = 0;
  cin >> t;
  for (uint tc = 1; tc <= t; ++tc) {
    cout << "#" << tc << " ";

    uint n = 0;
    uint q = 0;
    cin >> n >> q;

    std::array<elem_t, N> data;

    // init
    for (uint i = 0; i < n; ++i) {
      elem_t e = 0;
      cin >> e;
      data[i] = e;
    }
    init(data, n);

    // queries
    for (uint i = 0; i < q; ++i) {
      uint inst;
      cin >> inst;
      switch (static_cast<Inst>(inst)) {
      case Inst::UPDATE: {
        uint idx = 0;
        elem_t value = 0;
        cin >> idx >> value;
        update(idx, value, n);
        break;
      }
      case Inst::SUM: {
        uint left = 0;
        uint right = 0;
        cin >> left >> right;

        elem_t submit = jagged_sum(left, right, n);
        cout << submit << " ";
        break;
      }
      }
    }

    cout << "\n";
  }
  return 0;
}