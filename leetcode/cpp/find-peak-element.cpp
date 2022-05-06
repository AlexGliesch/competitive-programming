#include "includes.h"

class Solution {
public:
  int findPeakElement(vector<int>& nums) {
    // if at i
    // if peak return i
    // if i-1 is less (i+1 is greater, increasing)
    //    go right (there must be a peak to the right)
    // else
    //    go left (there must be a peak to the left)

    int lo = 0, hi = nums.size() - 1;
    while (hi > lo) {
      int i = (hi + lo) / 2;
      bool leftSmaller = (i == 0 || nums[i - 1] < nums[i]);
      bool rightSmaller = (i == nums.size() - 1 || nums[i + 1] < nums[i]);
      if (leftSmaller && rightSmaller) return i;
      if (leftSmaller) {
        lo = i + 1;
      } else {
        hi = i - 1;
      }
    }
    return -1;
  }
};