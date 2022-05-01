#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

/* just trim the spaces from the string and compare. */

int main() {
  ios_base::sync_with_stdio(false);
  int T;
  cin >> T;
  string user, judge, trimmed;
  getline(cin, user);
  for (int t = 1; t <= T; ++t) {
    getline(cin, user);
    getline(cin, judge);
    trimmed = user;
    trimmed.erase(remove_if(begin(trimmed), end(trimmed),
                            [](char c) { return c == ' '; }),
                  end(trimmed));
    cout << "Case " << t << ": ";
    if (user == judge)
      cout << "Yes" << endl;
    else if (trimmed == judge)
      cout << "Output Format Error" << endl;
    else
      cout << "Wrong Answer" << endl;
  }
}
