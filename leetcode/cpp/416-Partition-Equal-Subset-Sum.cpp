#include "includes.h"

class Solution {
public:
  vector<int> cumSum;
  int totalSum;
  vector<int> nums;
  set<pair<int, int>> dp;

  bool rec(int i, int costIn, int costOut) {

    // if sum(i -> nums.size) + costIn  < S/2 or
    //    sum(i -> nums.size) + costOut < S/2 -- prune
    //
    //
    if (i == nums.size()) return costIn == costOut;
    if (cumSum[i] + costIn < totalSum / 2) return false;
    if (cumSum[i] + costOut < totalSum / 2) return false;
    if (dp.count(make_pair(i, costIn)) || dp.count(make_pair(i, costOut)))
      return false;
    dp.emplace(i, costIn);
    dp.emplace(i, costOut);
    return rec(i + 1, costIn + nums[i], costOut) ||
           rec(i + 1, costIn, costOut + nums[i]);
  }

  bool canPartition(vector<int>& nums) {
    this->nums=nums;
    totalSum = accumulate(begin(nums), end(nums), 0);
    // if (totalSum % 2 == 1) return false;


    cumSum.assign(nums.size(), 0);
    cumSum.back() = nums.back();
    for (int i = nums.size() - 2; i >= 0; --i) {
      cumSum[i] = nums[i] + cumSum[i + 1];
    }
    return rec(0, 0, 0);
  }
};