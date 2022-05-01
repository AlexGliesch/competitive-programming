#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

int bbscs(vector<int> &a, vector<int> &b) {
  int swaps = 0;
  for (int i = 0; i < a.size(); i++) {
    int j = i;
    for (; j < b.size(); j++) {
      if (a[i] == b[j])
        break;
    }
    // a[i] == b[j]
    while (j != i) {
      int helper = b[j];
      b[j] = b[j - 1];
      b[j - 1] = b[j];
      j--;
      swaps++;
    }
  }
  return swaps;
}

int main() {
  int n;
  while (cin >> n) {
    vector<int> b;
    vector<int> e;
    for (int i = 0; i < n; i++) {
      int j;
      cin >> j;
      b.push_back(j);
    }
    for (int i = 0; i < n; i++) {
      int j;
      cin >> j;
      e.push_back(j);
    }
    int bbss = bbscs(b, e);
    cout << bbss << '\n';
  }
  return 0;
}