#include <algorithm>
#include <ciso646>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* The input isn't trivial: watch out during parsing.
 *
 * Solve it using a slightly modified dfs.
 *
 * Don't forget to print the candles in the order they were placed, not in
 * alphabetical order.*/

vector<vector<int>> g;
vector<bool> lit;
int theseus, mino, k;

int main() {
  string s;
  while (getline(cin, s)) {
    if (s == "#")
      break;
    g.clear();
    g.resize(255);
    lit.assign(255, false);
    int n = 0;
    int i = 0;
    while (s[i] != ' ') {
      int v = s[i] - 'A';
      i += 2;
      while (s[i] != ';' and s[i] != '.')
        g[v].push_back(s[i++] - 'A');
      ++i;
      n = std::max(n, v + 1);
    }
    mino = s[i + 1] - 'A', theseus = s[i + 3] - 'A';
    k = atoi(s.data() + i + 5);
    int k_count = 0;
    bool trapped = false;
    while (not trapped) {
      trapped = true;
      for (int i = 0; i < g[mino].size(); ++i) {
        if (g[mino][i] != theseus and not lit[g[mino][i]]) {
          theseus = mino;
          mino = g[mino][i];
          ++k_count;
          trapped = false;
          break;
        }
      }
      if (k_count >= k) {
        k_count = 0;
        if (not lit[theseus])
          cout << char(theseus + 'A') << " ";
        lit[theseus] = true;
      }
    }
    cout << "/" << char(mino + 'A') << endl;
  }
}