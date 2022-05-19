class Solution {
public:
  string tolowercase(string s) {
    for (char& c : s) c = tolower(c);
    return s;
  }
  
  string mostCommonWord(string paragraph, vector<string>& banned) {
    sort(begin(banned), end(banned));
    map<string, int> freq;
    int p1 = 0;
    while (p1 < paragraph.size()) {
      int p2 = paragraph.find_first_of(" !?\',;.\"", p1);
      if (p2 == string::npos) p2 = paragraph.size();      
      string s = tolowercase(paragraph.substr(p1, p2 - p1));
      if (!s.empty() && binary_search(begin(banned), end(banned), s) == false) {
        ++freq[s];
      }      
      p1 = p2 + 1;
    }
    pair<string, int> ans("", -1);
    for (auto p : freq) if (p.second > ans.second) ans = p;    
    return ans.first;
  }
};