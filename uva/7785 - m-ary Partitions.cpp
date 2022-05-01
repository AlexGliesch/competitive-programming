#include <algorithm>
#include <iostream>
#include <vector>

// Feito com Augusto

using namespace std;

typedef long long int lli;
typedef vector<int> vi;
typedef pair<int, int> ii;
vi v;
vector<vi> dp;

int times(int n, int i) {
  if (i == v.size())
    return 0;
  if (n < 0)
    return 0;
  if (n == 0)
    return 1;
  if (dp[n][i] != -1)
    return dp[n][i];

  int ans = times(n - v[i], i) + times(n, i + 1);
  return dp[n][i] = ans;
}

int main() {

  int p;
  cin >> p;

  while (p--) {
    int k, m, n;
    cin >> k >> m >> n;
    cout << k << " ";

    v.clear();
    for (int i = 1; i <= n; i = i * m)
      v.push_back(i);

    dp.assign(n + 10, vi(v.size(), -1));

    cout << times(n, 0) << endl;
  }
}
