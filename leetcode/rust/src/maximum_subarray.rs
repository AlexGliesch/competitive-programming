pub struct Solution;

impl Solution {
  // R[i] = max(R[i+1], R[i+1] + nums[i])
  pub fn max_sub_array(nums: Vec<i32>) -> i32 {
    let n = nums.len();
    let mut r = nums[n - 1];
    let mut ans = r;
    for i in (1..n).rev() {
      r = std::cmp::max(nums[i - 1], r + nums[i - 1]);
      ans = std::cmp::max(ans, r);
    }
    ans
  }
}

pub fn main() {
  assert!(Solution::max_sub_array([-2, 1, -3, 4, -1, 2, 1, -5, 4].to_vec()) == 6);
  assert!(Solution::max_sub_array([1].to_vec()) == 1);
  assert!(Solution::max_sub_array([5, 4, -1, 7, 8].to_vec()) == 23);
  assert!(Solution::max_sub_array([-5, -4].to_vec()) == -4);
}
