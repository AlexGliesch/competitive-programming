#include <algorithm>
#include <ciso646>
#include <iostream>
#include <string>

using namespace std;

enum { py = 0, my, pz, mz, px, mx };

int py_v[] = {mx, px, pz, mz, py, my};
int my_v[] = {px, mx, pz, mz, my, py};
int pz_v[] = {py, my, mx, px, pz, mz};
int mz_v[] = {py, my, px, mx, mz, pz};

int main() {
  int L;
  while (cin >> L, L != 0) {
    int cur = px;
    for (int i = 0; i < L - 1; ++i) {
      string s;
      cin >> s;
      if (s == "+y") {
        cur = py_v[cur];
      } else if (s == "-y") {
        cur = my_v[cur];
      } else if (s == "+z") {
        cur = pz_v[cur];
      } else if (s == "-z") {
        cur = mz_v[cur];
      }
    }
    if (cur == py)
      cout << "+y" << endl;
    if (cur == my)
      cout << "-y" << endl;
    if (cur == pz)
      cout << "+z" << endl;
    if (cur == mz)
      cout << "-z" << endl;
    if (cur == px)
      cout << "+x" << endl;
    if (cur == mx)
      cout << "-x" << endl;
  }
}