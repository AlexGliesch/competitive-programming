pub struct Solution;

impl Solution {
  pub fn first_uniq_char(s: String) -> i32 {
    let mut occ = vec![0; 255];
    for byte in s.bytes() {
      occ[byte as usize] += 1;
    }
    for (i, byte) in s.bytes().enumerate() {
      if occ[byte as usize] == 1 {
        return i as i32;
      }
    }
    -1
  }
}

pub fn main() {
  assert!(Solution::first_uniq_char("leetcode".to_string()) == 0);
  assert!(Solution::first_uniq_char("loveleetcode".to_string()) == 2);
  assert!(Solution::first_uniq_char("aabb".to_string()) == -1);
}
