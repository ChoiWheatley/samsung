c++로 작성되어있음. CMakeLists.txt에 의해 빌드 시스템이 구축 되어있음. 빌드 방법은

1. `cmake -S . -B build`
2. `cd build`
3. `make`

파일 구조는 다음과 같다.

- problem
  - no{{n}}
    - `main.cc` : main 함수와 함께 입출력을 담당
    - `tests.cc` : GoogleTest에 기반한 테스트 코드
    - `solution.hpp` : 문제풀이를 위한 코드가 들어감.
- CMakeLists.txt

빌드 후 테스트 하는 방법은 다음과 같다.

1. `cd build`
2. `ctest -V`

빌드 후 메인 프로그램을 실행하는 방법은 다음과 같다. id는 main.cc가 들어있는 디렉토리의 이름과 동일하다.

1. `cd build/bin`
2. `./{{id}}_app.out`
