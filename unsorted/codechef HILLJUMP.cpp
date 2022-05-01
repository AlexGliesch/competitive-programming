#include <iostream>
#include <vector>
using namespace std;

typedef long long int lli;

lli rsq(const vector<lli>& ft, int n) {
  lli sum=0;
  while (n>0) {
    sum += ft[n];
    n &= n-1;
  }
  return sum;
}

void inc(vector<lli>& ft, int n, lli v) {
  while (n < ft.size()) {
    ft[n] += v;
    n += (n&-n);
  }
}

int main() {
  int n, q;
  cin >> n >> q;
  vector<lli> input(n+2, 0);
  for (int i=0; i<n; ++i)
    cin >> input[i+1];
  vector<lli> ft(n+2, 0);
  for (int i=1; i<=n+1; ++i) {
    inc(ft, i, input[i]-input[i-1]);
  }
  for (int qa=0; qa<q; ++qa) {
    int t;
    cin >> t;
    if (t==1) {
      int i, k;
      cin >> i >> k;
      for (int ka=0; ka<k; ++ka)
        for (int j=1; j<=100 && i+j<=n; ++j)
          if (rsq(ft, i) < rsq(ft, i+j)) {
            i += j;
            break;
          }
      cout << i << endl;
    } else {
      int l, r;
      lli x;
      cin >> l >> r >> x;
      inc(ft, l, x);
      inc(ft, r+1, -x);
    }
  }
}