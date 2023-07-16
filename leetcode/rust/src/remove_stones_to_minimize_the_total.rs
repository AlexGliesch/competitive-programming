pub struct Solution;

impl Solution {
  pub fn min_stone_sum(piles: Vec<i32>, k: i32) -> i32 {
    let mut heap = std::collections::BinaryHeap::from(piles);
    let n = heap.len();

    for _i in 0..(k as usize) {
      assert_eq!(n, heap.len());
      if let Some(x) = heap.pop() {
        let s = (x as f64 / 2.0).floor();
        heap.push(x - s as i32);
      }
    }
    let sum = heap.iter().sum();
    return sum;
  }
}

pub fn main() {
  println!("{:?}", Solution::min_stone_sum(vec![5, 4, 9], 2));
  println!("{:?}", Solution::min_stone_sum(vec![4, 3, 6, 7], 3));
}
