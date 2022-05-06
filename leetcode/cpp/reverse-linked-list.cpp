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
  ListNode* reverseList(ListNode* head) {
    if (head == nullptr) return nullptr;
    vector<int> s;
    auto n = head;
    while (n != nullptr) {
      s.push_back(n->val);
      n = n->next;
    }

    auto newHead = new ListNode();
    n = newHead;
    for (int i = s.size() - 1; i >= 0; --i) {
      n->val = s[i];
      if (i > 0) {
        n->next = new ListNode();
        n = n->next;
      }
    }
    return newHead;
  }
};