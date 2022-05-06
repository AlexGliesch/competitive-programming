/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */

// After reading other solutions I realize my solution is awful

class Solution {
public:
  unordered_map<TreeNode*, int> dp[2];

  int lc2(TreeNode* node, bool incr) {
    if (node == nullptr) return 0;
    if (dp[incr].count(node)) return dp[incr][node];
    int v = node->val, lv = node->left ? node->left->val : INT_MAX,
        rv = node->right ? node->right->val : INT_MAX;
    int l = ((incr && v + 1 == lv) || (!incr && lv == v - 1))
                ? lc2(node->left, incr)
                : 0;
    int r = ((incr && v + 1 == rv) || (!incr && rv == v - 1))
                ? lc2(node->right, incr)
                : 0;
    return dp[incr][node] = max(r, l) + 1;
  }

  int longestConsecutive(TreeNode* root) {
    if (root == nullptr) return 0;
    int ans = 1;

    int v = root->val, lv = root->left ? root->left->val : INT_MAX,
        rv = root->right ? root->right->val : INT_MAX;

    int leftIncr =
        (v + 1 == lv ? 1 : (v - 1 == lv ? 0 : -1)); // 1 incr 0 decr -1 nada
    int rightIncr =
        (v + 1 == rv ? 1 : (v - 1 == rv ? 0 : -1)); // 1 incr 0 decr -1 nada

    int l = left && leftIncr != -1 ? lc2(root->left, leftIncr) : 0;
    int r = right && rightIncr != -1 ? lc2(root->right, rightIncr) : 0;

    if (leftIncr != -1 && leftIncr == rightIncr)
      ans += max(l, r);
    else {
      if (leftIncr != -1) ans += lc2(root->left, leftIncr);
      if (rightIncr != -1 && rightIncr != leftIncr)
        ans += lc2(root->right, rightIncr);
    }

    return max(ans, max(longestConsecutive(root->left),
                        longestConsecutive(root->right)));
  }
};