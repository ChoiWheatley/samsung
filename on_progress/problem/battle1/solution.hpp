#ifndef SOLUTION
#define SOLUTION

#include <algorithm>
#include <map>
#include <set>
#include <vector>
using std::map;
using std::set;
using std::vector;

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

class SoldierController {
public:
  explicit SoldierController() = default;
  void hire(int mID, int mTeam, int mScore) {
    m_soldiers.insert({mID, Soldier{mID, mTeam, mScore}});
  }

  void fire(int mID) {
    auto itr = m_soldiers.find(mID);
    if (itr != m_soldiers.end()) {
      m_soldiers.erase(itr);
    }
  }

  void updateSoldier(int mID, int mScore) {
    auto result = m_soldiers.insert({mID, Soldier{mID, 0, 0}});
    if (!result.second) {
      result.first->second.mScore = mScore;
    }
  }

  void updateTeam(int mTeam, int mChangeScore) {

    for (auto itr = m_soldiers.begin(); itr != m_soldiers.end(); ++itr) {
      auto &elem = itr->second;
      if (elem.mTeam == mTeam) {
        elem.mScore = normalize_score(elem.mScore + mChangeScore);
      }
    }
  }

  int bestSoldier(int mTeam) const {
    int max = 0;
    int id = 0;
    for (auto itr = m_soldiers.cbegin(); itr != m_soldiers.cend(); ++itr) {
      auto const &elem = itr->second;
      if (elem.mTeam == mTeam) {
        if (elem.mScore > max) {
          max = elem.mScore;
          id = elem.mID;
        } else if (elem.mScore == max) {
          id = std::max(id, elem.mID);
        }
      }
    }
    return id;
  }

private:
  map<int, Soldier> m_soldiers{};
};

SoldierController sc;

void init() { sc = SoldierController(); }

void hire(int mID, int mTeam, int mScore) { sc.hire(mID, mTeam, mScore); }

void fire(int mID) { sc.fire(mID); }

void updateSoldier(int mID, int mScore) { sc.updateSoldier(mID, mScore); }

void updateTeam(int mTeam, int mChangeScore) {
  sc.updateTeam(mTeam, mChangeScore);
}

int bestSoldier(int mTeam) { return sc.bestSoldier(mTeam); }

#endif