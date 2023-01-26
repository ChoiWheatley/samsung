#ifndef SOLUTION
#define SOLUTION

#include <cstring>
#include <exception>
#include <functional>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999

using std::map;
using std::string;
using std::stringstream;

constexpr size_t MAX_N = 50000;

struct Directory;
auto compare(Directory *a_ptr, Directory const *b_ptr) -> bool;

struct Directory {
  string name;
  string full_name;
  // name 끼리 비교하기 위한 몸부림
  map<string, Directory *, std::less<>> children{};

  explicit Directory() = default;
  explicit Directory(std::string name) : name(std::move(name)) {}

  auto operator==(const Directory &o) const { return name == o.name; };
  auto operator<(const Directory &o) const { return name < o.name; };
};

inline auto compare(Directory const *a_ptr, Directory const *b_ptr) -> bool {
  return a_ptr->name < b_ptr->name;
}

namespace err {
struct dir_not_found : std::exception {
  explicit dir_not_found() = default;
  explicit dir_not_found(const char raw_string[]) : desc(raw_string){};
  const char *what() const noexcept override {
    auto *ret = new char[100];
    std::strcat(ret, "directory cannot be found! :: ");
    std::strcat(ret, desc);
    return ret;
  }

private:
  const char *desc;
};

struct cache_out_of_bounds : std::exception {
  const char *what() const noexcept override { return "cache size exceeds!"; }
};

struct no_parent : std::exception {
  const char *what() const noexcept override {
    return "parent is null when new_dir";
  }
};

} // namespace err

template <class Consumer>
auto foreach_token(const string &glob, char delim, Consumer const &consumer) {
  stringstream stream{glob};
  string token = "";
  while (std::getline(stream, token, delim)) {
    consumer(token);
  }
}

inline auto last_token(const string &glob, char delim)
    -> std::pair<decltype(glob.begin()), decltype(glob.end())> {
  auto itr = glob.rbegin();
  auto end = glob.rbegin();
  if (*glob.rbegin() == delim) { // strip the last deilm
    itr++;
    end++;
  }

  for (; itr != glob.rend() && *itr != delim; itr++)
    ;
  return {itr.base(), end.base()};
}

class DirectoryController {
public:
  explicit DirectoryController() {
    root->name = "/";
    root->full_name = root->name;
    m_fullname_cache.insert({root->name, root});
  };

  /**
  @arg
    - path: '/' delimetered string indicates path of directories
    - trace: callback function which calls whenever iterates through tree
  @return
    - nullptr: if no directory is not found in path
    - pointer: if directory is found in path
  */
  template <class Consumer>
  auto get(const string &path, const Consumer &trace) -> Directory * {
    Directory *cur = root;
    foreach_token(path, '/', [&cur, &trace](string const &token) {
      if (cur == nullptr) {
        return;
      }
      if (!token.empty()) {
        auto iter = cur->children.find(token);
        if (iter == cur->children.end()) { // not found
          cur = nullptr;
        } else {
          trace(cur);
          cur = iter->second;
        }
      }
      return;
    });
    return cur;
  }

  /**
      returns: pointer of directory (Nullable)
      args:
      - path: '/' delimetered string indicates path of directories
   */
  auto get(const string &path) -> Directory * {
    return get<>(path,
                 []([[maybe_unused]] Directory const *cur) { /*do nothing*/ });
  }

  auto get_full_path(const string &path) -> Directory * {
    auto itr = m_fullname_cache.find(path);
    if (itr == m_fullname_cache.end()) {
      throw err::dir_not_found{path.c_str()};
    }
    return itr->second;
  }

  /**
  path 디렉터리의 하위에 name 이름을 가진 새로운 디렉터리를 생성한다.
  */
  auto cmd_mkdir(const string &path, string &&name) -> Directory * {
    string full_path = path + name + "/";
    Directory *parent = get_full_path(path);
    Directory *newbie = new_dir(std::move(name), parent);

    parent->children.insert({newbie->name, newbie});
    m_fullname_cache.insert({full_path, newbie});

    return newbie;
  }

