// MLE!

#include "includes.h"

class Solution {
public:
  vector<vector<vector<int>>> dp;
  // bool dp[31][31][10000 * 31];

  bool rec(int i, int count, int sum, const vector<int>& nums) {
    if (i >= nums.size()) {
      double a1 = double(sum) / double(count);
      double a2 = double(accumulate(nums.begin(), nums.end(), 0) - sum) /
                  double(nums.size() - count);
      return fabs(a1 - a2) < 1e-7;
    }

    if (!dp[i + 1][count + 1][sum + nums[i]]) {
      dp[i + 1][count + 1][sum + nums[i]] = true;
      if (rec(i + 1, count + 1, sum + nums[i], nums)) return true;
    }
    if (!dp[i + 1][count][sum]) {
      dp[i + 1][count][sum] = true;
      if (rec(i + 1, count, sum, nums)) return true;
    }
    return false;
  }

  bool splitArraySameAverage(vector<int>& nums) {
    if (count(begin(nums), end(nums), 0) == nums.size() && nums.size() > 1)
      return true;
    // memset(dp, 0, sizeof(dp));
    dp.assign(31, vector<vector<int>>(31, vector<int>(31*10000)));

    // vector<vector<unordered_set<int>>> dp(31,
    // vector<unordered_set<int>>(31));
    return rec(0, 0, 0, nums);
  }
};
int main() {
  Solution s;
  // vector<int> v{2, 0, 5, 6, 16, 12, 15, 12, 4};
  // vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 123, 325, 5, 4, 543};
  // vector<int> v{3863, 703, 1799, 327,  3682, 4330, 3388, 6187, 5330,
  //               6572, 938, 6842, 678,  9837, 8256, 6886, 2204, 5262,
  //               6643, 829, 745,  8755, 3549, 6627, 1633, 4290, 7};
  // vector<int> v{0, 0};
  vector<int> v{5, 16, 4, 11, 4};

  cout << s.splitArraySameAverage(v) << endl;
}