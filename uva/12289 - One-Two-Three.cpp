#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

/*
* very simple.
* for each input, count the number of different characters to the strings
* "one", "two" and "three".
* if any of the differences is <= 1, then print that number.
 **/

int difference(const string &a, const string &b) {
  if (a.size() != b.size())
    return (int)max(a.size(), b.size());
  int ans = 0;
  for (int i = 0; i < (int)a.size(); ++i)
    if (a[i] != b[i])
      ++ans;
  return ans;
}

int main() {
  int n;
  cin >> n;
  string s;
  getline(cin, s);
  for (int i = 0; i < n; ++i) {
    getline(cin, s);
    if (difference(s, "one") <= 1) {
      cout << 1 << endl;
    } else if (difference(s, "two") <= 1) {
      cout << 2 << endl;
    } else if (difference(s, "three") <= 1) {
      cout << 3 << endl;
    }
  }
}
