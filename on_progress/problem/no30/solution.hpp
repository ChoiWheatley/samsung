#ifndef SOLUTION
#define SOLUTION

#include <cstddef>
#include <sstream>
#include <string>
using std::string;
using std::stringstream;

static size_t djb2(const string &key) {
  size_t hash = 5381;
  for (auto c : key) {
    hash = ((hash << 5) + hash) + c;
  }
  return hash;
}

/**
@breif: 일렬로 만든 두 이차원 문자열 dream, sam으로부터 dream이 sam에 몇 번
나타나는지 알아내시오.
@param:
 - h: height of dream
 - w: width of dream
 - n: height of sam
 - m: width of sam
*/
inline int solution(int h, int w, int n, int m, //
                    string const &dream, string const &sam) {
  size_t key = djb2(dream);
  int cnt = 0;
  // i,j = start position
  for (int i = 0; i < n - h + 1; ++i) {
    for (int j = 0; j < m - w + 1; ++j) {
      stringstream concater;
      // append str into concater
      for (int row = 0; row < h; ++row) {
        int startidx = (i + row) * n + j;
        concater << sam.substr(startidx, w);
      }
      string subpicture = concater.str();
      if (key == djb2(subpicture)) {
        cnt++;
      }
    }
  }
  return cnt;
}

#endif