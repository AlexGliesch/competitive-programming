#include "includes.h"

// Definition for a binary tree node.
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
  int rec(TreeNode* node, int& best) {
    // go either left, or right
    int c = node->val, l = 0, r = 0;
    if (node->left) l = rec(node->left, best);
    if (node->right) r = rec(node->right, best);
    best = max(best, c + max(l, 0) + max(r, 0));
    return max(c, c + max(l, r));
  }

  int maxPathSum(TreeNode* root) {
    int best = -numeric_limits<int>::max();
    rec(root, best);
    return best;
  }
};

int main() {}