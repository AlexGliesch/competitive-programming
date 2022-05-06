#include "includes.h"

class Solution {
public:
  vector<int> shortestToChar(string s, char c) {
    vector<int> dist(s.size(), numeric_limits<int>::max());

    for (int i = 0; i < (int)s.size(); ++i) {
      if (s[i] == c)
        dist[i] = 0;
      else if (i > 0 && dist[i - 1] != numeric_limits<int>::max())
        dist[i] = dist[i - 1] + 1;
    }
    for (int i = (int)s.size() - 2; i >= 0; --i) {
      dist[i] = std::min(dist[i], dist[i + 1] + 1);
    }
    
    return dist;
  }
};
