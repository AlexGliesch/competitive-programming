#include <algorithm>
#include <ciso646>
#include <iostream>
#include <vector>

using namespace std;

/*
 * the original position of a racer is the current position + the number of
 * times he passed by someone (or he got passed by).
 *
 * if that position is out of bounds, or two people are mapped to the same
 * position, it constitutes an impossible situation.
 *
 * ps: don't print whitespace at the end of a line.
 * */

int main() {
  int N;
  while (cin >> N, N) {
    vector<pair<int, int>> pole;
    for (int i = 0; i < N; ++i) {
      int c, p;
      cin >> c >> p;
      pole.emplace_back(c, p);
    }

    vector<int> positions(N, -1);
    bool possible = true;
    for (int i = 0; i < N; ++i) {
      int old_pos = i + pole[i].second;
      if (old_pos < 0 or old_pos >= N or positions[old_pos] != -1) {
        possible = false;
        break;
      } else
        positions[old_pos] = pole[i].first;
    }
    if (not possible)
      cout << -1 << endl;
    else {
      for (int i = 0; i < N; ++i) {
        cout << positions[i];
        if (i != N - 1)
          cout << " ";
      }
      cout << endl;
    }
  }
}
