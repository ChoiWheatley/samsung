#include "solution.hpp"
#include <cstdint>
#include <cstdio>
#include <ios>
#include <iostream>

struct LessEq {
  auto operator()(int a, int b) const { return a < b; }
};

int main(void) {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  freopen("sample_input-4.txt", "r", stdin);

  size_t t = 0;
  std::cin >> t;

  for (size_t tc = 1; tc <= t; ++tc) {
    Heap<int, LessEq> heap{};
    size_t n = 0;
    std::cin >> n;
    std::cout << "#" << tc << " ";

    while (n-- > 0) {

      size_t instruction = 0;
      std::cin >> instruction;

      if (instruction == 1) {
        int item;
        std::cin >> item;
        heap.insert(item);
      } else if (instruction == 2) {
        auto item = heap.peek();
        heap.pop();

        if (item.state == State::Err) {
          std::cout << "-1 ";
        } else {
          std::cout << item.retval << " ";
        }
      }
    }

    std::cout << "\n";
  }

  return 0;
}