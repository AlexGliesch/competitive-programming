pub struct Solution;

impl Solution {
  pub fn remove_duplicates(s: String, k: i32) -> String {
    let mut r = String::new();
    let mut count = Vec::new();
    for i in 0..s.len() {      
      if count.is_empty() || s.as_bytes()[i] != *r.as_bytes().last().unwrap() {
        count.push(1);
      } else {
        assert!(s.as_bytes()[i] == *r.as_bytes().last().unwrap());
        count.push(1 + *count.last().unwrap());
      }
      r.push(s.as_bytes()[i] as char);
      if *count.last().unwrap() == k as usize {
        for _ in 0..k {
          assert!(!count.is_empty());
          count.pop();
          r.pop();
        }
      }
      // println!("{} {:?}", r, count);
    }
    r
  }
}

pub fn main() {
  println!("{:?}", Solution::remove_duplicates("abcd".to_string(), 2));
  println!(
    "{:?}",
    Solution::remove_duplicates("deeedbbcccbdaa".to_string(), 3)
  );
  println!(
    "{:?}",
    Solution::remove_duplicates("pbbcggttciiippooaais".to_string(), 2)
  );
}
