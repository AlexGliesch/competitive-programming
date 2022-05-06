#include "includes.h"

class Solution {
public:
  bool isSelfDividing(int x) {
    int y = x;
    while (y > 0) {
      int dig = y % 10;
      if (dig == 0 || x % dig != 0) return false;
      y /= 10;
    }
    return true;
  }

  vector<int> selfDividingNumbers(int left, int right) {
    vector<int> ans;
    for (int i = left; i <= right; ++i) {
      if (isSelfDividing(i)) ans.push_back(i);
    }
    return ans;
  }
};