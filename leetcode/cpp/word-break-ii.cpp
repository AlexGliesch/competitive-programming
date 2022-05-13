class Solution {
public:
  string s;
  int maxWordSize;
  unordered_set<string> words;
  vector<vector<int>> dp;
  vector<bool> visited;
  vector<string> ans;  
  
  bool dfs(int i) {    
    string r;
    if (i == s.size()) return true;
    if (visited[i]) return dp[i].size();
    for (int j = i; j < s.size() && r.size() <= maxWordSize; ++j) {
      r.push_back(s[j]);
      if (words.count(r) && dfs(j+1)) dp[i].push_back(j+1);      
    }
    visited[i] = true;
    return dp[i].size();
  }
  
  void dfs2(int i, string r) {
    if (i >= s.size()) 
      ans.push_back(r);
    else 
      for (int j : dp[i]) 
        dfs2(j, r + string(begin(s) + i, begin(s) + j) + (j == s.size() ? "" : " "));
  }
  
  vector<string> wordBreak(string s, vector<string>& wordDict) {
    maxWordSize = 0;    
    for (const auto& s : wordDict) {
      words.insert(s);
      maxWordSize = max(maxWordSize, (int)s.size());
    }
    this->s = s;
    visited.assign(s.size(), false);
    dp.resize(s.size());
    dfs(0);
    // for (int i = 0; i < s.size(); ++i) { cout << i << ": "; for (int j : dp[i]) cout << j << " "; cout << endl; }
    dfs2(0, "");    
    return ans;
  }
};