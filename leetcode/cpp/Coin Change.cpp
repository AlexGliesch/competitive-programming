class Solution {
private:
  vector<int> c;
  vector<int> dp;
  static constexpr int MAX = 1<<28;
  
  int dfs(int i, int amount) {
    if (amount == 0) return 0;
    if (i >= c.size() || amount < c[i]) return MAX;
    if (dp[amount*12+i] != -1) return dp[amount*12+i];
    return dp[amount*12+i] = min(1 + dfs(i, amount - c[i]), dfs(i + 1, amount));
  }
  
public:  
  int coinChange(vector<int>& coins, int amount) {
    c = coins;
    sort(begin(c), end(c));
    dp.assign(12 * 10001, -1);
    int ans = dfs(0, amount);
    return ans == MAX ? -1 : ans;
  }
};