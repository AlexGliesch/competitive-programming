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
  vector<long long> size, val;
  
  void avgLevelsRecursive(TreeNode* n, int depth) {
    if (n == nullptr) return;
    while (size.size() < depth + 1) {
      assert(size.size() == val.size());
      size.push_back(0);
      val.push_back(0);
    }
    ++size[depth];
    val[depth] += (long long)n->val;
    avgLevelsRecursive(n->right, depth + 1);
    avgLevelsRecursive(n->left, depth + 1);
  }
  
  vector<double> averageOfLevels(TreeNode* root) {
    avgLevelsRecursive(root, 0);    
    vector<double> ans(size.size());
    for (int i = 0; i < size.size(); ++i) ans[i] = val[i] / double(size[i]);
    return ans;
  }
};