#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/* very simple. use std::__gcd, and iterate over all possible values. */

int main() {
  int v[120], N, M;
  string s;
  cin >> N;
  getline(cin, s);
  while (getline(cin, s)) {
    istringstream ss(s);
    M = 0;
    while (ss >> v[M])
      ++M;
    int max_gcd = 0;
    for (int i = 0; i < M; ++i)
      for (int j = 0; j < M; ++j)
        max_gcd = i == j ? max_gcd : max(max_gcd, __gcd(v[i], v[j]));
    cout << max_gcd << endl;
  }
}