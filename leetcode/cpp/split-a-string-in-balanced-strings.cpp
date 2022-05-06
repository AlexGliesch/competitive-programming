class Solution {
public:
  int balancedStringSplit(string s) {
    int nr = 0, nl = 0;
    int ans = 0;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] == 'R') ++nr; else ++nl;
      if (nl == nr) ++ans;
    }
    return ans;
  }
};