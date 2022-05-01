#include <algorithm>
#include <ciso646>
#include <cstring>
#include <iostream>
#include <string>

/*
 * DP. A recorr�ncia tem como par�metros os �ndices de in�cio e de fim de um
 * n�mero, e p�ra quando o indice de fim chega at� o tamanho da string.
 * A recorrencia deve parar tamb�m quando o valor do n�mero fica maior que
 * (1 << 31) - 1 (m�ximo valor de 32-bit integer). Logo, para detectar isso,
 * deve-se usar long long.
 * */

using namespace std;

string s;
long long dp[210][210];

long long partition(int i, int j) {
  if (j > s.size())
    return -(1LL << 50);
  if (dp[i][j] != -1)
    return dp[i][j];
  long long val = atoll(string(s, i, j - i).c_str());
  if (val >= (1LL << 31) - 1LL)
    return dp[i][j] = -(1LL << 50);
  if (j == s.size())
    return dp[i][j] = val;
  return dp[i][j] = max(val + partition(j, j + 1), partition(i, j + 1));
}

int main() {
  int n;
  cin >> n;
  getline(cin, s);
  while (n--) {
    getline(cin, s);
    memset(dp, -1, sizeof dp);
    long long val = s.size() == 1 ? atoll(s.c_str()) : partition(0, 1);
    cout << val << endl;
  }
}