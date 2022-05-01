#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> v(2000010);

int main() {
  int n;
  while (cin >> n, n != 0) {
    for (int i = 0; i < n; ++i)
      cin >> v[i];
    sort(v.begin(), v.begin() + n);
    for (int i = 0; i < n - 1; ++i)
      cout << v[i] << ' ';
    cout << v[n - 1] << endl;
  }
}
