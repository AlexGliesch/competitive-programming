pub struct Solution;

impl Solution {
  pub fn find_kth_largest(mut nums: Vec<i32>, k: i32) -> i32 {
    let n = nums.len() - k as usize;
    // nums.select_nth_unstable(n);
    nums.sort();
    nums[n]
  }
}

pub fn main() {
  assert!(Solution::find_kth_largest([3, 2, 1, 5, 6, 4].to_vec(), 2) == 5);
  assert!(Solution::find_kth_largest([3, 2, 3, 1, 2, 4, 5, 5, 6].to_vec(), 4) == 4);
}
