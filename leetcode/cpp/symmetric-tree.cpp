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
  void lnr(TreeNode* n, vector<int>& v) {
    if (n == nullptr) {
      v.push_back(numeric_limits<int>::max());
    } else if (n->left == nullptr && n->right == nullptr) {
      v.push_back(n->val);
    } else {
      lnr(n->left, v);
      lnr(n->right, v);      
      v.push_back(n->val);
    }
  }
  
  void rnl(TreeNode* n, vector<int>& v) {
    if (n == nullptr) {
      v.push_back(numeric_limits<int>::max());
    } else if (n->left == nullptr && n->right == nullptr) {
      v.push_back(n->val);
    } else {
      rnl(n->right, v);          
      rnl(n->left, v);    
      v.push_back(n->val);
    }
  }
  
  bool isSymmetric(TreeNode* root) {
    if (root == nullptr) return true;
    vector<int> l, r;
    lnr(root->left, l);
    rnl(root->right, r);
    return l == r;    
  }
};