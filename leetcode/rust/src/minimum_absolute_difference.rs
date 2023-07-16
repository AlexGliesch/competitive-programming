pub struct Solution;

impl Solution {
  pub fn minimum_abs_difference(arr: Vec<i32>) -> Vec<Vec<i32>> {
    let mut arr = arr;
    arr.sort();
    let mut min_diff = std::i32::MAX;
    for i in 1..arr.len() {
      min_diff = std::cmp::min(min_diff, arr[i] - arr[i - 1]);
      assert!(min_diff >= 0);
    }
    use std::collections::HashSet;
    let mut hash = HashSet::new();
    for &i in &arr {
      hash.insert(i);
    }
    let mut ans = Vec::new();
    for i in arr {
      if hash.contains(&(i - min_diff)) {
        ans.push(vec![i - min_diff, i]);
      }
    }
    return ans;
  }
}

pub fn main() {
  println!("{:?}", Solution::minimum_abs_difference(vec![4, 2, 1, 3]));
  println!(
    "{:?}",
    Solution::minimum_abs_difference(vec![1, 3, 6, 10, 15])
  );
  println!(
    "{:?}",
    Solution::minimum_abs_difference(vec![3, 8, -10, 23, 19, -4, -14, 27])
  );
}
