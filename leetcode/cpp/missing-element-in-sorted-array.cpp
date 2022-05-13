class Solution {
public:
  int missingElement(vector<int>& s, int k) {
    // log n solution:
    // a b c
    // missing numbers between b and a is s[b] - s[a] - b + a = Mab
    // missing numbers between c and b is s[c] - s[b] - c + b = Mcb
    // 
    // if 1 <= k <= Mab --> binary search go left
    // else if Mab < k <= Mab+Mcb --> binary search go right 
    
    int mac = s.back() - s[0] - (s.size()-1);
    if (k > mac) return k - mac + s.back();
      
    for (int i = 0; i < s.size()-1; ++i) {
      int m = s[i+1] - s[i] - (i+1) + i;      
      if (m >= k) return s[i]+k;
      k -= m;
    }
    return 0;  
  }
};