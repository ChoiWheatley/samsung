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
#include <vector>

#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999

using std::map;
using std::string;
using std::stringstream;
using std::unique_ptr;
using std::vector;

constexpr size_t MAX_N = 50000;

struct Directory {
  string name;
  // name 끼리 비교하기 위한 몸부림
  map<string, Directory *> children{};

  explicit Directory() = default;
  explicit Directory(std::string name) : name(std::move(name)) {}

  auto operator==(const Directory &o) const { return name == o.name; };
  auto operator<(const Directory &o) const { return name < o.name; };
};

inline bool operator<(const Directory &a, const Directory &b) {
  return a.name < b.name;
}

struct dir_not_found : std::exception {
  explicit dir_not_found() = default;
  explicit dir_not_found(const char *raw_string) : desc(raw_string){};
  const char *what() const noexcept override {
    auto *ret = new char[100];
    std::strcat(ret, "directory cannot be found! :: ");
    std::strcat(ret, desc);
    return ret;
  }

private:
  const char *desc;
};

template <class Consumer>
auto foreach_token(const string &glob, char delim, Consumer const &consumer) {
  stringstream stream{glob};
  string token = "";
  while (std::getline(stream, token, delim)) {
    consumer(token);
  }
}

class DirectoryController {
public:
  explicit DirectoryController() = default;
  explicit DirectoryController(size_t size) : cache{size * 2, Directory()} {
    root = &cache[cache_top];
    cache_top += 1;
    root->name = "/";
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
    foreach_token(path, '/', [&](string const &token) {
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

  /**
  path 디렉터리의 하위에 name 이름을 가진 새로운 디렉터리를 생성한다.
  */
  auto cmd_mkdir(const string &path, string &&name) -> void {
    Directory *cur = get(path);
    if (cur == nullptr) {
      throw dir_not_found(path.c_str());
    }
    Directory *newbie = new_dir(std::move(name));
    cur->children.emplace(newbie->name, newbie);
  }

  /**
  path 디렉터리와 그 모든 하위 디렉터리를 삭제한다.
  */
  auto cmd_rm(const string &path) -> void {
    Directory *cur = root;
    Directory *parent = nullptr;
    cur = get<>(path, [&parent](Directory *p) { parent = p; });
    if (cur == nullptr) {
      throw dir_not_found{path.c_str()};
    }
    rm_recur(cur);
    // 마침내 parent의 자식 중 cur를 삭제한다.
    parent->children.erase(cur->name);
  }

  /**
  dst_path의 하위에 src_path의 디렉터리와 그 모든 하위 디렉터리들을 복사한다.
  */
  auto cmd_cp(const string &src_path, const string &dst_path) {
    Directory *dst = get(dst_path);
    Directory const *src = get(src_path);
    if (dst == nullptr) {
      throw dir_not_found{dst_path.c_str()};
    }
    if (src == nullptr) {
      throw dir_not_found{src_path.c_str()};
    }
    Directory *clone = cp_recur(src);
    dst->children.emplace(clone->name, clone);
  }

  /**
  dstPath 디렉터리의 하위에 srcPath 의 디렉터리와 그 모든 하위 디렉터리를
  이동한다.
  */
  auto cmd_mv(const string &src_path, const string &dst_path) {
    Directory *dst = get(dst_path);
    Directory *src_parent = nullptr;
    Directory *src =
        get(src_path, [&src_parent](Directory *ptr) { src_parent = ptr; });
    if (dst == nullptr) {
      throw dir_not_found{dst_path.c_str()};
    }
    if (src == nullptr) {
      throw dir_not_found{src_path.c_str()};
    }
    dst->children.emplace(src->name, src);
    src_parent->children.erase(src->name);
  }

  /**
  path 디렉터리의 모든 하위 디렉터리 개수를 반환한다.
  */
  auto cmd_find(const string &src_path) -> int {
    Directory const *src = get(src_path);
    if (src == nullptr) {
      throw dir_not_found{src_path.c_str()};
    }
    int count = 0;
    for (auto const &child : src->children) {
      count += count_recur(child.second);
    }
    return count;
  }

private:
  vector<Directory> cache{MAX_N, Directory()};
  Directory *root = &cache[0];
  size_t cache_top = 1;
  map<string, Directory *> m_full_path_map;

  auto new_dir(string &&name) -> Directory * {
    if (cache_top >= cache.size()) {
      cache.reserve(cache.size() * 2);
    }
    Directory &ret = cache[cache_top];
    cache_top++;
    ret.name = std::move(name);
    return &ret;
  }

  /** 실제로 자원을 반납하지는 않을 예정. 먼저 자식들에게 재귀적으로 삭제
   * 메시지를 보낸 후에 비로소 자신의 자식과 연결을 끊는다. */
  static auto rm_recur(Directory *dir) -> void {
    for (auto child : dir->children) {
      rm_recur(child.second);
    }
    dir->children.clear();
  }

  /**
  target과 그 하위 디렉토리들을 모두 복제한 새 디렉토리를 리턴한다.
  */
  auto cp_recur(Directory const *target) -> Directory * {
    Directory *newbie = new_dir(string{target->name});
    for (auto const &child : target->children) {
      Directory *clone = cp_recur(child.second);
      newbie->children.emplace(clone->name, clone);
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
};

static DirectoryController dc{};

void init(int n) { dc = DirectoryController{static_cast<size_t>(n)}; }

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