#include <algorithm>
#include <ciso646>
#include <iostream>
#include <vector>

using namespace std;

/* go over the notes and search for elements who are smaller or greater than
 * their neighbours. don't forget that the loop goes around (N goes to 1). */

int main() {
  int N;
  while (cin >> N, N) {
    vector<int> v(N);
    for (int i = 0; i < N; ++i)
      cin >> v[i];
    int num_peaks = 0;
    for (int i = 0; i < N; ++i) {
      int bef = i == 0 ? N - 1 : i - 1;
      int aft = i == N - 1 ? 0 : i + 1;
      if (v[bef] < v[i] and v[aft] < v[i] or v[bef] > v[i] and v[aft] > v[i]) {
        ++num_peaks;
      }
    }
    cout << num_peaks << endl;
  }
}
