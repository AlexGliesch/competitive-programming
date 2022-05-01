#include <functional>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

/* Find all solutions vial backtracking. There are going to be a lot of
 * duplicate solutions. In order to remove them, I used a set<vector<int>>,
 * with greater<int> as comparison. */

int v[12], t, n;
vector<int> sols;

void backtrack(int i, int sum, int mask) {
  if (sum > t)
    return;
  if (sum == t)
    sols.push_back(mask);
  if (i == n)
    return;
  backtrack(i + 1, sum, mask);
  backtrack(i + 1, sum + v[i], mask | (1 << i));
}

int main() {
  while (cin >> t >> n, n != 0) {
    for (int i = 0; i < n; ++i)
      cin >> v[i];
    sols.clear();
    backtrack(0, 0, 0);
    cout << "Sums of " << t << ":" << endl;
    if (sols.empty())
      cout << "NONE" << endl;

    else {
      set<vector<int>, greater<vector<int>>> unique_sols;
      for (int i = 0; i < sols.size(); ++i) {
        vector<int> sol;
        for (int j = 0; j < n; ++j) {
          if (sols[i] & (1 << j))
            sol.push_back(v[j]);
        }
        unique_sols.insert(sol);
      }

      for (set<vector<int>>::iterator i = unique_sols.begin();
           i != unique_sols.end(); ++i) {
        bool first = true;
        for (int j = 0; j < i->size(); ++j) {
          if (!first)
            cout << "+";
          first = false;
          cout << (*i)[j];
        }
        cout << endl;
      }
    }
  }
}