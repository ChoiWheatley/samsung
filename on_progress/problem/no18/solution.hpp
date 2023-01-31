#ifndef SOLUTION
#define SOLUTION

using size_t = unsigned long;

class Node {
public:
  static constexpr size_t MAX_CHILD = 5;
  int id = 0;
  auto push_back(Node *node) {
    children[top] = node;
    top++;
  }
  auto size() const noexcept -> size_t { return top; }
  auto at(size_t idx) const noexcept -> Node const * { return children[idx]; }

private:
  size_t top = 0;
  Node *children[MAX_CHILD];
};

static constexpr size_t MAX_ID = 101;
static Node memory_pool[MAX_ID];

static void pool_init() {
  for (int i = 0; i < MAX_ID; ++i) {
    memory_pool[i] = Node{};
    memory_pool[i].id = i;
  }
}

void dfs_init(int N, int path[100][2]) {
  pool_init();
  for (size_t i = 0; i < N - 1; ++i) {
    const int father_id = path[i][0];
    const int son_id = path[i][1];
    memory_pool[father_id].push_back(&memory_pool[son_id]);
  }
}

/** node 서브트리의 자식을 dfs로 재귀적으로 순회한다. */
template <class UnaryFunc>
static bool dfs_recur(Node const *node, UnaryFunc const &unary_fn) {
  if (unary_fn(node->id)) {
    // 주어진 조건을 만족하면 더 이상 순회하지 않는다.
    return true;
  }
  for (size_t i = 0; i < node->size(); ++i) {
    Node const *child = node->at(i);
    if (dfs_recur(child, unary_fn)) {
      return true;
    }
  }
  return false;
}

int dfs(int n) {
  auto root = &memory_pool[n];
  auto min = -1;
  dfs_recur(root, [root, &min](decltype(Node::id) id) {
    if (root->id < id) {
      min = id;
      return true;
    }
    return false;
  });
  return min;
}

#endif