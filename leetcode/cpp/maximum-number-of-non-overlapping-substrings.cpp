class Solution {
public:
  // For every char c, record indices beg[c] and end[c]
  // Remember that beg[c] and end[c] must consider beg/end of intermediate characters
  // Select maximum number of ranges (beg, end) that do not overlap... 
  // 
  // dfs(i):
  //    - either add range [beg[s[i]], end[s[i]]], or skip i
  //    - if i is not beg[s[i]], always skip i
  //    - returns the number of ranges that can be added after (incl.) i
  //    - DP it 
  //    - actually: dfs result is a pair (max strings, min strings length)
  vector<int> beg, end, parent;
  string s;
  vector<pair<int, int>> dp;
  
  pair<int, int> dfs(int i) {
    if (i >= s.size()) return pair(0, 0);
    if (dp[i] != pair(-1, -1)) return dp[i];
    auto a1 = i == beg[s[i]] ? pair(1 + dfs(1 + end[s[i]]).first, 
                                    -(end[s[i]] - beg[s[i]] + 1) + dfs(1 + end[s[i]]).second) 
                             : pair(0, INT_MIN);
    auto a2 = dfs(i + 1);
    dp[i] = max(a1, a2);
    parent[i] = (a1 == dp[i] ? 1 + end[s[i]] : i + 1);
    return dp[i];
  }  
  
  vector<string> maxNumOfSubstrings(string s) {
    this->s = s;
    dp.assign(s.size(), pair(-1, -1));
    parent.assign(s.size(), -1);
    beg.assign(255, -1);
    end.assign(255, -1);    
    for (int i = 0; i < s.size(); ++i) if (beg[s[i]] == -1) beg[s[i]] = i;
    for (int i = s.size() - 1; i >= 0; --i) if (end[s[i]] == -1) end[s[i]] = i;
    for (int c = 'a'; c <= 'z'; ++c) if (beg[c] != -1) {
      for (int i = beg[c] + 1; i <= end[c] - 1; ++i) {
        beg[c] = min(beg[s[i]], beg[c]);
        end[c] = max(end[s[i]], end[c]);          
      }
    }    
    dfs(0);
    vector<string> ans;
    int i = 0;
    while (i < s.size()) {
      if (i == beg[s[i]] && parent[i] - 1 == end[s[i]]) 
        ans.emplace_back(s.begin() + i, s.begin() + parent[i]);              
      i = parent[i];
    }
    return ans;
  }
};