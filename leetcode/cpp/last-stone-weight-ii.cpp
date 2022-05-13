class Solution {
public:
  // if stones = [s_1, s_2, ..., s_n]
  // expression always evaluates to an expression of type +-s_1 +-s_2 +- ... +-
  // s_n each stone can either be added or subtracted
  unordered_map<int, int> dp[31];

  int dfs(const vector<int>& s, int i, int sum) {
    if (i == s.size()) return sum >= 0 ? sum : numeric_limits<int>::max();
    if (dp[i].count(sum)) return dp[i][sum];
    int ans = dfs(s, i + 1, sum + s[i]);
    ans = min(ans, dfs(s, i + 1, sum - s[i]));
    return dp[i][sum] = ans;
  }

  int lastStoneWeightII(vector<int>& stones) { return dfs(stones, 0, 0); }
};