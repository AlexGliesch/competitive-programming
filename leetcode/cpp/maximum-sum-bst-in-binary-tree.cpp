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
  unordered_map<TreeNode*, int> sumdp, smalldp, largedp, bstdp;
  
  int sum(TreeNode* root) {
    if (root == nullptr) return 0;
    if (sumdp.count(root)) return sumdp[root];
    return sumdp[root] = root->val + sum(root->left) + sum(root->right);
  }
  
  int smallest(TreeNode* root) {
    if (root == nullptr) return INT_MAX;
    if (smalldp.count(root)) return smalldp[root];
    return smalldp[root] = min(root->val, min(smallest(root->left), smallest(root->right)));
  }
  
  int largest(TreeNode* root) {
    if (root == nullptr) return INT_MIN;
    if (largedp.count(root)) return largedp[root];
    return largedp[root] = max(root->val, max(largest(root->left), largest(root->right)));
  }
  
  bool bst(TreeNode* root) {
    if (root == nullptr) return true;
    if (bstdp.count(root)) return bstdp[root];
    return bstdp[root] = ((root->left == nullptr || largest(root->left) < root->val) 
                          && (root->right == nullptr || smallest(root->right) > root->val) 
                          && bst(root->left) && bst(root->right));
  }
  
  int maxSumBST(TreeNode* root) {
    if (root == nullptr) return 0;
    int ans = max(maxSumBST(root->left), maxSumBST(root->right));
    if (bst(root)) ans = max(ans, sum(root->left) + sum(root->right) + root->val);
    return ans;
  }
};