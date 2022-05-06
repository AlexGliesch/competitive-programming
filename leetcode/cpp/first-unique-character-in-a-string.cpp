class Solution {
public:
    int firstUniqChar(string s) {
      int freq[255];
      fill(freq, freq+255, 0);
      for (int c : s) ++freq[c];
      for (int i=0; i<s.size(); ++i) if (freq[s[i]] == 1) return i;
      return -1;        
    }
};