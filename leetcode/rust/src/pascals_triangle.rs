pub struct Solution;

impl Solution {
  pub fn generate(num_rows: i32) -> Vec<Vec<i32>> {
    let n = num_rows as usize;
    let mut sol = vec![Vec::new(); n];
    for r in 0..n {
      sol[r].resize(r + 1, 1);
      if r >= 2 {
        for i in 1..r {
          sol[r][i] = sol[r - 1][i - 1] + sol[r - 1][i];
        }
      }
    }
    sol
  }
}

pub fn main() {
  println!("{:?}", Solution::generate(5));
  println!("{:?}", Solution::generate(1));
}
