class Solution {
  // rec(time, i1, i2, i3) 
  //  note that i2 = i3 - i1 so we only need to dp [time][i1][i3]
  //  if i3 = s3.size() 
  //    return true
  //  if dp[time][i1][i3]
  //    return false 
  //  j = 0
  //  if time == 1
  //    while i1 + j < s1.size() && i3 + j < s3.size() && s1[i1 + j] == s3[i3 + j]
  //      if rec(1 - time, i1 + j + 1, i2, i3 + j + 1)
  //        return true
  //      ++j
  //  else
  //    while i2 + j < s2.size() && i3 + j < s3.size() && s2[i2 + j] == s3[i3 + j]
  //      if rec(1 - time, i1, i2 + j + 1, i3 + j + 1)
  //        return true
  //      ++j
  //  dp[time][i1][i3] = true
  //  return false
  int dp[2][101][201];
  string s1, s2, s3;
  
  int dfs(int time, int i1, int i2, int i3) {    
    assert(i2 == i3 - i1); 
    assert(time == 0 || time == 1);
    if (i3 == s3.size())
      return true;
    if (dp[time][i1][i3])
      return false;
    int j = 0;
    if (time == 1) {
      while (i1 + j < s1.size() && i3 + j < s3.size() && s1[i1 + j] == s3[i3 + j]) {
        if (dfs(1 - time, i1 + j + 1, i2, i3 + j + 1))
          return true;
        ++j;
      }
    } else {
      while (i2 + j < s2.size() && i3 + j < s3.size() && s2[i2 + j] == s3[i3 + j]) {
        if (dfs(1 - time, i1, i2 + j + 1, i3 + j + 1))
          return true;
        ++j;
      }
    }
    dp[time][i1][i3] = 1;
    return false;
  }
  
public:    
  bool isInterleave(string s1, string s2, string s3) {
    if (s3.size() != s1.size() + s2.size()) 
      return false;
    this->s1 = s1, this->s2 = s2, this->s3 = s3;
    memset(dp, 0, sizeof(dp));
    return dfs(0, 0, 0, 0) || dfs(1, 0, 0, 0);
  }
};