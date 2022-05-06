// Honestly this problem was hard, lots of edge cases...

class Solution {
public:
  int search(vector<int>& nums, int target) {
    if (nums.size() < 10) { // cba with edge cases
      for (int i = 0; i < nums.size(); ++i)
        if (nums[i] == target) return i;
      return -1;
    }

    // binary search 0th element
    auto is_zeroth = [&](int i) {
      return i != 0 && i != nums.size() - 1 && nums[i - 1] > nums[i] &&
             nums[i + 1] > nums[i];
    };

    int lo = 0, hi = nums.size() - 1, zeroth = -1;
    while (lo <= hi) {
      int mid = (lo + hi) / 2;
      if (is_zeroth(lo)) {
        zeroth = lo;
        break;
      }
      if (is_zeroth(mid)) {
        zeroth = mid;
        break;
      }
      if (is_zeroth(hi)) {
        zeroth = hi;
        break;
      }
      if (nums[mid] > nums[lo])
        lo = mid + 1;
      else
        hi = mid - 1;
    }
    if (zeroth == -1) return -1;

    auto ls = lower_bound(begin(nums), begin(nums) + zeroth, target);
    if (ls != end(nums) && *ls == target) return ls - begin(nums);

    auto gr = lower_bound(begin(nums) + zeroth, end(nums), target);
    if (gr != end(nums) && *gr == target) return gr - begin(nums);

    return -1;
  }
};