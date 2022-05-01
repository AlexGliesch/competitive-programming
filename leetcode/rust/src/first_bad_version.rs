pub struct Solution {
  pub bad: i32,
}

impl Solution {
  pub fn isBadVersion(&self, versions: i32) -> bool {
    versions >= self.bad
  }
}

impl Solution {
  pub fn first_bad_version(&self, n: i32) -> i32 {
    let mut p: (i64, i64) = (1, n as i64);
    while p.0 < p.1 {
      let mid: i64 = (p.0 + p.1) / 2;
      p = if self.isBadVersion(mid as i32) {
        (p.0, mid)
      } else {
        (mid + 1, p.1)
      };
    }
    p.1 as i32
  }
}
