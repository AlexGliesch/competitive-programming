class Solution {
public:
  // 1 2 2 4 4 5 5 6 6 6 7 7 8 8 9
  // 0 1 1 3 3 5 5 7 7 7
  vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
    vector<int> ans(nums.size(), 0), order(nums.size());
    iota(begin(order), end(order), 0);
    sort(begin(order), end(order),
         [&](int i, int j) { return nums[i] < nums[j]; });

    for (int i = 1; i < ans.size(); ++i)
      if (nums[order[i]] == nums[order[i - 1]])
        ans[order[i]] = ans[order[i - 1]];
      else
        ans[order[i]] = i;
    return ans;
  }
};