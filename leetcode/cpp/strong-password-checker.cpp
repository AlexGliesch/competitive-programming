class Solution {
public:
  // Actual solution is greedy. But tbh DP was easier to implement

  // dp[i][size][hasl][hasu][hasd][prv][iscrit]
  //   50 * 50 *  2    * 2   * 2   * 50 * 2  ~ 3 mil
  int dp[51][51][2][2][2][255][2];

  int rec(const string& s, int n, int i, int size, int hasl, int hasu, int hasd,
          int prv, int iscrit) {
    if (i == n) {
      // size, hasl,hasu,hasd
      int ans = 0;
      if (size < 6)
        ans = 6 - size;
      else if (size > 20)
        ans = size - 20;

      int free = max(0, 6 - size);
      if (!hasl) free ? --free : ++ans;
      if (!hasu) free ? --free : ++ans;
      if (!hasd) free ? --free : ++ans;

      return ans;
    }
    if (dp[i][size][hasl][hasu][hasd][prv][iscrit] != -1) {
      return dp[i][size][hasl][hasu][hasd][prv][iscrit];
    }
    int ans = 200;
    if (iscrit && prv != 0 && s[i] == prv) {
      // change s[i]
      ans = min(ans, 1 + rec(s, n, i + 1, size, 1, hasl ? 1 : hasu,
                             hasl && hasu ? 1 : hasd, 0, 0));
      // delete s[i]
      if (size > 20)
        ans =
            min(ans, 1 + rec(s, n, i + 1, size - 1, hasl, hasu, hasd, prv, 1));
      // add something before s[i]
      if (size < 6)
        ans = min(ans, 1 + rec(s, n, i + 1, size + 1, 1, hasl ? 1 : hasu,
                               hasl && hasu ? 1 : hasd, 0, 0));
    } else {
      ans = rec(s, n, i + 1, size, hasl, hasu, hasd, s[i],
                prv > 0 ? s[i] == prv : 0);
    }
    return dp[i][size][hasl][hasu][hasd][prv][iscrit] = ans;
  }

  int strongPasswordChecker(string pw) {
    memset(dp, -1, sizeof(dp));
    int numlower = 0, numupper = 0, numdigits = 0;
    for (char c : pw) { // could do count_if
      numlower += (c >= 'a' && c <= 'z');
      numupper += (c >= 'A' && c <= 'Z');
      numdigits += (c >= '0' && c <= '9');
    }
    return rec(pw, pw.size(), 0, pw.size(), numlower > 0, numupper > 0,
               numdigits > 0, 0, 0);
  }
};