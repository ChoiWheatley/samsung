#include "solution.hpp"
#include <gtest/gtest.h>
#include <sstream>
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
  DirectoryController dir{100};
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
  DirectoryController dir{100};
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
  DirectoryController dir{100};
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
  DirectoryController dir{100};
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
  DirectoryController dir{11};
  dir.cmd_mkdir("/", "aa");
  dir.cmd_mkdir("/", "bb");
  dir.cmd_mkdir("/aa/", "cc");
  dir.cmd_mkdir("/bb/", "dd");
  dir.cmd_cp("/bb/", "/aa/");
  dir.cmd_mv("/aa/cc/", "/");
  ASSERT_EQ(6, dir.cmd_find("/"));
}