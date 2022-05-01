#include <iostream>
#include <vector>

using namespace std;


int calcGcd(int a, int b)
{
    if (a == 0) return b;
    if (b == 0) return a;
    if (a < b)
        swap(a, b);
    return calcGcd(b, (a % b));
}

int main()
{
    string s;
    cin >> s;
    int n = s.size();
    vector<int> gcd(n);
    for (int i=0; i<n; ++i)
      gcd[i] = calcGcd(i, n);
    vector<int> amtGcd(n+1, 0);
    for (int i=0; i<n; ++i)
      amtGcd[gcd[i]]++;
    int res=0;
    for (int i=1; i<n; ++i)
      if (amtGcd[i]>0) {
        for (int start=0; start<i; ++start) {
          int done=true;
          for (int j=start; j<n; j+=i)
            if (s[j]=='P')
              done=false;
          if (done) {
            res += amtGcd[i];
            break;
          }
        }
      }
    cout << res << endl;
}
