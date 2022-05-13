class Solution {
public:
  int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
    // Can compute cost of a given submatrix in O(1) 
    // by doing shenanigans with cost matrix from (0,0) to (n,n)
    
    // Basically let C(i,j) = cost from (i,j) to (0,0)
    // then C(x1, x2, y1, y2) = C(x2, y2) + C(x1, y1) - C(x2, y1) - C(x1, y2) 
    
    int C[101][101];
    memset(C, 0, sizeof(C));
    for (int r = 0; r < matrix.size(); ++r) for (int c = 0; c < matrix[0].size(); ++c) {
      C[r][c] = matrix[r][c];
      if (r > 0) C[r][c] += C[r-1][c];
      if (c > 0) C[r][c] += C[r][c-1];
      if (r > 0 && c > 0) C[r][c] -= C[r-1][c-1];
    }
    
    int ans = 0;
    for (int r1 = 0; r1 < matrix.size(); ++r1) for (int c1 = 0; c1 < matrix[0].size(); ++c1)
      for (int r2 = r1; r2 < matrix.size(); ++r2) for (int c2 = c1; c2 < matrix[0].size(); ++c2) {
        bool ok = ((C[r2][c2] + (r1 && c1 ? C[r1-1][c1-1] : 0) - (c1 ? C[r2][c1-1] : 0) - (r1 ? C[r1-1][c2] : 0)) == target);
        ans += ok;
        
      }
    return ans;
    
    // given (x2,y2), can I find easily a (x1,y1) s.t. C(x1,x2,y1,y2) = t?
    // 
    //  
    // t - C(x2,y2) = C(x1, y1) - C(x2, y1) - C(x1, y2) 
    //      k  = a - b - c
    //      a precedes b and c
    //      a is vertically same as b
    //      a is horizontally same as c
    // 
    // x2,y2,x1 - can find best y1 by binary search
    // still 10^6 log(100) = 7 * 10^6
    // doable 
    
    // given a list of integers, how many 4-tuples (a,b,c,d) are there s.t. a+b-c-d=t, also a<b
    
    

  }
};