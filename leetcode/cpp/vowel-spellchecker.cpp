class Solution {
public:  
  string toLowercase(string s) {
    for (char& c : s) if (c >= 'A' && c <= 'Z') c = c - ('A' - 'a');
    return s;
  }
  
  string vowelsStripped(string s) {
    s = toLowercase(s);
    for (char& c : s) if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') c = '_';
    return s;
  }
  
  vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
    unordered_map<string, vector<string>> lowercase;
    unordered_map<string, vector<string>> vowels;
    unordered_set<string> wl;
    for (const auto& s : wordlist) {
      wl.insert(s);      
      lowercase[toLowercase(s)].push_back(s);
      vowels[vowelsStripped(s)].push_back(s);            
    }
    vector<string> ans(queries.size());
    for (int i = 0; i < queries.size(); ++i) {
      const auto& s = queries[i];
      if (wl.count(s)) ans[i] = s;
      else if (lowercase.count(toLowercase(s))) ans[i] = lowercase[toLowercase(s)][0];
      else if (vowels.count(vowelsStripped(s))) ans[i] = vowels[vowelsStripped(s)][0];
      else ans[i] = "";      
    }    
    return ans;
  }
};