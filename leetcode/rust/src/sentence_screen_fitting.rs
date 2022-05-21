pub struct Solution;

// Pretty difficult implementation problem actually

impl Solution {
  pub fn words_typing(sentence: Vec<String>, rows: i32, cols: i32) -> i32 {
    let mut i = 0;
    let (mut r, mut c) = (0, 0);
    let mut count = 0;
    let cols = cols as usize;
    let rows = rows as usize;
    let mut dp = vec![(usize::MAX, usize::MAX); sentence.len() + 1]; // (row, count) when string i was at col 0
    while r < rows {
      if sentence[i].len() > cols {
        // no sentence will ever fit
        assert!(count == 0);
        break;
      }
      if c == 0 {
        if dp[i].0 != usize::MAX {
          // cycled
          let x = (rows - r) / (r - dp[i].0);
          r += (r - dp[i].0) * x;
          count += (count - dp[i].1) * x;
          if r >= rows {
            break;
          }
        } else {
          dp[i] = (r, count);
        }
      }
      if c + sentence[i].len() <= cols {
        // word fits
        c += sentence[i].len();
        if c != cols {
          // space
          c += 1;
        }
        if c == cols {
          // break line
          r += 1;
          c = 0;
        }
        i += 1; // go to next word
        if i == sentence.len() {
          count += 1;
          i = 0;
        }
      } else {
        // word doesn't fit, break line
        r += 1;
        c = 0;
      }
    }
    count as i32
  }
}

pub fn main() {
  println!(
    "{:?}",
    Solution::words_typing(
      ["hello".to_string(), "world".to_string()].to_vec(),
      2,
      8
    )
  );

  println!(
    "{:?}",
    Solution::words_typing(
      ["a".to_string(), "bcd".to_string(), "e".to_string()].to_vec(),
      3,
      6
    )
  );

  println!(
    "{:?}",
    Solution::words_typing(
      [
        "i".to_string(),
        "had".to_string(),
        "apple".to_string(),
        "pie".to_string()
      ]
      .to_vec(),
      4,
      5
    )
  );

  println!(
    "{:?}",
    Solution::words_typing(
      ["i".to_string(), "had".to_string(),].to_vec(),
      20000,
      20000
    )
  );

  println!(
    "{:?}",
    Solution::words_typing(
      ["f".to_string(), "p".to_string(), "a".to_string()].to_vec(),
      8,
      7
    )
  );
}
