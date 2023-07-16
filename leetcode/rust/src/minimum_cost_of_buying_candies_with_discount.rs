pub struct Solution;

impl Solution {
  pub fn minimum_cost(cost: Vec<i32>) -> i32 {
    let mut cost = cost;
    cost.sort();
    let mut ans = 0;
    let mut i = (cost.len() - 1) as i32;
    while i >= 0 {
      ans += cost[i as usize];
      if i > 0 {
        ans += cost[(i - 1) as usize];
      }
      i -= 3;
    }
    return ans;
  }
}

pub fn main() {
  println!("{:?}", Solution::minimum_cost(vec![1, 2, 3]));
  println!("{:?}", Solution::minimum_cost(vec![6, 5, 7, 9, 2, 2]));
  println!("{:?}", Solution::minimum_cost(vec![5, 5]));
}
