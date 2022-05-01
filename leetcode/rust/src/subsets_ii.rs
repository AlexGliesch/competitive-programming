pub struct Solution;

impl Solution {
  pub fn subsets_with_dup(nums: Vec<i32>) -> Vec<Vec<i32>> {
    let n = nums.len();
    let nn = 2usize.pow(n as u32);
    let mut ps = std::collections::BTreeSet::new();
    for i in 0..nn {
      let mut p = Vec::new();
      for j in 0..n {
        if i & (1 << j) > 0 {
          p.push(nums[j]);
        }
      }
      p.sort();
      ps.insert(p);
    }
    ps.iter().cloned().collect()
  }
}

pub fn main() {
  println!("{:?}", Solution::subsets_with_dup([4, 4, 4, 1, 4].to_vec()));
  println!("{:?}", Solution::subsets_with_dup([1, 2, 2].to_vec()));
  println!("{:?}", Solution::subsets_with_dup([0].to_vec()));
}
