#include <algorithm>
#include <bitset>
#include <ciso646>
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

/* Very simple problem, naive solution works: use each data structure,
 * push/pop the elements and check if the results are equal.
 *
 * Important: if you call pop() on an empty container C++ gives undefined
 * behaviour! */

int main() {
  int n;
  while (cin >> n) {
    stack<int> s;
    queue<int> q;
    priority_queue<int> pq;
    bitset<3> can("111");
    for (int i = 0; i < n; ++i) {
      int mode, v;
      cin >> mode >> v;
      if (mode == 1) {
        s.push(v), q.push(v), pq.push(v);
      } else {
        if (s.size()) {
          can[0] = can[0] and s.top() == v;
          can[1] = can[1] and q.front() == v;
          can[2] = can[2] and pq.top() == v;
          s.pop(), q.pop(), pq.pop();
        } else
          can.reset();
      }
    }
    if (can.none())
      cout << "impossible" << endl;
    else if (can.count() > 1)
      cout << "not sure" << endl;
    else if (can[0])
      cout << "stack" << endl;
    else if (can[1])
      cout << "queue" << endl;
    else if (can[2])
      cout << "priority queue" << endl;
  }
}