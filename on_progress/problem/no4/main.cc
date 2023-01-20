#include "solution.hpp"
#include <iostream>

using sol2::CodeContainer;
using std::cin;
using std::cout;

class unknown_instruction {};

static auto instruction_parser(CodeContainer &cont, char inst) -> void {
  size_t x;
  size_t y;

  switch (inst) {

  case 'I': {
    /**
     * x의 위치 바로 다음에 y개의 stdin으로부터 입력받은 숫자를 삽입한다.
      테스트 케이스를 확인해 보니 스택처럼 순서가 뒤집혀 들어가는 게 아니라
     벡터처럼 들어가는 것을 확인했다.
     */
    cin >> x >> y;
    CodeContainer newbie{};
    code_t input = 0;
    while (y-- > 0) {
      std::cin >> input;
      newbie.add(input);
    }
    cont.insert_all(x, newbie);
    break;
  }

  case 'D': {
    /**
     * x의 위치 바로 다음에 y개의 숫자를 삭제한다.
     */
    cin >> x >> y;
    cont.del(x, y);
  } break;

  case 'A': {
    /** 맨 뒤에 y개의 stdin으로부터 입력받은 숫자를 삽입한다. */
    cin >> y;
    CodeContainer newbie{};
    code_t input = 0;
    while (y-- > 0) {
      std::cin >> input;
      newbie.add(input);
    }
    cont.add_all(newbie);
    break;
  }

  default:
    throw unknown_instruction{};
  }
}

int main(void) {
  std::ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  // DEBUG: 파일로 입력받기
  freopen("input.txt", "r", stdin);

  const int t = 10;

  for (int test_case = 1; test_case <= t; ++test_case) {

    CodeContainer cont{};

    /** n개의 원본 암호문 길이*/
    size_t n;
    cin >> n;
    while (n-- > 0) {
      code_t code = 0;
      cin >> code;
      cont.add(code);
    }

    /** m: 명령어의 개수 */
    size_t m;
    cin >> m;
    while (m-- > 0) {
      char inst = 0;
      cin >> inst;
      instruction_parser(cont, inst);
    }

    /** 수정된 암호문의 처음 10개 항을 출력한다. */
    cout << "#" << test_case << " ";
    auto iter = cont.begin();
    for (int i = 0; i < 10; ++i) {
      cout << iter->data << " ";
      iter = iter->next;
    }
    cout << "\n";
  }

  return 0;
}