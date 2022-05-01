#include <algorithm>
#include <ciso646>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

/* there's nothing tricky about this problem, except that you need a lot of
 * patience and attention to detail: read the description carefully. */

int main() {
  ios_base::sync_with_stdio(false);

  int T;
  cin >> T;
  while (T--) {
    int N;
    cin >> N; /* number of staions */
    int S;
    cin >> S; /* maximum capacity of my carrier */
    int Q;
    cin >> Q; /* maximum capacity of each station queue*/

    vector<queue<int>> B(N + 1); /* the station B queues */
    stack<int> s;                /* the cargo carrier */

    int left_to_deliver = 0, delivered = 0;

    for (int i = 1; i <= N; ++i) {
      int Qi;
      cin >> Qi;
      left_to_deliver += Qi;
      for (int j = 0; j < Qi; ++j) {
        int d;
        cin >> d;
        B[i].push(d);
      }
    }

    int i = 1;    /* the current station */
    int time = 0; /* total time it has taken so far */

    while (delivered < left_to_deliver) {
      /* unloading */
      while (s.size() and (s.top() == i or s.top() != i and B[i].size() < Q)) {
        /* deliver box i to station i */
        while (s.size() and s.top() == i) {
          ++delivered;
          s.pop();
          time += 1; /* operation takes 1 min */
        }

        /* put box != i in queue B[i] */
        while (s.size() and s.top() != i and B[i].size() < Q) {
          B[i].push(s.top());
          s.pop();
          time += 1; /* operation takes 1 min */
        }
      }

      /* loading */
      while (s.size() < S and B[i].size()) {
        /* put item in queue B[i] to the top of the stack*/
        s.push(B[i].front());
        B[i].pop();
        time += 1; /* operation takes 1 min */
      }

      /* if there's still stuff to deliver, move to next station */
      if (delivered < left_to_deliver) {
        time += 2;
        i = (i % N) + 1;
      }
    }

    cout << time << endl;
  }
}