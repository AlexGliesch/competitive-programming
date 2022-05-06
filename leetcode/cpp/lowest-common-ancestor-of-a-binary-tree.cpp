/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
  unordered_set<int> hasp, hasq;
  bool computeHas(TreeNode* node, int val, unordered_set<int>& has) {
    if (node == nullptr) return false;
    if (node->val == val || computeHas(node->left, val, has) || computeHas(node->right, val, has)) {
      has.insert(node->val);
      return true;
    }
    return false;
  }
  
  TreeNode* lcaRecursive(TreeNode* node, TreeNode* p, TreeNode* q) {
    for (auto c : {node->left, node->right})
      if (c != nullptr && hasp.count(c->val) && hasq.count(c->val)) 
        return lcaRecursive(c, p, q);
    return node;
  }
  
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    computeHas(root, p->val, hasp);
    computeHas(root, q->val, hasq);
    return lcaRecursive(root, p, q);
  }
};