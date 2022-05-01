#include <functional>
#include <iostream>
#include <queue>

using namespace std;

/* You can get the minimum cost by greedily always adding the smallest
 * two elements in the set of numbers, and adding the result to the set
 * of numbers. This can be achieved by using a std::priority_queue. */

int main() {
  int n;
  while (cin >> n, n) {
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < n; ++i) {
      int x;
      cin >> x;
      pq.push(x);
    }
    int x, res = 0;
    while (pq.size()) {
      x = pq.top();
      pq.pop();
      if (pq.empty())
        break;
      x += pq.top();
      pq.pop();
      res += x;
      pq.push(x);
    }
    cout << res << endl;
  }
}