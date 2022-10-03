pub struct Solution;

impl Solution {
  pub fn longest_valid_parentheses(s: String) -> i32 {
    let mut start = 0;
    let mut max = 0;
    let mut stack = Vec::new();
    let b = s.as_bytes();
    for i in 0..s.len() {
      if b[i] == b'(' {
        stack.push(i);
      } else {
        if !stack.is_empty() && b[*stack.last().unwrap()] == b'(' {

        } else {
          start = i;       }
      }

    }

    



    count
  }
}

pub fn main() {
  print!(
    "{:?}",
    Solution::longest_valid_parentheses(")()())".to_string())
  );
  print!(
    "{:?}",
    Solution::longest_valid_parentheses("(()".to_string())
  );
  print!(
    "{:?}",
    Solution::longest_valid_parentheses("()(())()".to_string())
  );
  print!(
    "{:?}",
    Solution::longest_valid_parentheses("".to_string())
  );
}
