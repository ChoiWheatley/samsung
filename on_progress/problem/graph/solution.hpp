#ifndef SOLUTION
#define SOLUTION

#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

using std::pair;
using std::vector;
using edge_t = pair<int, int>; // first = 정점1, second = 정점2

/**
가장 널리 알려진 2d 벡터를 사용한 그래프 구현법
*/
inline auto ver_2_1(int n, vector<edge_t> const &edges) -> vector<vector<int>> {

  // data
  vector<vector<int>> graph{size_t(n)};
  // build
  for (auto const &e : edges) {
    graph[e.first].emplace_back(e.second); // 찾을 땐 graph[i][j] 하면 끝.
  }
  return graph;
}

struct Node2 {
  int id;
  int next;
};

/**
  # 연결리스트로 그래프를 구현하는 방법.
  ## 사용법
    - i와 연결된 정점들을 찾고싶다 => nodes[head[i]].id가 첫번째 인접노드
    - nodes[head[i]].next를 다시 nodes의 인덱스에 넣으면 다음 인접노드.
    - until next is -1
  ## 장점: 메모리 낭비없이 사용가능.
  ## 단점:
    - 가독성이 떨어짐
    - 연결리스트를 배열에 넣었기 때문에 중간 삽입, 삭제가 불편함
    - 여러번 점프를 해야 하기 때문에 배열보다 느림.
  @return
    - nodes : 연결리스트. id가 정점번호이고 next는 형제노드
    - head : 인덱스가 각 정점의 번호. 인접 노드로 가는 첫 번째 nodes 인덱스를
  가리킴.
*/
inline auto ver_2_2(int n, vector<edge_t> const &edges)
    -> pair<vector<Node2> /*nodes*/, vector<int> /*head*/> {

  // -1로 초기화하는 이유는 아직 아무도 연결이 안 되었기 때문.
  auto head = vector<int>{n, int(-1)};
  auto node = vector<Node2>{edges.size()};

  for (size_t i = 0; i < edges.size(); ++i) {
    auto const &edge = edges[i];
    node[i].id = edge.second; // i의 인접노드번호
    node[i].next = head[edge.first]; // 마지막으로 가리켰던 head를 가리키게
    head[edge.first] = static_cast<int>(i); // head[i]가 자신을 가리키게
  }

  return {node, head};
}

#endif