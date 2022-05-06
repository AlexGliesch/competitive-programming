#include "includes.h"

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

class Solution {
public:
  // find depth of a branch, store in `val`
  int findMaxDepth(TreeNode* node, vector<int>& md) {
    if (node == nullptr) return 0;
    md[node->val] =
        1 + max(findMaxDepth(node->right, md), findMaxDepth(node->left, md));
    return md[node->val];
  }

  TreeNode* lcaDeepestLeavesAux(TreeNode* root, const vector<int>& md) {
    assert(root != nullptr);
    if (root->right == nullptr && root->left == nullptr) return root;
    if (root->right != nullptr && root->left != nullptr) {
      if (md[root->right->val] == md[root->left->val])
        return root;
      else if (md[root->right->val] > md[root->left->val])
        return lcaDeepestLeaves(root->right);
      else
        return lcaDeepestLeaves(root->left);
    } else if (root->right == nullptr)
      return lcaDeepestLeaves(root->left);
    else
      return lcaDeepestLeaves(root->right);
  }

  TreeNode* lcaDeepestLeaves(TreeNode* root) {
    vector<int> md(1001, 0);
    findMaxDepth(root, md);
    return lcaDeepestLeavesAux(root, md);
  }
};