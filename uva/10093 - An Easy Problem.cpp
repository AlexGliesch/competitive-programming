#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
using ll = long long;

/*
 * if we try to calculate the numbers by exponentiation, we might have to calcu
 * late something like 62^62, which will overflow long long pretty quickly.
 *
 * here, we use the generalization of the rule that a number is divisible by 9
 * if the sum of its digits is also divisible by 9:
 * "a number in base B is divisible by B-1 <=> the sum of the digits
 * in that number is divisible by B-1."
 *
 * just test for every possible base, from 2 to 62, and take the first for which
 * the rule is true.
 *
 * */

void strip_string(string &s) {
  s.erase(remove_if(begin(s), end(s),
                    [](char c) {
                      return not(c >= '0' and c <= '9' or
                                 c >= 'a' and c <= 'z' or
                                 c >= 'A' and c <= 'Z' or c == '+' or c == '-');
                    }),
          end(s));
}

bool is_divisible_by_n_menos_1(const string &s, ll base) {
  ll ans = 0, x;
  for (ll i = s.size() - 1; i >= 0; --i) {
    if (s[i] >= '0' and s[i] <= '9')
      x = s[i] - '0';
    else if (s[i] >= 'A' and s[i] <= 'Z')
      x = s[i] - 'A' + 10;
    else if (s[i] >= 'a' and s[i] <= 'z')
      x = s[i] - 'a' + 36;
    else
      continue;
    if (x >= base)
      return false;

    ans += x;
  }
  if (s[0] == '-')
    ans = -ans;
  return (ans % (base - 1)) == 0;
}

int main() {
  string s;
  while (getline(cin, s)) {
    strip_string(s);
    bool has = false;
    for (ll b = 2; b <= 62; ++b) {
      if (is_divisible_by_n_menos_1(s, b)) {
        has = true;
        cout << b << endl;
        break;
      }
    }
    if (not has)
      cout << "such number is impossible!" << endl;
  }
}
