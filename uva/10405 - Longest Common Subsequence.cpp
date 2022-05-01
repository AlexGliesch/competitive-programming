#include <algorithm>
#include <ciso646>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

/*
 * to solve LCS, we recurse both strings starting from their end.
 *
 * lcs(Sa, Sb, Ia, Ib):
 * - if Sa[Ia] == Sb[Ib], then pop the last character of both strings, and
 *		return 1 + lcs(Sa, Sb, Ia - 1, Ib - 1) *
 * - if Sa[Ia] != Sb[Ib], then get the best of popping a character from each
 * string.
 *		return max(lcs(Sa, Sb, Ia - 1, Ib), lcs(Sa, Sb, Ia, Ib - 1)); *
 * - if we've reached the end of the string (Ia or Ib < 0) we return 0.
 * after
 *
 * ps: I had a problem with getline(), where it was ignoring the \n (line feed)
 * but not the \r (carriage return). Maybe it was because of cygwin, but I'm
 * not sure...
 *
 * */

string Sa, Sb;
int dp[1010][1010];

int lcs(int Ia, int Ib) {
  if (Ia < 0 or Ib < 0)
    return 0;
  if (dp[Ia][Ib] == -1) {
    if (Sa[Ia] == Sb[Ib])
      dp[Ia][Ib] = 1 + lcs(Ia - 1, Ib - 1);
    else
      dp[Ia][Ib] = max(lcs(Ia - 1, Ib), lcs(Ia, Ib - 1));
  }
  return dp[Ia][Ib];
}

int main() {
  while (getline(cin, Sa) and getline(cin, Sb)) {
    while (Sa.back() == '\n' or Sa.back() == '\r')
      Sa.pop_back();
    while (Sb.back() == '\n' or Sb.back() == '\r')
      Sb.pop_back();
    memset(dp, -1, sizeof dp);
    cout << lcs(Sa.size() - 1, Sb.size() - 1) << endl;
  }
}