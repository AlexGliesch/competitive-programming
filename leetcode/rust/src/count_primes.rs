pub struct Solution;

impl Solution {
  pub fn count_primes(n: i32) -> i32 {
    if n <= 2 {
      return 0;
    }
    let n = n as usize;
    let mut count = 0;
    let mut sieve = vec![false; n+1];
    for x in 2usize..n {
      if sieve[x] {
        continue;
      }
      count += 1;
      let mut u = 2 * x;
      while u <= n {
        sieve[u] = true;
        u += x;
      }
    }
    count
  }
}

pub fn main () {
  assert!(Solution::count_primes(10) == 4);
  assert!(Solution::count_primes(1) == 0);
  assert!(Solution::count_primes(0) == 0);
  println!("{}", Solution::count_primes(129834));
}