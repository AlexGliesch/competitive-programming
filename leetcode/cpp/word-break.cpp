class Solution {
  string s;
  int maxWordSize;
  unordered_set<string> words;
  vector<bool> visited;
  
  bool dfs(int i) {    
    string r;
    if (i == s.size()) return true;
    if (visited[i]) return false;
    visited[i] = true;
    for (int j = i; j < s.size() && r.size() <= maxWordSize; ++j) {
      r.push_back(s[j]);
      if (words.count(r) && dfs(j+1)) return true;
    }
    return false;
  }

public:
  bool wordBreak(string s, vector<string>& wordDict) {
    maxWordSize = 0;    
    for (const auto& s : wordDict) {
      words.insert(s);
      maxWordSize = max(maxWordSize, (int)s.size());
    }
    this->s = s;
    visited.assign(s.size(), false);
    return dfs(0);
  }
};