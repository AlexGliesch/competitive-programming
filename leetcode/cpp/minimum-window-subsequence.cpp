class Solution {
public:
  
  int dp[101][20001];
  int minSubseq(int i, int j, const string& s1, const string& s2) {
    if (i == s2.size()) return j;
    if (j == s1.size()) return -1;    
    if (dp[i][j] != -1) return dp[i][j];
    if (s1[j] == s2[i]) return dp[i][j] = minSubseq(i+1, j+1, s1, s2);
    else return dp[i][j] = minSubseq(i, j+1, s1, s2);
  }
  
  string minWindow(string s1, string s2) {
    if (s2.size() > s1.size() or s2.size() == s1.size() and s2 != s1) return "";    
    memset(dp, -1, sizeof(dp));
    string ans;
    for (int i = 0; i < s1.size(); ++i)
      if (s1[i] == s2[0]) {
        int j = minSubseq(0, i, s1, s2);
        if (j != -1) {
          auto s = string(s1.begin()+i, s1.begin()+j); 
          if (ans.empty() or s.size() < ans.size()) ans = s;
        }
      }
    return ans;
  }
};