pub struct Solution;

// aaa
// a a a aa aa aaa

impl Solution {
  fn expand_palindrome(i: i32, j: usize, b: &[u8]) -> i32 {
    let mut i = i;
    let mut j = j;
    let mut count = 0;
    while i >= 0 && j < b.len() && b[i as usize] == b[j] {
      count += 1;
      j += 1;
      i -= 1;
    }
    count
  }

  pub fn count_substrings(s: String) -> i32 {
    let mut count = 0; // every character itself is a palindrome
    let b = s.as_bytes();
    for i in 0..s.len() {
      // palindromes of odd num. chars
      count += Solution::expand_palindrome(i as i32, i, b);
      // palindromes of even num. chars
      count += Solution::expand_palindrome(i as i32, i + 1, b);
    }
    count
  }
}

pub fn main() {
  println!("{:?}", Solution::count_substrings("aaa".to_string()));
  println!("{:?}", Solution::count_substrings("abc".to_string()));
}
