#ifndef SOLUTION
#define SOLUTION

#include <algorithm>
#include <array>
#include <functional>
#include <limits>
#include <map>
#include <stdexcept>
#include <string>

using std::array;
using std::string;

struct unknown_expression : std::exception {
  const char *what() const noexcept override { return "unknown_expression"; }
};
struct not_a_operator : std::exception {
  const char *what() const noexcept override { return "not_a_operator"; }
};
struct not_a_number : std::exception {
  const char *what() const noexcept override { return "not_a_float"; }
};
struct null_pointer_exception : std::exception {
  const char *what() const noexcept override {
    return "null pointer should not be detected!";
  }
};

const std::map<char, std::function<float(float, float)>> oper_mapper = {
    {'+', [](float a, float b) { return a + b; }},
    {'-', [](float a, float b) { return a - b; }},
    {'/', [](float a, float b) { return a / b; }},
    {'*', [](float a, float b) { return a * b; }}};

inline auto is_int(const string &s) -> bool {
  try {
    std::stoi(s);
    return true;
  } catch (std::invalid_argument e) {
    return false;
  }
}

inline auto is_operator(char c) -> bool {
  return oper_mapper.find(c) != oper_mapper.end();
}

struct Node {
  enum class Type { NUMBER, OPER };

  constexpr static size_t INVALID_IDX = std::numeric_limits<size_t>::max();

  const string data;
  const Type type;
  const size_t left = INVALID_IDX;
  const size_t right = INVALID_IDX;
  explicit Node(const string &data, Type type) : data{data}, type{type} {}
  explicit Node(const string &data, Type type, size_t left, size_t right)
      : data{data}, type{type}, left{left}, right{right} {}

  auto to_int() const -> int {
    if (type != Type::NUMBER) {
      throw not_a_number{};
    }
    return std::stoi(data);
  }

  auto to_oper() const -> std::function<float(float, float)> const & {
    if (type != Type::OPER) {
      throw not_a_operator{};
    }
    return oper_mapper.at(data[0]);
  }
};

template <size_t N = 1000> class BinTree {
public:
  void add(size_t idx, const string &data, size_t left_child,
           size_t right_child) {
    if (!is_operator(data[0])) {
      throw not_a_operator{};
    }
    m_tbl.at(idx) = new Node{data, Node::Type::OPER, left_child, right_child};
  }

  void add(size_t idx, const string &data) {
    // must be able to convert to number, or throws
    if (!is_int(data)) {
      throw not_a_number{};
    }
    m_tbl.at(idx) = new Node(data, Node::Type::NUMBER);
  }

  float calc() const { return calc_recur(m_tbl, 1); } // 1부터 시작함

private:
  array<Node *, N> m_tbl{};

  static float calc_recur(const array<Node *, N> &tbl, size_t idx) {
    if (idx >= tbl.size())
      throw unknown_expression{};
    if (tbl[idx] == nullptr) {
      throw null_pointer_exception{};
    }

    const Node *node = tbl[idx];
    if (node->type == Node::Type::NUMBER) {

      return static_cast<float>(node->to_int());

    } else if (node->type == Node::Type::OPER) {

      size_t left = node->left;
      size_t right = node->right;
      float result_left = calc_recur(tbl, left);
      float result_right = calc_recur(tbl, right);
      return node->to_oper()(result_left, result_right);

    } else {

      throw unknown_expression{};
    }
  }
};

#endif