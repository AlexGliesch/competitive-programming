pub struct Solution;

// Super verbose, need to get better at Rust?

impl Solution {
  pub fn find_max_form(strs: Vec<String>, m: i32, n: i32) -> i32 {
    let mut dp =
      vec![vec![vec![-1; n as usize + 1]; m as usize + 1]; strs.len() + 1];
    let mut zeros = vec![0; strs.len()];
    let mut ones = vec![0; strs.len()];
    for (i, s) in strs.iter().enumerate() {
      zeros[i] = s.as_bytes().iter().filter(|&&x| x == b'0').count();
      ones[i] = s.len() - zeros[i];
    }

    fn dfs(
      i: usize,
      mc: usize,
      nc: usize,
      m: usize,
      n: usize,
      ones: &[usize],
      zeros: &[usize],
      dp: &mut Vec<Vec<Vec<i32>>>,
    ) -> i32 {
      if mc > m as usize || nc > n as usize {
        return std::i32::MIN;
      }
      if i == ones.len() {
        return 0;
      }
      if dp[i][mc][nc] != -1 {
        return dp[i][mc][nc];
      }
      dp[i][mc][nc] = std::cmp::max(
        1 + dfs(i + 1, mc + zeros[i], nc + ones[i], m, n, ones, zeros, dp),
        dfs(i + 1, mc, nc, m, n, ones, zeros, dp),
      );
      dp[i][mc][nc]
    }

    let a = dfs(0, 0, 0, m as usize, n as usize, &ones, &zeros, &mut dp);
    return if a > 0 { a } else { 0 };
  }
}

pub fn main() {
  println!(
    "{:?}",
    Solution::find_max_form(
      vec![
        "10".to_string(),
        "0001".to_string(),
        "111001".to_string(),
        "1".to_string(),
        "0".to_string(),
      ],
      5,
      3
    )
  );
  println!(
    "{:?}",
    Solution::find_max_form(
      vec!["10".to_string(), "1".to_string(), "0".to_string(),],
      1,
      1
    )
  );
}
