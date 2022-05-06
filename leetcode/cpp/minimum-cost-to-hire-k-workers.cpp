#include "includes.h"

class Solution {
public:
  double mincostToHireWorkers(vector<int>& q, vector<int>& w, int k) {
    vector<int> byRatio(q.size());
    iota(begin(byRatio), end(byRatio), 0);
    sort(begin(byRatio), end(byRatio), [&](int i, int j) {
      return w[i] / double(q[i]) < w[j] / double(q[j]);
    });

    priority_queue<double> qSelected; // list of current smallest k qualities
    double qCumSum = 0.0;             // sum of current smallest k qualities
    double ans = numeric_limits<double>::max();
    for (size_t ii = 0; ii < q.size();
         ++ii) { // every previous element has a ratio less than ratio(i)!
      int i = byRatio[ii];
      assert(qSelected.size() <= k);
      if (qSelected.size() < k) { // less than k, fine, add to queue
        qCumSum += q[i];
        qSelected.push(q[i]);
      } else if (q[i] < qSelected.top()) { // update queue top
        qCumSum -= qSelected.top();
        qCumSum += q[i];
        qSelected.pop();
        qSelected.push(q[i]);
      }
      if (qSelected.size() == k) {
        double ratio = (w[i] / double(q[i]));
        // cout << i << " " << ratio << " " << qCumSum << endl;
        ans = min(ans, qCumSum * ratio);
      }
    }
    return ans;
  }
};
