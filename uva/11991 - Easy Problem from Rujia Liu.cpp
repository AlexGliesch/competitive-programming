#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> num;

int main() {
  int n, m;
  while (cin >> n >> m) {
    num.clear();
    num.resize(1000002);

    for (int i = 0; i < n; ++i) {
      int x;
      cin >> x;
      num[x].push_back(i);
    }

    for (int i = 0; i < m; ++i) {
      int k, v;
      cin >> k >> v;
      --k;
      if (num[v].size() <= k)
        cout << 0 << endl;
      else
        cout << num[v][k] + 1 << endl;
    }
  }
}