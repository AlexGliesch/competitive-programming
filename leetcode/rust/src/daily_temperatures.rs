pub struct Solution;

impl Solution {
  pub fn daily_temperatures(temperatures: Vec<i32>) -> Vec<i32> {
    let mut stack = vec![(-1, std::usize::MAX); temperatures.len()];
    let mut sz = 0;
    let mut ans = vec![-1; temperatures.len()];

    for i in 0..temperatures.len() {
      while sz > 0 && stack[sz - 1].0 < temperatures[i] {
        assert!(i > stack[sz - 1].1);
        ans[stack[sz - 1].1] = (i - stack[sz - 1].1) as i32;
        sz -= 1;
      }
      stack[sz] = (temperatures[i], i);
      sz += 1;
    }
    while sz > 0 {
      ans[stack[sz - 1].1] = 0i32;
      sz -= 1;
    }
    assert!(!ans.contains(&-1));
    return ans;
  }
}

pub fn main() {
  println!(
    "{:?}",
    Solution::daily_temperatures(vec![73, 74, 75, 71, 69, 72, 76, 73])
  );
  println!("{:?}", Solution::daily_temperatures(vec![30, 40, 50, 60]));
  println!("{:?}", Solution::daily_temperatures(vec![30, 60, 90]));
}
