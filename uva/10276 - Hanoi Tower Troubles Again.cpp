#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

/*
 * greedy: put the numbers on the first possible available peg.
 *
 * test if a number x is square by using
 * r = int(round(sqrt(x))), if (r * r == x)
 *
 * there must be a more intelligent way to detect infinite possibilities
 * (if there indeed exist), but i just checked if the ball number exceeds
 * a very large number (10000000). if so, then i consider it infinite.
 *
*/

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; ++t) {
    int N;
    cin >> N;
    vector<int> top(N, 0);
    int j;
    bool can = true;
    for (j = 1; j < 10000000 && can; ++j) {
      can = false;
      for (int k = 0; k < N; ++k) {
        int x = top[k] + j;
        int r = int(round(sqrt(x)));
        if (top[k] == 0 or x == r * r) {
          top[k] = j;
          can = true;
          break;
        }
      }
    }
    if (j < 10000000)
      cout << j - 2 << endl;
    else
      cout << -1 << endl;
  }
}
