pub struct Solution;

impl Solution {
  pub fn fizz_buzz(n: i32) -> Vec<String> {
    let mut r: Vec<String> = Vec::with_capacity(n as usize);
    for i in 1..=n {
      r.push(match(i%3, i%5) {
        (0, 0) => "FizzBuzz".to_string(),
        (0, _) => "Fizz".to_string(),
        (_, 0) => "Buzz".to_string(),
        (_, _) => i.to_string()
      });
    }
    r
  }
}