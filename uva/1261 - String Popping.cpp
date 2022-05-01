#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

/* DP bem simples, basta fazer a recursao de ir tentando contrair a string,
 * e depois memoizar */

unordered_map<string, bool> dp;

bool can(const string &s) {
  if (s.empty())
    return true;
  if (dp.find(s) != dp.end())
    return dp[s];
  for (size_t i = 0; i < s.size() - 1; ++i) {
    if (s[i] == s[i + 1]) {
      size_t j = s.find_first_not_of(s[i], i);
      auto s_new = s.substr(0, i);
      if (j != string::npos)
        s_new += s.substr(j);
      if (can(s_new))
        return dp[s_new] = dp[s] = true;
      i = j - 1;
    }
  }
  return dp[s] = false;
}

int main() {
  ios_base::sync_with_stdio(false);
  int T;
  cin >> T;
  for (int t = 0; t < T; ++t) {
    string s;
    cin >> s;
    if (can(s))
      cout << 1 << endl;
    else
      cout << 0 << endl;
  }
}