#include <algorithm>
#include <ciso646>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int t = 0;
  while (true) {
    vector<int> v;

    int x;
    cin >> x;
    if (x == -1)
      break;
    v.push_back(x);

    while (cin >> x, x != -1) {
      v.push_back(x);
    }

    vector<int> lis(v.size(), 1);
    for (int i = 1; i < v.size(); ++i) {
      for (int j = 0; j < i; ++j) {
        if (v[j] >= v[i]) {
          lis[i] = max(lis[i], 1 + lis[j]);
        }
      }
    }
    if (t != 0)
      cout << endl;
    cout << "Test #" << ++t << ":" << endl;
    cout << "  maximum possible interceptions: "
         << *max_element(lis.begin(), lis.end()) << endl;
  }
}