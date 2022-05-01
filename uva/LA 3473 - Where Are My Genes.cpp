#include <algorithm>
#include <ciso646>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int t = 1, n, r;
  while (cin >> n >> r, n != 0) {
    vector<int> genes(n);
    for (int i = 0; i < n; ++i)
      genes[i] = i + 1;

    vector<pair<int, int>> rev(r);
    for (int i = 0; i < r; ++i) {
      cin >> rev[i].first >> rev[i].second;
    }

    for (int i = r - 1; i >= 0; --i) {
      reverse(genes.begin() + rev[i].first - 1, genes.begin() + rev[i].second);
    }

    cout << "Genome " << t++ << endl;
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
      int x;
      cin >> x;
      cout << genes[x - 1] << endl;
    }
  }
}