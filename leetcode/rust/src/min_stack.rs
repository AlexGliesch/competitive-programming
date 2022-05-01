struct MinStack {
  val: Vec<i32>,
  min: Vec<i32>,
}

impl MinStack {
  fn new() -> Self {
    Self {
      val: Vec::new(),
      min: Vec::new(),
    }
  }

  fn push(&mut self, val: i32) {
    self.val.push(val);
    self.min.push(std::cmp::min(
      *self.min.last().unwrap_or(&std::i32::MAX),
      val,
    ));
  }

  fn pop(&mut self) {
    self.val.pop();
    self.min.pop();
  }

  fn top(&self) -> i32 {
    *self.val.last().unwrap()
  }

  fn get_min(&self) -> i32 {
    *self.min.last().unwrap()
  }
}

pub fn main() {
  let mut obj = MinStack::new();
  obj.push(0);
  obj.push(1);
  obj.pop();
  let ret_3: i32 = obj.top();
  let ret_4: i32 = obj.get_min();
}
