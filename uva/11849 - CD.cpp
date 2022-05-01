#include <bitset>
#include <iostream>

using namespace std;
bitset<2000010> jack;

int main() {
  int N, M;
  while (cin >> N >> M, N != 0 && M != 0) {
    jack.reset();
    for (int i = 0; i < N; ++i) {
      int x;
      cin >> x;
      jack.set(x, true);
    }
    int res = 0;
    for (int i = 0; i < M; ++i) {
      int x;
      cin >> x;
      if (jack[x])
        ++res;
    }
    cout << res << endl;
  }
}