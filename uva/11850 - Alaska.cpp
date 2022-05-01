#include <algorithm>
#include <ciso646>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int N;
  while (cin >> N, N) {
    vector<int> v(N);
    for (int i = 0; i < N; ++i)
      cin >> v[i];
    sort(begin(v), end(v));
    bool possible = true;
    for (int i = 0; i < N - 1; ++i) {
      if (v[i + 1] - v[i] > 200) {
        possible = false;
        break;
      }
    }
    if (1422 - v.back() > 100) {
      possible = false;
    }
    cout << (possible ? "POSSIBLE" : "IMPOSSIBLE") << endl;
  }
}