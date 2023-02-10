#ifndef SOLUTION
#define SOLUTION

#include <algorithm>
#include <array>
#include <bitset>
#include <map>
#include <set>
#include <vector>

using std::array;

constexpr size_t MAX_ID = 100000 + 1;
constexpr size_t MAX_SCORE = 5 + 1;
constexpr size_t MAX_TEAM = 5 + 1;

struct Soldier {
  int mID = 0;
  int mTeam = 0;
  Soldier *next = nullptr;
  Soldier *prev = nullptr;
};

struct Team {
  array<Soldier *, MAX_SCORE> score_head; // dummy node
  array<Soldier *, MAX_SCORE> score_tail; // dummy node
  explicit Team() {
    for (size_t score = 1; score < MAX_SCORE; ++score) {
      score_head[score] = new Soldier();
      score_tail[score] = new Soldier();
      score_head[score]->next = score_tail[score];
      score_tail[score]->prev = score_head[score];
    }
  }
};

static auto normalize_score(int score) -> int {
  if (score < 1)
    return 1;
  if (score > 5)
    return 5;
  return score;
}

array<Soldier, MAX_ID> soldiers;
array<Team, MAX_TEAM> teams;

void init() {
  soldiers = {};
  teams = {};
}

void hire(int mID, int mTeam, int mScore) {
  soldiers[mID].mID = mID;
  soldiers[mID].mTeam = mTeam;
  auto head = teams[mTeam].score_head[mScore];
  soldiers[mID].next = head->next;
  soldiers[mID].prev = head;
  head->next->prev = &soldiers[mID];
  head->next = &soldiers[mID];
}

void fire(int mID) {
  auto curr = soldiers[mID];
  curr.prev->next = curr.next;
  curr.next->prev = curr.prev;
  curr.mID = 0;
  curr.mTeam = 0;
}

/** fire -> hire */
void updateSoldier(int mID, int mScore) {
  int team = soldiers[mID].mTeam;
  fire(mID);
  hire(mID, team, mScore);
}

/** oldhead~oldtail 구간에 있는 원소들을 newhead 뒤에 삽입한다. */
auto replace(Soldier *oldhead, Soldier *oldtail, Soldier *newhead) {

  newhead->next->prev = oldtail->prev;
  oldtail->prev->next = newhead->next;

  oldhead->next->prev = newhead;
  newhead->next = oldhead->next;

  oldhead->next = oldtail;
  oldtail->prev = oldhead;
}

void updateTeam(int mTeam, int mChangeScore) {
  auto team = teams[mTeam];
  if (mChangeScore > 0) {
    // 5-4-3-2-1 순으로 돌아야 연쇄적으로 격상되는 걸 방지할 수 있음.
    for (int score = MAX_SCORE - 1; score > 0; --score) {
      auto target_score = normalize_score(score + mChangeScore);
      if (target_score == score ||
          team.score_head[score]->next == team.score_tail[score]) {
        continue;
      }
      // score => target_score 으로 링크를 갈아끼워주기
      replace(team.score_head[score], team.score_tail[score],
              team.score_head[target_score]);
    }
  } else if (mChangeScore < 0) {
    // 마찬가지로 1-2-3-4-5 순으로 돌아야 연쇄적으로 강등되는 걸 방지할 수 있음.
    for (int score = 1; score < MAX_SCORE; ++score) {
      auto target_score = normalize_score(score + mChangeScore);
      if (target_score == score ||
          team.score_head[score]->next == team.score_tail[score]) {
        continue;
      }
      // score => target_score 으로 링크를 갈아끼워주기
      replace(team.score_head[score], team.score_tail[score],
              team.score_head[target_score]);
    }
  }
}

int bestSoldier(int mTeam) {
  // 100번밖에 호출을 안하니 전수조사 시행한다.
  int id = 0;
  for (size_t score = MAX_SCORE - 1; score > 0; --score) {
    auto const *head = teams[mTeam].score_head[score];
    auto const *tail = teams[mTeam].score_tail[score];
    auto *cur = head->next;
    while (cur != tail) {
      id = std::max(id, cur->mID);
      cur = cur->next;
    }
    if (id != 0) {
      return id;
    }
  }
  // not found
  return 0;
}

#endif