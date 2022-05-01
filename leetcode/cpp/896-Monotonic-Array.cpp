#include "includes.h"

class Solution {
public:
  template<typename T>
  bool isMono(vector<int>& nums, T op) {
    for (int i = 0; i < nums.size() - 1; ++i)
      if (op(nums[i], nums[i + 1])) return false;
    return true;
  }

  bool isMonotonic(vector<int>& nums) {
    return isMono(nums, less<int>()) || isMono(nums, greater<int>());
  }
};