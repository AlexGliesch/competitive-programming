#include <algorithm>
#include <ciso646>
#include <iostream>
#include <locale>
#include <string>
#include <vector>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  int N;
  cin >> N;
  string buf;
  getline(cin, buf);

  vector<pair<int, char>> dict(26);
  for (char c = 'A'; c <= 'Z'; ++c)
    dict[c - 'A'].second = c;

  for (int t = 0; t < N; ++t) {
    getline(cin, buf);
    for (auto c : buf) {
      c = toupper(c);
      if (c >= 'A' and c <= 'Z')
        --dict[c - 'A'].first;
    }
  }

  sort(begin(dict), end(dict));

  for (const auto &p : dict) {
    if (p.first)
      cout << p.second << ' ' << -p.first << endl;
  }
}