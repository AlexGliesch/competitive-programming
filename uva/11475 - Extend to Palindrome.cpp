#include <algorithm>
#include <iostream>
#include <string>
#define MAXN 100000

using namespace std;

int b[MAXN]; /* back table for kmp. */

void kmp_preprocess(const string &p /* pattern */) {
  int i = 0, j = -1, m = p.size();
  b[0] = -1;
  while (i < m) {
    while (j >= 0 and p[i] != p[j])
      j = b[j];
    ++i, ++j;
    b[i] = j;
  }
}

/*
 * this kmp finds the size of the longest prefix of s that matches p
 * */
int kmp_longest_prefix(const string &s, const string &p) {
  kmp_preprocess(p);
  int i = 0, j = 0, n = s.size(), m = p.size(), ans = 0;
  while (i < n) {
    while (j >= 0 and s[i] != p[j])
      j = b[j];
    ++i, ++j;
  }
  return i - j;
}

int main() {
  string s;
  while (getline(cin, s)) {
    string rs = string(s.rbegin(), s.rend());
    int best_prefix = kmp_longest_prefix(s, rs);
    /*for (int i = rs.size(); i >= 1; --i) {
            ss = string(rs, 0, i);
            int k = kmp(s, ss);
            if (k != s.size()) {
                    best_prefix = k;
                    break;
            }
    }*/
    rs = string(s, 0, best_prefix);
    reverse(rs.begin(), rs.end());

    cout << s << rs << endl;
  }
}