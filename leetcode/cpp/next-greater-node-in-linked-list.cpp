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
  vector<int> nextLargerNodes(ListNode* head) {
    vector<int> ans;
    priority_queue<pair<int, int>, 
                   vector<pair<int, int>>, 
                   greater<pair<int, int>>> q; // (val, i)
    
    int i = 0;
    auto n = head;
    while (n != nullptr) {
      while (!q.empty() && n->val > q.top().first) {
        while (q.top().second + 1 > ans.size()) ans.push_back(0);
        ans[q.top().second] = n->val;
        q.pop();
      }
      q.emplace(n->val, i);
      ++i;
      n = n->next;
    }
    while (ans.size() < i) ans.push_back(0);
    return ans;
  }
};