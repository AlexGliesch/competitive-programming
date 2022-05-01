#include <ciso646>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

vector<bool> used;
vector<string> v;
set<string> tried;
int length_sum;

bool try_file(const string &s, int i, int num_used) {
  if (i == v.size())
    return num_used == i;
  if (used[i])
    return try_file(s, i + 1, num_used);
  for (int j = 0; j < v.size(); ++j) {
    if (used[j] or j == i)
      continue;
    if (v[j].size() + v[i].size() == length_sum and
        (v[i] + v[j] == s or v[j] + v[i] == s)) {
      used[i] = used[j] = true;
      if (try_file(s, i + 1, num_used + 2))
        return true;
      used[i] = used[j] = false;
    }
  }
  return false;
}

int main() {
  int T;
  cin >> T;
  string input, ans;
  getline(cin, input);
  getline(cin, input);
  for (int t = 0; t < T; ++t) {
    v.clear();
    length_sum = 0;
    while (getline(cin, input), input.size()) {
      length_sum += input.size();
      v.emplace_back(move(input));
    }
    used.assign(v.size(), false);
    tried.clear();
    length_sum = (2 * length_sum) / v.size();
    for (int i = 1; i < v.size(); ++i) {
      if (v[i].size() + v[0].size() == length_sum) {
        used[0] = used[i] = true;
        auto s1 = v[i] + v[0], s2 = v[0] + v[i];
        if (tried.count(s1) == 0 and try_file(s1, 1, 2)) {
          ans = move(s1);
          goto leave;
        } else if (tried.count(s2) == 0 and try_file(s2, 1, 2)) {
          ans = move(s2);
          goto leave;
        }
        tried.insert(s1), tried.insert(s2);
        used[0] = used[i] = false;
      }
    }
  leave:;
    if (t)
      cout << endl;
    cout << ans << endl;
  }
}