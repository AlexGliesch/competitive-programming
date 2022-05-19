class Solution {
public:
  vector<int> cw;
  
  Solution(vector<int>& w) {    
    cw = w;
    for (int i = 1; i < w.size(); ++i) cw[i] += cw[i - 1];    
  }

  int pickIndex() {    
    int r = rand() % cw.back();    
    auto it = upper_bound(begin(cw), end(cw), r);
    // cout << "r " << r << ", it " << it - begin(cw) << endl;
    assert(it != end(cw));
    return it - begin(cw);
  }
};
// c  [5, 1,  2,  8,  4,  10]
// cw [5, 6,  8,  16, 20, 30]
// r = rand(0, 30)? or rand(0, 31)? or rand(0, 29)?
// find first element which is >= r 
//

// c  [1, 3]
// cw [1, 4]
// r = rand() % 4
// r = 0     -> 0 
// r = 1,2,3 -> 1



/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */