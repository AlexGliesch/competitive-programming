class Solution {
public:
  int romanToInt(string s) {
    int cost[255];
    cost['I'] = 1;
    cost['V'] = 5;
    cost['X'] = 10;
    cost['L'] = 50;
    cost['C'] = 100;
    cost['D'] = 500;
    cost['M'] = 1000;
    int ans = 0;
    for (int i = s.size() - 1; i >= 0; --i) {
      ans += cost[s[i]];
      if (i > 0 && cost[s[i - 1]] < cost[s[i]]) ans -= cost[s[i - 1]], --i;
    }
    return ans;
  }
};