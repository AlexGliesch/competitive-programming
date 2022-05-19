class Solution {
public:
  vector<int> productExceptSelf(vector<int>& nums) {
    vector<int> sup(nums.size() + 1, 1);
    for (int i = nums.size() - 1; i >= 0; --i) sup[i] = nums[i] * sup[i+1];
    
    int p = 1;
    vector<int> ans(nums.size());
    for (int i = 0; i < nums.size(); ++i) {
      ans[i] = p * sup[i+1];
      p = p * nums[i];
    }
    return ans;
  }
};