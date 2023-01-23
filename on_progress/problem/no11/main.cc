#include "solution.hpp"
#include <cstdio>
#include <ios>
#include <iostream>

using std::cin;
using std::cout;
using std::ios_base;

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  // DEBUG
  std::freopen("input.txt", "r", stdin);

  size_t t;
  cin >> t;
  for (size_t test_case = 1; test_case <= t; ++test_case) {

    mykey_t vertices;
    size_t edges;
    mykey_t v1;
    mykey_t v2;
    cin >> vertices >> edges >> v1 >> v2;

    BinTree tree{vertices};
    while (edges-- > 0) {

      mykey_t parent;
      mykey_t child;
      cin >> parent >> child;
      tree.set_child(parent, child);
    }

    Node const *common_ancestor = tree.common_ancestor(v1, v2);
    cout << "#" << test_case << " " << common_ancestor->key << " "
         << common_ancestor->get_size() << "\n";
  }

  return 0;
}