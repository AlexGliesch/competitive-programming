#include <ciso646>
#include <iostream>
#include <unordered_map>

using namespace std;
using ull = unsigned long long;

/*
 * for each integer, keep the position where it last appeared.
 *
 * have two pointers p1 and p2, iterating over the range: p2 is the current
 *
 * index being analyzed, and p1 points to one position after the last occurence
 * of a repeated number.
 *
 * at each iteration, add to the result the difference between p1 and p2.
 * */

int main() {
  ios_base::sync_with_stdio(false);
  int T;
  cin >> T;
  while (T--) {
    int N;
    cin >> N;
    unordered_map<ull, int> last;
    int p1 = 0;
    ull ans = 0;
    for (int p2 = 0; p2 < N; ++p2) {
      ull x;
      cin >> x;
      ans += (p2 - p1);
      if (last.count(x) and last[x] >= p1) {
        p1 = 1 + last[x];
      }
      last[x] = p2;
    }
    cout << ans + (N - p1) << endl;
  }
}
