class Solution {
public:
  vector<int> nextGreaterElements(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n, -1);
    for (int i = 0; i < n; ++i) {
      for (int seen = 0, j = i; seen <= n; ++seen, j = (j + 1) % n) {
        if (nums[j] > nums[i]) {
          ans[i] = nums[j];
          break;
        }
      }
    }
    return ans;
  }
};