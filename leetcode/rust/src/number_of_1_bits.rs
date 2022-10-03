pub struct Solution;

impl Solution {
  pub fn hammingWeight(n: u32) -> i32 {
    let mut i = n;
    let mut count = 0;
    for _ in 0..32 {
      count += i & 1;
      i = i >> 1;
    }
    count as i32
  }
}

pub fn main() {
  println!("{}", Solution::hammingWeight(1));
  println!("{}", Solution::hammingWeight(2));
  println!("{}", Solution::hammingWeight(3));
  println!("{}", Solution::hammingWeight(15));
}