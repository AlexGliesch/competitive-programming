#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

int main() {
  int T;
  cin >> T;
  while (T--) {
    int N, M;
    cin >> N >> M;
    multiset<int> la, lb;
    for (int i = 0; i < N; ++i) {
      int x;
      cin >> x;
      la.insert(x);
    }
    for (int i = 0; i < M; ++i) {
      int x;
      cin >> x;
      lb.insert(x);
    }

    int res = 0;
    while (la.size()) {
      int x = *la.begin();
      res += std::abs((int)la.count(x) - (int)lb.count(x));
      la.erase(x);
      lb.erase(x);
    }
    res += lb.size();
    cout << res << endl;
  }
}
