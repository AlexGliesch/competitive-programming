#include <algorithm>
#include <iostream>

using namespace std;

/* Easy, with the std::__gcd function ;) */

int main() {
  ios_base::sync_with_stdio(false);
  int N;
  while (cin >> N, N) {
    int G = 0;
    for (int i = 1; i < N; ++i)
      for (int j = i + 1; j <= N; ++j)
        G += __gcd(i, j);
    cout << G << endl;
  }
}