#include "includes.h"

class Solution {
public:
  bool intersect(const vector<int>& a, const vector<int>& b) {
    return a[0] >= b[0] && a[0] <= b[1] || a[1] >= b[0] && a[1] <= b[1];
  }

  vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList,
                                           vector<vector<int>>& secondList) {
    auto a = firstList, b = secondList;
    if (a.empty() || b.empty()) return {};

    sort(begin(a), end(a)), sort(begin(b), end(b));

    vector<vector<int>> ans;

    int i = 0, j = 0;
    while (true) {
      while (i < a.size() && j < b.size() && !intersect(b[j], a[i]) &&
             !intersect(a[i], b[j])) {
        if (a[i][0] < b[j][0])
          ++i;
        else
          ++j;
      }
      if (i == a.size() || j == b.size()) break;

      int from = max(a[i][0], b[j][0]);
      int to = min(a[i][1], b[j][1]);
      vector<int> v;
      v.push_back(from), v.push_back(to);
      ans.push_back(v);

      if (to == a[i][1]) ++i;
      if (to == b[j][1]) ++j;
    }

    // merge successive intervals with same end/beg
    vector<vector<int>> merged;
    for (size_t i = 0; i < ans.size(); ++i) {
      if (i < ans.size() - 1 && ans[i][1] == ans[i + 1][0]) {
        vector<int> v;
        v.push_back(ans[i][0]), v.push_back(ans[i + 1][1]);
        merged.push_back(v);
        ++i;
      } else {
        merged.push_back(ans[i]);
      }
    }
    return merged;
  }
};