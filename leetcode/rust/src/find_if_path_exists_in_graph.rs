// Incomplete
pub struct Solution;

impl Solution {
  pub fn valid_path(
    n: i32,
    edges: Vec<Vec<i32>>,
    source: i32,
    destination: i32,
  ) -> bool {
    let mut g = vec![Vec::new(); n as usize];
    for e in &edges {
      assert!(e.len() == 2);
      g[e[0] as usize].push(e[1] as usize);
      g[e[1] as usize].push(e[0] as usize);
    }
    use std::collections::VecDeque;
    let mut q = VecDeque::from([source as usize]);
    let mut vis = vec![false; n as usize];
    vis[source as usize] = true;

    while !q.is_empty() {
      let v = *q.front().unwrap();
      q.pop_front();

      if v == destination as usize {
        return true;
      }
      for &nb in &g[v] {
        if !vis[nb] {
          vis[nb] = true;
          q.push_back(nb);
        }
      }
    }
    return false;
  }
}

pub fn main() {
  println!(
    "{:?}",
    Solution::valid_path(3, vec![vec![0, 1], vec![1, 2], vec![2, 0]], 0, 2)
  );
  println!(
    "{:?}",
    Solution::valid_path(
      6,
      vec![vec![0, 1], vec![0, 2], vec![3, 5], vec![5, 4], vec![4, 3]],
      0,
      5
    )
  );
}
