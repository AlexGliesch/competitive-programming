class Solution {
public:
  vector<string> commonChars(vector<string>& words) {
    vector<int> freq(255, -1);
    for (const auto& s : words) {
      vector<int> tmp(255, 0);
      for (char c : s) 
        ++tmp[c];
      for (char i = 'a'; i <= 'z'; ++i) 
        freq[i] = (freq[i] == -1 ? tmp[i] : min(freq[i], tmp[i]));
    }
      
      
    vector<string> ans;
    for (char i = 'a'; i <= 'z'; ++i) 
      for (int j = 0; j < freq[i]; ++j) 
        ans.emplace_back(1, i);
    return ans;
  }
};