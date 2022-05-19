/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:  
  pair<bool, pair<int, int>> bst(TreeNode* n) {
    if (n == nullptr) 
      return pair(true, pair(INT_MAX, INT_MIN));
    auto l = bst(n->left), r = bst(n->right);
    if (l.first && r.first &&
        (n->left == nullptr || l.second.second < n->val) && 
        (n->right == nullptr || r.second.first > n->val))
      return pair(true, pair(min(n->val, l.second.first), 
                             max(n->val, r.second.second)));
    return pair(false, pair(INT_MIN, INT_MAX));
  }
  
  bool isValidBST(TreeNode* n) {
    return bst(n).first;
  }
};