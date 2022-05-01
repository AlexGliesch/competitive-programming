use std::collections::VecDeque;

pub struct Solution;

impl Solution {
  pub fn num_islands(grid: Vec<Vec<char>>) -> i32 {
    let R = grid.len();
    let C = grid[0].len();
    let dr = [-1, 1, 0, 0];
    let dc = [0, 0, -1, 1];
    let mut v = vec![vec![false; C]; R];
    let mut q: VecDeque<(usize, usize)> = VecDeque::new();
    let mut isl = 0;
    for r in 0..R {
      for c in 0..C {
        if v[r][c] || grid[r][c] == '0' {
          continue;
        }
        isl = isl + 1;
        v[r][c] = true;
        q.push_back((r, c));
        while !q.is_empty() {
          assert_eq!(grid[r][c], '1');
          let (r, c) = q.pop_front().unwrap();
          for i in 0..4 {
            let (nr, nc) = (r as i32 + dr[i], c as i32 + dc[i]);
            if nr < 0 || nc < 0 {
              continue;
            }
            let (nr, nc) = (nr as usize, nc as usize);
            if nr >= R || nc >= C || v[nr][nc] || grid[nr][nc] == '0' {
              continue;
            }
            v[nr][nc] = true;
            q.push_back((nr, nc));
          }
        }
      }
    }
    isl
  }
}

pub fn main() {
  let t1 = [
    ['1', '1', '0', '0', '0'].to_vec(),
    ['1', '1', '0', '0', '0'].to_vec(),
    ['0', '0', '1', '0', '0'].to_vec(),
    ['0', '0', '0', '1', '1'].to_vec(),
  ]
  .to_vec();
  assert_eq!(3, Solution::num_islands(t1));


}
