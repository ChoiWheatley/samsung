#include "solution.hpp"
#include <cstdio>
#include <iostream>

using sol::MyContainer;
using std::cin;
using std::cout;

struct unknown_inst_err {};

MyContainer &&inst_parser(MyContainer &&cont, char inst) {

  size_t x;
  data_t y;
  switch (inst) {
  case 'I': { // I x y : x번 인덱스 앞에 y를 추가하고 한 칸씩 뒤로 이동
    cin >> x >> y;
    cont.insert_at(x, y);
    break;
  }
  case 'D': { // D x : x번 인덱스 자리를 지우고 한 칸씩 앞으로 이동
    cin >> x;
    cont.delete_at(x);
    break;
  }
  case 'C': { // C x y : x번 인덱스 자리를 y로 바꾼다.
    cin >> x >> y;
    cont.change_at(x, y);
    break;
  }
  default:
    throw unknown_inst_err{};
  }

  return std::move(cont);
}

int main(void) {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  // DEBUG
  // std::freopen("sample_input.txt", "r", stdin);

  size_t t;
  cin >> t;

  for (size_t test_case = 1; test_case <= t; ++test_case) {
    size_t n; // 초기 수열의 길이
    size_t m; // 명령어 개수
    size_t l; // 출력할 인덱스 번호
    cin >> n >> m >> l;

    data_t input;
    MyContainer cont{};
    // 초기 수열
    while (n-- > 0) {
      cin >> input;
      cont.add(input);
    }

    // 명령어들
    char inst;
    while (m-- > 0) {
      cin >> inst;
      cont = inst_parser(std::move(cont), inst);
    }

    // 결과물 출력
    auto iter = cont.begin();
    size_t cnt = 0;
    for (; cnt < l && iter != cont.end(); iter = iter->next) {
      cnt++;
    }
    cout << "#" << test_case << " ";
    if (cnt == l) {
      cout << iter->data << "\n";
    } else {
      cout << -1 << "\n";
    }
  }
  return 0;
}