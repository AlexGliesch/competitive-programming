class Solution {
public:
  int n; 
  
  int d1(int r, int c) { return r+c; }
  int d2(int r, int c) { return r-c+n-1; }
  
  int dfs(int r, int fc, int fd1, int fd2) {
    if (r == n) return 1;
    int ans = 0;    
    for (int c = 0; c < n; ++c)
      if ((fc & (1<<c)) && (fd1 & (1<<d1(r,c))) && (fd2 & (1<<d2(r,c))))
        ans += dfs(r+1, fc & ~(1<<c), fd1 & ~(1<<d1(r,c)), fd2 & ~(1<<d2(r,c)));      
    return ans;
  }
  
  int totalNQueens(int n) {
    this->n = n;
    return dfs(0, -1, -1, -1);
  }
};