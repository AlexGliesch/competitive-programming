#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

int m[32][32], i;
string s;

void read_tree(int r, int c, int size) {
  if (i >= s.size() or s[i] == 'e') {
    return;
  } else if (s[i] == 'f') {
    for (int ri = r; ri < r + size; ++ri)
      for (int ci = c; ci < c + size; ++ci)
        m[ri][ci] = 1;
  } else { // 'p'
    int s2 = size / 2;
    ++i, read_tree(r, c, s2);
    ++i, read_tree(r + s2, c, s2);
    ++i, read_tree(r, c + s2, s2);
    ++i, read_tree(r + s2, c + s2, s2);
  }
}

int main() {
  int c;
  cin >> c;
  while (c--) {
    memset(m, 0, sizeof(m));
    i = 0;
    cin >> s;
    read_tree(0, 0, 32);
    i = 0;
    cin >> s;
    read_tree(0, 0, 32);
    int ans = 0;
    for (auto& i : m)
      for (int j : i)
        ans += j;
    cout << "There are " << ans << " black pixels.\n";
  }
}
