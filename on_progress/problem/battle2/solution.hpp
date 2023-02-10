#ifndef SOLUTION
#define SOLUTION

#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <list>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using std::array;
using std::set;
using std::string;
using std::unordered_map;

constexpr size_t MAX_N = 25;
constexpr size_t NAME_LEN = 11;

struct idx_t {
  int16_t r;
  int16_t c;
  constexpr explicit idx_t(int16_t r = 0, int16_t c = 0) : r{r}, c{c} {}
  constexpr auto get_hash() const { return r * MAX_N + c; }
};
inline auto operator==(idx_t a, idx_t b) { return a.r == b.r && a.c == b.c; }
inline auto operator!=(idx_t a, idx_t b) { return !(a == b); }
inline auto operator<(idx_t a, idx_t b) {
  if (a.r == b.r) {
    return a.c < b.c;
  }
  return a.r < b.r;
}
namespace std {
template <> struct hash<idx_t> {
  size_t operator()(const idx_t &x) const { return x.get_hash(); }
};
} // namespace std

struct Monarch {
  idx_t index;
  string name;
  int soldier;
};

enum class Rel { NEUTRAL = 0, ALLIANCE, ENEMY };

class Releam {
  template <typename T, size_t Size>
  using array2d_t = array<array<T, Size>, Size>;

  array2d_t<Monarch, MAX_N> m_releam;
  /**동맹관계를 저장하는 그래프*/
  array<set<idx_t>, MAX_N * MAX_N> m_allies;
  /**대적관계를 저장하는 그래프*/
  array<set<idx_t>, MAX_N * MAX_N> m_enemies;
  /**string을 바로 인덱스로 바꾸기 위한 공간*/
  unordered_map<string, idx_t> m_name_cache;

  const int N;

  static auto subscript(decltype(m_releam) &arr2d, idx_t index) -> Monarch & {
    return arr2d[index.r][index.c];
  }

public:
  explicit Releam(int N, int mSoldier[MAX_N][MAX_N],
                  char mMonarch[MAX_N][MAX_N][NAME_LEN])
      : N{N} {
    for (decltype(idx_t::r) r = 0; r < N; ++r) {
      for (decltype(idx_t::c) c = 0; c < N; ++c) {
        auto &target = m_releam[r][c];
        target.index = idx_t{r, c};
        target.name = string{mMonarch[r][c]};
        target.soldier = mSoldier[r][c];

        m_name_cache.insert({target.name, target.index});
      }
    }
  }

  auto str_to_idx(string const &name) -> idx_t {
    return m_name_cache.find(name)->second;
  }

  auto at(idx_t pos) -> Monarch & { return subscript(m_releam, pos); }

  auto at(string const &name) -> Monarch & { return at(str_to_idx(name)); }

  auto is_ally(idx_t a, idx_t b) const {
    auto l_set = m_allies.at(a.get_hash());
    return l_set.find(b) != l_set.end();
  }

  /**
  a의 동맹과 b의 동맹간에 적대관계가 있는경우
  */
  auto is_enemy(idx_t a, idx_t b) const {
    auto allies = m_allies.at(a.get_hash());
    auto enemies = m_enemies.at(a.get_hash());
    for (auto const &i : allies) {
      for (auto const &j : enemies) {
        for (auto const &enemy : m_allies.at(j.get_hash())) {
          if (i == enemy) {
            return true;
          }
        }
      }
    }
    return false;
  }

  /**
  이미 동맹관계이면 -1을, a의 동맹과 b의 동맹간에 적대관계가
  있으면 -2를 반환한다. 위의 두 경우가 아니라면 동맹관계가 맺어지고 1을
  반환한다.
  */
  auto ally(idx_t a, idx_t b) -> int {
    auto enemy_rel = m_enemies.at(a.get_hash());
    auto ally_rel = m_allies.at(a.get_hash());
    if (is_enemy(a, b)) {
      return -2;
    }
    if (is_ally(a, b) || a == b) {
      return -1;
    }
    ally_rel.insert(b);
    return 1;
  }

  /**
  target과 관련한 모든 연결을 끊는다.
  */
  auto del_ln(idx_t target) {
    m_enemies.at(target.get_hash()).clear();
    m_allies.at(target.get_hash()).clear();
  }

  /**
  a와 동맹들이 b의 영토를 공격한다.*/
  auto attack(idx_t a, idx_t b, string general) {}
};

void init(int N, int mSoldier[25][25], char mMonarch[25][25][11]) {}

void destroy() {}

int ally(char mMonarchA[11], char mMonarchB[11]) { return -4; }

int attack(char mMonarchA[11], char mMonarchB[11], char mGeneral[11]) {
  return -3;
}

int recruit(char mMonarch[11], int mNum, int mOption) { return -1; }

#endif