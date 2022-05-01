#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
  string s;
  cin >> s;
  int n;
  cin >> n;
  vector<vector<int> > pd(s.size(), vector<int>(n, -1));
  pd.back()[0] = 0;
  for (int i=s.size()-2; i>=0; --i)
    for (int m=0; m<n; ++m) {
      if (s[i+1]!='?') {
        int next = (m*10+s[i+1]-'0')%n;
        if(pd[i+1][next] != -1)
          pd[i][m] = s[i+1]-'0';
      } else {
        for (int next=0; next<10; ++next)
          if (pd[i+1][(m*10+next)%n] != -1) {
            pd[i][m] = next;
            break;
          }
      }
    }
  for (int f=1; f<10; ++f) {
    if (pd[0][f%n] != -1) {
      int curd=f, m=f%n;
      for (int i=0; i<s.size(); ++i) {
        cout << curd;
        curd = pd[i][m];
        m = (m*10+curd)%n;
      }
      cout << endl;
      return 0;
    }
  }
  cout << '*' << endl;
  return 0;
}