  /**
  path 디렉터리와 그 모든 하위 디렉터리를 삭제한다.
  */
  auto cmd_rm(const string &path) -> void {
    if (path == "/") {
      return; // cannot delete root
    }

    auto last_token_itr = last_token(path, '/');
    string parent_path =
        path.substr(0, std::distance(path.cbegin(), last_token_itr.first));

    // cur의 모든 자식들을 삭제한다.
    Directory *cur = get_full_path(path);
    Directory *parent = get_full_path(parent_path);
    rm_recur(cur);
    // 마침내 cur를 삭제한다.
    parent->children.erase(cur->name);
    m_fullname_cache.erase(path);

    delete cur;
  }

  /**
  dst_path의 하위에 src_path의 디렉터리와 그 모든 하위 디렉터리들을 복사한다.
  */
  auto cmd_cp(const string &src_path, const string &dst_path) {
    Directory *dst = get_full_path(dst_path);
    Directory const *src = get_full_path(src_path);
    Directory *clone = cp_recur(src, string{dst_path});
    dst->children.insert({clone->name, clone});
  }

  /**
  dstPath 디렉터리의 하위에 srcPath 의 디렉터리와 그 모든 하위 디렉터리를
  이동한다.
  */
  auto cmd_mv(const string &src_path, const string &dst_path) {
    auto last_token_rng = last_token(src_path, '/');
    string parent_path = src_path.substr(
        0, std::distance(src_path.cbegin(), last_token_rng.first));

    Directory *dst = get_full_path(dst_path);
    Directory *src = get_full_path(src_path);

    // remove from cache
  }

  /**
  path 디렉터리의 모든 하위 디렉터리 개수를 반환한다.
  */
  auto cmd_find(const string &src_path) -> int {
    Directory const *src = get_full_path(src_path);
    int count = 0;
    for (auto const &child : src->children) {
      count += count_recur(child.second);
    }
    return count;
  }

private:
  auto new_dir(string &&name, Directory const *parent) -> Directory * {
    if (parent == nullptr) {
      throw err::no_parent{};
    }
    auto *ret = new Directory(std::move(name));
    ret->full_name = parent->full_name + ret->name + "/";
    return ret;
  }

  /** 먼저 자식들에게 재귀적으로 삭제 메시지를 보낸 후에 비로소 자신의 자식과
   * 연결을 끊는다. */
  auto rm_recur(Directory *dir) -> void {
    for (auto child : dir->children) {
      rm_recur(child.second);
    }
    do_rm(dir);
  }

  /** dir의 자식을 제거한다. */
  auto do_rm(Directory *dir) -> void {
    // fullname_cache를 일괄적으로 삭제함.
    for (auto const &elem : dir->children) {
      auto itr = m_fullname_cache.find(elem.second->full_name);
      m_fullname_cache.erase(itr);
    }
    dir->children.clear();
  }

  /**
  target과 그 하위 디렉토리들을 모두 복제한 새 디렉토리를 리턴한다.
  */
  auto cp_recur(Directory const *target, string &&full_path) -> Directory * {
    Directory *newbie = cmd_mkdir(full_path, string{target->name});
    for (auto const &child : target->children) {
      string child_path = full_path + target->name + "/";
      cp_recur(child.second, std::move(child_path));
    }
    return newbie;
  }

  static auto count_recur(Directory const *dir) -> int {
    int cnt = 1;
    for (auto const &child : dir->children) {
      cnt += count_recur(child.second);
    }
    return cnt;
  }

  Directory *root = new Directory("/");
  map<string, Directory *, std::less<>> m_fullname_cache; // "/a/b/c/"
};

static DirectoryController dc;

/** 그냥 동적할당 쌔림 */
void init(int n) { dc = DirectoryController{}; }

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
  dc.cmd_mkdir(string{path}, string{name});
}

void cmd_rm(char path[PATH_MAXLEN + 1]) { dc.cmd_rm(string{path}); }

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
  dc.cmd_cp(string{srcPath}, string{dstPath});
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
  dc.cmd_mv(string{srcPath}, string{dstPath});
}

int cmd_find(char path[PATH_MAXLEN + 1]) { return dc.cmd_find(string{path}); }

#endif