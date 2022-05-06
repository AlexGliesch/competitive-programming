#include "includes.h"

class Solution {
public:
  vector<int> findBuildings(vector<int>& heights) {
    vector<int> ans;
    ans.push_back(heights.size() - 1);
    int hi = heights.back();
    for (int i = heights.size() - 2; i >= 0; --i) {
      if (heights[i] > hi) ans.push_back(i);
      hi = max(hi, heights[i]);
    }
    reverse(begin(ans), end(ans));
    return ans;
  }
};