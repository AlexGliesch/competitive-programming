pub struct Solution;

impl Solution {
  pub fn top_k_frequent(nums: Vec<i32>, k: i32) -> Vec<i32> {
    let mut m = std::collections::HashMap::with_capacity(nums.len());
    for i in nums {
      m.entry(i).and_modify(|v| *v += 1).or_insert(1);
    }
    let mut v: Vec<i32> = m.keys().cloned().collect();
    v.sort_by(|x, y| m[y].cmp(&m[x]));
    v[0..k as usize].to_vec()
  }
}

pub fn main() {
  assert!(Solution::top_k_frequent([1, 1, 1, 2, 2, 3].to_vec(), 2) == [1, 2].to_vec());
  assert!(Solution::top_k_frequent([1].to_vec(), 1) == [1].to_vec());
}
