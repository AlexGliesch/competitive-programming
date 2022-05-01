#include "includes.h"

class Solution {
public:
  int rec(int r, int c, const vector<vector<int>>& m, vector<vector<int>>& DP) {
    if (r >= m.size()) return 0;
    if (r == m.size() - 1) return m[r][c];
    if (DP[r][c] != numeric_limits<int>::max()) return DP[r][c];

    int ans = m[r][c] + rec(r + 1, c, m, DP);
    if (c > 0) ans = min(ans, m[r][c] + rec(r + 1, c - 1, m, DP));
    if (c < m.size() - 1) ans = min(ans, m[r][c] + rec(r + 1, c + 1, m, DP));
    return DP[r][c] = ans;
  }

  int minFallingPathSum(vector<vector<int>>& m) {
    vector<vector<int>> DP(m.size(),
                           vector<int>(m.size(), numeric_limits<int>::max()));
    int ans = numeric_limits<int>::max();
    for (int c = 0; c < (int)m.size(); ++c)
      ans = min(ans, rec(0, c, m, DP));

    return ans;
  }
};
