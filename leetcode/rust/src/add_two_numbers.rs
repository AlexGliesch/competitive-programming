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
    *r = Some(Box::new(ListNode::new(val)));
    &mut r.as_mut().unwrap().next
  }

  pub fn add_two_numbers(
    l1: Option<Box<ListNode>>,
    l2: Option<Box<ListNode>>,
  ) -> Option<Box<ListNode>> {
    let mut head = None;
    let mut tail = &mut head;
    let mut carry = 0;
    let mut l1 = &l1;
    let mut l2 = &l2;

    while l1.is_some() || l2.is_some() {
      let mut n = carry;

      if let Some(n1) = l1 {
        n += n1.val;
        l1 = &n1.next;
      }
      if let Some(n2) = l2 {
        n += n2.val;
        l2 = &n2.next;
      }

      tail = Solution::list_append(tail, n % 10);
      carry = n / 10;
    }

    if carry > 0 {
      Solution::list_append(tail, carry);
    }

    head
  }
}

pub fn main() {}
