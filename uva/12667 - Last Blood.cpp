#include <algorithm>
#include <ciso646>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  int n, t, s;
  cin >> n >> t >> s;
  vector<pair<int, int>> last_blood(n, {-1, -1});
  vector<vector<bool>> solved(t, vector<bool>(n, false));
  for (int i = 0; i < s; ++i) {
    int time, team;
    char problem;
    string verdict;
    cin >> time >> team >> problem >> verdict;
    if (verdict == "No")
      continue;
    if (not solved[team - 1][problem - 'A']) {
      solved[team - 1][problem - 'A'] = true;
      last_blood[problem - 'A'] = make_pair(time, team);
    }
  }
  for (int i = 0; i < n; ++i) {
    cout << (char)('A' + i) << ' ';
    if (last_blood[i].first == -1)
      cout << "- -" << endl;
    else
      cout << last_blood[i].first << ' ' << last_blood[i].second << endl;
  }
}