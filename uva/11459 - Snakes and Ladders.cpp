#include <algorithm>
#include <ciso646>
#include <iostream>
#include <vector>

using namespace std;

/* Easy problem, you just need to follow the rules of the game.
 * Store the jumps in a vector that says where a certain position
 * will jump to.
 * Store the positions of each player in a vector.
 * Don't let ayone go over 100. */

int main() {
  ios_base::sync_with_stdio(false);
  int T;
  cin >> T;
  vector<int> jumps(101, 0);
  for (int t = 0; t < T; ++t) {
    jumps.assign(101, 0);
    int a, b, c;
    cin >> a >> b >> c;
    for (int i = 0; i < b; ++i) {
      int from, to;
      cin >> from >> to;
      jumps[from] = to;
    }
    vector<int> pos(a, 1);
    bool ended = false;
    for (int i = 0; i < c; ++i) {
      int die;
      cin >> die;
      if (not ended) {
        pos[i % a] = min(100, pos[i % a] + die);
        if (jumps[pos[i % a]])
          pos[i % a] = jumps[pos[i % a]];
        if (pos[i % a] >= 100)
          ended = true;
      }
    }
    for (int i = 0; i < a; ++i) {
      cout << "Position of player " << i + 1 << " is " << pos[i] << "." << endl;
    }
  }
}
