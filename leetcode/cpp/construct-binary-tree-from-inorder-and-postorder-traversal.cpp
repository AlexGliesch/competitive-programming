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
  // postorder: lrn
  // inorder: lnr
  TreeNode* buildTreeRec(int ia, int ib, int pa, int pb, 
                         const vector<int>& inorder, 
                         const vector<int>& postorder,
                         unordered_map<int, int>& iindex) {
    if (ia > ib or pa > pb) return nullptr;
    TreeNode* node = new TreeNode(postorder[pb]);     
    if (ib == ia) return node;  
    
    int pos = iindex[node->val]; 
    node->left = buildTreeRec(ia, pos - 1, pa, pa + pos - ia - 1, inorder, postorder, iindex);
    node->right = buildTreeRec(pos + 1, ib, pa + pos - ia, pb - 1, inorder, postorder, iindex);
    return node;
  }
  
  TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    unordered_map<int, int> iindex;
    for (int i = 0; i < inorder.size(); ++i) 
      iindex[inorder[i]] = i;
    return buildTreeRec(0, inorder.size() - 1, 0, inorder.size() - 1, inorder, postorder, iindex);
    // take last element from postOrder
    // left part is everything left of it in inorder
    // right part is everything right of it in inorder
    // left/right parts in post order have same sizes as left/right parts in inorder
  }
};