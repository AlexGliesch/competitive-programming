#include <iostream>
#include <vector>
#include <map>
#define mp make_pair 

using namespace std;

int n, k;
string s;

map<pair<int, int>, bool> dp;


// Feito com Augusto

// -k <= num <= k
// 0 <= i < n
bool coloca(int i, int num) {
  auto m = mp(i,num);
  if (dp.count(m))
    return dp[m];
      
  if (num==-k or num==k) { return i==n; }
  else if (i==n) { return dp[m] = false; }
  else {
    if (s[i]=='?') {
      if (coloca(i+1, num+1)) {
        s[i]='W';
        return dp[m] = true;
      } else if (coloca(i+1, num-1)) {
        s[i]='L';
        return dp[m] =   true;
      } else if (coloca(i+1, num)) {
        s[i]='D';
        return dp[m] = true;
      } else {
        return dp[m] = false;
      }
    } 
      else if (s[i] == 'W') return dp[m] = coloca(i+1, num+1);
      else if (s[i] == 'L') return dp[m] = coloca(i+1, num-1);
      else /*if (s[i]=='D')*/ return dp[m] = coloca(i+1, num);
  }
}

int main() {  
  
  
  cin >> n >> k;
  
  
  cin >> s;
  if (coloca(0,0)) cout << s <<endl;
  else  cout<< "NO" <<endl;
  

}