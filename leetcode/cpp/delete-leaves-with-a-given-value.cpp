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
    TreeNode* removeLeafNodes(TreeNode* n, int target) {
      if (n == nullptr) return nullptr;
      
      auto left = removeLeafNodes(n->left, target);
      auto right = removeLeafNodes(n->right, target);
      
      if (!left && !right && n->val == target)
        return nullptr;           
        
      TreeNode* a = new TreeNode(n->val);
      a->left = left;
      a->right = right;
      a->val = n->val;
      return a;
    }
};