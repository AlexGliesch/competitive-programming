#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<int> v;
  int x;
  while (cin >> x) {
    v.insert(upper_bound(begin(v), end(v), x), x);
    if (v.size() % 2 == 0) {
      cout << int((v[v.size() / 2] + v[v.size() / 2 - 1]) / 2.0) << endl;
    } else {
      cout << v[v.size() / 2] << endl;
    }
  }
}