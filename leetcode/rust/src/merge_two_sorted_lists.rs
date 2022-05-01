// Definition for singly-linked list.
#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
  pub val: i32,
  pub next: Option<Box<ListNode>>,
}

impl ListNode {
  #[inline]
  fn new(val: i32) -> Self {
    ListNode { next: None, val }
  }
}

pub struct Solution;

impl Solution {
  fn list_append(mut r: &mut Option<Box<ListNode>>, val: i32) -> &mut Option<Box<ListNode>> {
    assert!((*r).is_none());
    *r = Some(Box::new(ListNode::new(val)));
    &mut r.as_mut().unwrap().next
  }

  pub fn merge_two_lists(
    mut a: Option<Box<ListNode>>,
    mut b: Option<Box<ListNode>>,
  ) -> Option<Box<ListNode>> {
    let mut head = None;
    let mut tail = &mut head;

    while a.is_some() && b.is_some() {
      let va = a.as_ref().unwrap().val;
      let vb = b.as_ref().unwrap().val;
      let val = if va < vb {
        a = a.unwrap().next;
        va
      } else {
        b = b.unwrap().next;
        vb
      };
      tail = Solution::list_append(tail, val);
    }

    while a.is_some() {
      tail = Solution::list_append(tail, a.as_ref().unwrap().val);
      a = a.unwrap().next;
    }

    while b.is_some() {
      tail = Solution::list_append(tail, b.as_ref().unwrap().val);
      b = b.unwrap().next;
    }

    head 
  }
}

pub fn main() {}
