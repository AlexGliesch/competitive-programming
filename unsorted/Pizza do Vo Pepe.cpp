#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int c, n;
  while (cin >> c >> n) {
    vector<int> p1(c);
    for (int i = 0; i < n; i++) {
      int a;
      cin >> a;
      p1[a] = 1;
    }

    int p = c / n;
    vector<int> p2(c, 0);
    for (int i = 0; i < p; i++) {
      p2[0] += p1[i];
    }
    for (int i = 1; i < c; i++) {
      p2[i] = p2[i - 1] - p1[i - 1] + p1[(i + p - 1) % c];
    }

    bool valid = false;
    for (int i = 0; i < p; i++) {
      valid = true;
      for (int j = i; j < c; j += p) {
        valid = p2[j] == 1;
        if (!valid)
          break;
      }
      if (valid)
        break;
    }

    cout << (valid ? "S" : "N") << endl;
  }
  return 0;
}