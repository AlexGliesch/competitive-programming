pub struct Solution;

impl Solution {
  pub fn is_valid(s: String) -> bool {
    let mut stack = vec![' '; s.len()];
    let mut top: i32 = -1;
    let mut mate = [' '; 255];
    mate[')' as usize] = '(';
    mate[']' as usize] = '[';
    mate['}' as usize] = '{';
    for b in s.chars() {
      match b {
        '(' | '{' | '[' => {
          top += 1;
          stack[top as usize] = b;
        }
        _ => {
          if top < 0 || stack[top as usize] != mate[b as usize] {
            return false;
          } else {
            top -= 1;
          }
        }
      }
    }
    top == -1
  }
}

pub fn main() {
  assert!(Solution::is_valid("([)]".to_string()) == false);
  assert!(Solution::is_valid("{[]}".to_string()) == true);
  assert!(Solution::is_valid("[".to_string()) == false);
}
