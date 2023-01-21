#ifndef SOL
#define SOL

#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::stringstream;
using std::vector;

struct Node {
  const char data;
  Node *left = nullptr;
  Node *right = nullptr;
  explicit Node(char data) : data{data} {};
};

static auto make_tree_recur(const vector<char> &bin_tree, size_t idx)
    -> Node * {
  if (idx >= bin_tree.size()) {
    return nullptr;
  }
  auto ret = new Node{bin_tree[idx]};
  ret->left = make_tree_recur(bin_tree, idx * 2 + 1); // index count from 0
  ret->right = make_tree_recur(bin_tree, idx * 2 + 2);
  return ret;
}

static auto traverse_recur(Node *sub_tree, stringstream &stream_out) -> void {
  if (sub_tree == nullptr) {
    return;
  }
  traverse_recur(sub_tree->left, stream_out);
  stream_out << sub_tree->data;
  traverse_recur(sub_tree->right, stream_out);
}

/** 중위순회 결과를 string에 담아 출력한다. */
inline string solution(vector<char> &&bin_tree) {
  stringstream ss;
  Node *root = make_tree_recur(bin_tree, 0);
  traverse_recur(root, ss);
  return ss.str(); // potential memory leak `root`
}

#endif