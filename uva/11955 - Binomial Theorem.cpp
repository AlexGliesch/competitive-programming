#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using ll = long long;

/*
* the theorem in the problem description is wrong!
* correction: x_1..._k+1 are such taht x_i = C(i-1, k).
*
* other than that, split string, find out how to get binomial coefficient.
* */

struct Delim {
  bool operator()(char c) { return not isalnum(c); }
};

void split_string(vector<string> &output, const string &input,
                  bool trim_empty = false) {
  string::const_iterator it = input.begin();
  string::const_iterator it_last = it;
  while (it = find_if(it, input.end(), Delim()), it != input.end()) {
    if (not(trim_empty and it == it_last)) {
      output.push_back(string(it_last, it));
    }
    ++it;
    it_last = it;
  }
  if (it_last != input.end())
    output.push_back(string(it_last, it));
}

ll binom(ll n, ll k) {
  ll ans = 1;
  if (k > n - k)
    k = n - k;
  for (ll i = 0; i < k; ++i) {
    ans *= (n - i);
    ans /= (i + 1);
  }
  return ans;
}

int main() {
  ll T;
  cin >> T;
  string s;
  getline(cin, s);
  for (int t = 1; t <= T; ++t) {
    cout << "Case " << t << ": ";
    getline(cin, s);
    vector<string> vs;
    split_string(vs, s, true);

    string &a = vs[0], &b = vs[1];
    ll k = atoll(vs[2].c_str());

    for (ll i = 0; i <= k; ++i) {
      if (i != 0)
        cout << "+";
      ll xi = binom(k, i);
      ll a_exp = k - i, b_exp = i;
      if (xi != 1)
        cout << xi;
      if (a_exp != 0) {
        if (xi != 1)
          cout << "*";
        cout << a;
        if (a_exp != 1)
          cout << "^" << a_exp;
      }
      if (b_exp != 0) {
        if (xi != 1 or a_exp != 0)
          cout << "*";
        cout << b;
        if (b_exp != 1)
          cout << "^" << b_exp;
      }
    }
    cout << endl;
  }
}