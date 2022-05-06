class Solution {
public:
  // dp[i][num(1-3)][sum]
  // 3500 * 3 * 400 = 4.200.000
  unordered_map<int, int> dp[3501][3];
  int dfs(vector<int>& nums, int target, int i, int count, int sum) {
    if (count == 3) return sum < target;
    if (i == nums.size()) return 0;
    if (dp[i][count].count(sum)) return dp[i][count][sum];

    return dp[i][count][sum] =
               dfs(nums, target, i + 1, count, sum) +
               dfs(nums, target, i + 1, count + 1, sum + nums[i]);
  }

  int threeSumSmaller(vector<int>& nums, int target) {
    return dfs(nums, target, 0, 0, 0);
  }
};