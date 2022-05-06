#include "includes.h"

class Solution {
public:
  //
  // nd_rec(s, i):
  //    if i>=s.len
  //      0
  //    else if s[i]=0
  //      -infty
  //    else
  //      [s[i]!=0] max(0, 1 + nd_rec(s,i+1))
  //      +
  //      [0<s[i]<=2 && 0<=s[i+1]<=6] max(0, 1 + nd_rec(s,i+2))
  //
  //

  int nd(const string& s, int i, int dp[101]) {
    if (i >= s.size()) return 1;
    if (s[i] == '0') return numeric_limits<int>::min();
    if (dp[i] != -1) return dp[i];

    int ans = 0;
    if (nd(s, i + 1, dp) >= 0) ans += nd(s, i + 1, dp);
    if (i + 1 < s.size() && (s[i] == '1' || s[i] == '2' && s[i + 1] <= '6') &&
        nd(s, i + 2, dp) >= 0)
      ans += nd(s, i + 2, dp);
    return dp[i] = ans;
  }

  int numDecodings(string s) {
    int dp[101];
    fill(begin(dp), end(dp), -1);
    int ans = nd(s, 0, dp);
    return max(ans, 0);
  }
};