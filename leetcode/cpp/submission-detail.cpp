class Solution {
public:
  
  vector<vector<int>> dp;
  
  int maxLines(int i, int j, const vector<int>& n1, const vector<int>& n2) {
    if (i >= n1.size() || j >= n2.size()) 
      return 0;
    if (dp[i][j] != -1) 
      return dp[i][j];
    int ans = (n1[i] == n2[j]) ? 
      1 + maxLines(i+1, j+1, n1, n2) : 
      max(maxLines(i+1, j, n1, n2), maxLines(i, j+1, n1, n2));
    return dp[i][j] = ans;
  } 
  
  int maxUncrossedLines(vector<int>& n1, vector<int>& n2) {
    dp.assign(n1.size(), vector<int>(n2.size(), -1));
    return maxLines(0, 0, n1, n2);
  }
};