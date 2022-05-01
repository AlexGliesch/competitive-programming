#include "includes.h"

class Solution {
public:
  int hIndex(vector<int>& citations) {
    set<int> uniqueC;
    for (int i : citations)
      uniqueC.insert(i);

    vector<int> sortedC = citations;
    sort(begin(sortedC), end(sortedC));

    int h = 0;
    for (int c : uniqueC) {
      auto it = lower_bound(begin(sortedC), end(sortedC), c);
      // cout << c << " " << sortedC.size() - (it - sortedC.begin()) << endl;
      h = max(h, min(c, int(sortedC.size() - (it - sortedC.begin()))));
    }
    return h;
  }
};

// h-index is the maximum h such that there are h papers with h or more
// citations sort citations for every distinct number of citations c:
//    find number of papers with >=citations than c by binary search
//    update best value