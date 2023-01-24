#include "solution.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

TEST(Getline, delim) {
  string path = "/a/b/c/";
  std::vector<string> answer = {"a", "b", "c"};
  std::vector<string> submit = {};

  std::stringstream stream{path};
  string token;
  stream.ignore(1);
  while (std::getline(stream, token, '/')) {
    submit.push_back(token);
  }

  ASSERT_EQ(answer, submit);
}

TEST(MKDIR, 1) {
  DirectoryController dir{MAX_N};
  dir.cmd_mkdir("/", "hello");
  dir.cmd_mkdir("/hello/", "my");
  dir.cmd_mkdir("/hello/my/", "name");
  dir.cmd_mkdir("/hello/my/name", "is");
  dir.cmd_mkdir("/hello/my/name/is", "choi");
  dir.cmd_mkdir("/hello/my/name/is", "park");
  ASSERT_EQ(6, dir.cmd_find("/"));
  ASSERT_EQ(2, dir.cmd_find("/hello/my/name/is/"));
}

TEST(RMDIR, 1) {
  DirectoryController dir{MAX_N};
  dir.cmd_mkdir("/", "hello");
  ASSERT_EQ(1, dir.cmd_find("/"));
  dir.cmd_rm("/hello/");
  ASSERT_EQ(0, dir.cmd_find("/"));
  dir.cmd_mkdir("/", "hello");
  dir.cmd_mkdir("/", "hello2");
  dir.cmd_mkdir("/", "hello3");
  dir.cmd_mkdir("/", "hello4");
  dir.cmd_mkdir("/hello/", "my");
  dir.cmd_mkdir("/hello/my/", "name");
  dir.cmd_mkdir("/hello/my/name", "is");
  dir.cmd_mkdir("/hello/my/name/is", "choi");
  dir.cmd_mkdir("/hello/my/name/is", "park");
  ASSERT_EQ(9, dir.cmd_find("/"));
  dir.cmd_rm("/hello/");
  ASSERT_EQ(3, dir.cmd_find("/"));
  ASSERT_THROW(dir.cmd_find("/hello/my/name/is/choi"),
               decltype(dir_not_found{}));
}

TEST(CP, 1) {
  DirectoryController dir{MAX_N};
  dir.cmd_mkdir("/", "hello");
  dir.cmd_mkdir("/hello/", "my");
  dir.cmd_mkdir("/hello/my/", "name");
  dir.cmd_mkdir("/hello/my/name", "is");
  dir.cmd_mkdir("/hello/my/name/is", "choi");
  dir.cmd_mkdir("/hello/my/name/is", "park");

  dir.cmd_mkdir("/", "hello2");
  dir.cmd_cp("/hello/my", "/hello2/");
  ASSERT_EQ(0, dir.cmd_find("/hello2/my/name/is/choi"));
  ASSERT_EQ(0, dir.cmd_find("/hello2/my/name/is/park"));
  ASSERT_EQ(0, dir.cmd_find("hello/my/name/is/choi"));
  ASSERT_EQ(0, dir.cmd_find("/hello/my/name/is/park"));
}

TEST(MV, 1) {
  DirectoryController dir{MAX_N};
  dir.cmd_mkdir("/", "hello");
  dir.cmd_mkdir("/hello/", "my");
  dir.cmd_mkdir("/hello/my/", "name");
  dir.cmd_mkdir("/hello/my/name", "is");
  dir.cmd_mkdir("/hello/my/name/is", "choi");
  dir.cmd_mkdir("/hello/my/name/is", "park");

  dir.cmd_mkdir("/", "hello2");
  dir.cmd_mv("/hello/my", "/hello2/");
  ASSERT_EQ(0, dir.cmd_find("/hello2/my/name/is/choi"));
  ASSERT_EQ(0, dir.cmd_find("/hello2/my/name/is/park"));
  ASSERT_THROW(dir.cmd_find("/hello/my"), decltype(dir_not_found{}));
}

TEST(SOL, 1) {
  DirectoryController dir{MAX_N};
  dir.cmd_mkdir("/", "aa");
  dir.cmd_mkdir("/", "bb");
  dir.cmd_mkdir("/aa/", "cc");
  dir.cmd_mkdir("/bb/", "dd");
  dir.cmd_cp("/bb/", "/aa/");
  dir.cmd_mv("/aa/cc/", "/");
  ASSERT_EQ(6, dir.cmd_find("/"));
}

namespace Timeout {

constexpr size_t MAX = 5000;

TEST(Timeout, 1) {
  DirectoryController dir{MAX};
  string concater = "/";
  for (size_t i = 0; i < MAX; ++i) {
    dir.cmd_mkdir(concater, std::to_string(i));
    concater += std::to_string(i) + "/";
  }
}

TEST(Timeout, 2) {
  string path = "/";
  Directory root{path};
  for (size_t i = 0; i < MAX; ++i) {
    // 1. find dir* from tokenized path
    std::stringstream stream{path};
    string token = "";

    Directory *cur = &root;
    if (stream.peek() == '/') {
      stream.ignore(1);
    }
    while (std::getline(stream, token, '/')) {
      auto iter = cur->children.find(token);
      if (iter == cur->children.end()) {
        return;
      }
      cur = iter->second;
    }

    // 2. add new child from leaf node
    auto newname = std::to_string(i);
    auto *newbie = new Directory(newname);
    cur->children.emplace(newbie->name, newbie);
    path += newname + "/";
  }
}

} // namespace Timeout

namespace MAP_TEST {
static constexpr size_t MAX = 100000;

TEST(Map, Timeout1) {
  std::map<string, Directory *> tmp_map;

  for (size_t i = 0; i < MAX; ++i) {
    auto str = std::to_string(i);
    tmp_map.insert(std::make_pair(str, new Directory(str)));
  }
}
TEST(Map, Timeout2) {
  std::map<string, Directory *> tmp_map;

  for (size_t i = 0; i < MAX; ++i) {
    auto str = std::to_string(i);
    tmp_map.insert({str, new Directory(str)});
  }
}
TEST(Map, Timeout3) {
  std::map<string, Directory *> tmp_map;

  for (size_t i = 0; i < MAX; ++i) {
    auto str = std::to_string(i);
    auto iter = tmp_map.emplace(str, new Directory(str));
  }
}
TEST(Map, Timeout4) {
  std::map<string, Directory *> tmp_map;

  for (size_t i = 0; i < MAX; ++i) {
    auto str = std::to_string(i);
    auto newbie = new Directory(str);
    auto ret = tmp_map.insert({str, newbie});
    if (!ret.second) { // key 중복이라면
      ret.first->second = newbie;
    }
  }
}
} // namespace MAP_TEST