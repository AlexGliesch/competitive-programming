/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* h = nullptr, *n = nullptr;
    int carry = 0;
    while (!(l1 == nullptr && l2 == nullptr)) {
      int i = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;
      carry = i / 10;      
      if (h == nullptr) {
        n = new ListNode(i % 10);
        h = n;
      } else {
        n->next = new ListNode(i % 10);
        n = n->next;
      }      
      if (l1) l1 = l1->next;
      if (l2) l2 = l2->next;
    }
    if (carry > 0) {
      assert(carry >= 1 && carry <= 9);
      n->next = new ListNode(carry);
    }
    return h;
  }
};