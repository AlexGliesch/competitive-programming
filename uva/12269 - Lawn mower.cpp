#include <algorithm>
#include <ciso646>
#include <iostream>
#include <vector>

using namespace std;

int nx, ny;
long long w;

bool cut() {
  vector<long long> len_pass(nx), wid_pass(ny);
  for (int i = 0; i < nx; ++i) {
    double p;
    cin >> p;
    len_pass[i] = (long long)(p * 100000000LL);
  }
  for (int i = 0; i < ny; ++i) {
    double p;
    cin >> p;
    wid_pass[i] = (long long)(p * 100000000LL);
  }

  sort(begin(len_pass), end(len_pass));
  sort(begin(wid_pass), end(wid_pass));

  if (len_pass[0] - w > 0 or len_pass.back() + w < 7500000000LL or
      wid_pass[0] - w > 0 or wid_pass.back() + w < 10000000000LL)
    return false;

  for (int i = 1; i < nx; ++i)
    if (len_pass[i - 1] + w < len_pass[i] - w)
      return false;

  for (int i = 1; i < ny; ++i)
    if (wid_pass[i - 1] + w < wid_pass[i] - w)
      return false;

  return true;
}

int main() {
  double d;
  while (cin >> nx >> ny >> d, nx and ny and d) {
    w = (long long)(d * 0.5 * 100000000LL);
    cout << (cut() ? "YES" : "NO") << endl;
  }
}