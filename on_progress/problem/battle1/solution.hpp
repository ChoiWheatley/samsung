#ifndef SOLUTION
#define SOLUTION

#include <algorithm>
#include <array>
#include <bitset>
#include <map>
#include <set>
#include <vector>

using std::array;
using std::bitset;
using std::map;
using std::set;
using std::vector;

constexpr size_t MAX_ID = 100000 + 1;
constexpr size_t MAX_SCORE = 5 + 1;
constexpr size_t MAX_TEAM = 5 + 1;

struct Soldier {
  int mID;
  int mTeam;
  int mScore;
};

static auto normalize_score(int score) -> int {
  if (score < 1)
    return 1;
  if (score > 5)
    return 5;
  return score;
}

template <class Consumer>
auto foreach_true(bitset<MAX_ID> const &bitmap, Consumer const &consumer) {
  for (int idx = 1; idx < MAX_ID; ++idx) {
    if (bitmap.test(idx)) {
      consumer(idx);
    }
  }
}

array<Soldier, MAX_ID> m_soldiers;
bitset<MAX_ID> m_existence;
array<bitset<MAX_ID>, MAX_TEAM> m_bitmap_team;
array<bitset<MAX_ID>, MAX_SCORE> m_bitmap_score;

void init() {
  m_soldiers.fill(Soldier{});
  m_existence.reset();
  m_bitmap_team.fill(bitset<MAX_ID>{});
  m_bitmap_score.fill(bitset<MAX_ID>{});
}

void hire(int mID, int mTeam, int mScore) {
  m_existence.set(mID);
  m_bitmap_team[mTeam].set(mID);
  m_bitmap_score[mScore].set(mID);
  m_soldiers[mID] = Soldier{mID, mTeam, mScore};
}

void fire(int mID) { m_existence.reset(mID); }

void updateSoldier(int mID, int mScore) {
  if (!m_existence.test(mID)) {
    return;
  }
  // 이전 스코어를 새 스코어에 할당하는 과정 필요.
  m_bitmap_score[m_soldiers[mID].mScore].reset(mID);
  m_bitmap_score[mScore].set(mID);
  // 실제 값 변경
  m_soldiers[mID].mScore = mScore;
}

void updateTeam(int mTeam, int mChangeScore) {
  // mTeam으로 질의, 일치하는 모든 id에 대하여 change score
  auto const result = m_bitmap_team[mTeam] & m_existence;
  foreach_true(result, [mChangeScore](int id) {
    updateSoldier(id, normalize_score(m_soldiers[id].mScore + mChangeScore));
  });
}

int bestSoldier(int mTeam) {
  auto const result = m_bitmap_team[mTeam] & m_existence;
  for (int score = MAX_SCORE - 1; score > 0; --score) {
    auto filtered = result & m_bitmap_score[score];
    for (int id = MAX_ID - 1; id > 0; --id) {
      if (filtered.test(id)) {
        return id;
      }
    }
  }
  // not found
  return 0;
}

#endif