#include <algorithm>
#include <ciso646>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef long long ll;

/*
 * we must develop a formula to get the nth permutation of a string, without
 * computing all the intermediate permutations (infeasible for N = 20).
 *
 * for example, if you have the string s = "abcde", with N = 119, you can fix
 * the first character of the output string, while permutating the other 4:
 *
 * abcde -> permutation # 0 * 4! = 0
 * bacde -> permutation # 1 * 4! = 24
 * cabde -> permutation # 2 * 4! = 48
 * dabce -> permutatoin # 3 * 4! = 72
 * eabcd -> permutation # 4 * 4! = 96
 *
 * now we know that, since N is 119 > 96, the first character of the output
 * string HAS to be 'e', since all permutations with index greater than 96 have
 * 'e' as the first character.
 *
 * this gives us the sub-problem of computing the permutation index of "abcd"
 * with N = 119 - 96 = 23. in other words,
 * nth_perm("abcde", 119) = "e" ++ nth_perm("abcd", 23). we can call this
 * recursively until the input string is empty, or N is 0.
 *
 * in order to find the character you want to fix rapidly, we must find
 * i = N / factorial(k), where k = s.size() - 1. then, s[i] is the character
 * you want to fix (in our example, 'e').
 *
 * */

ll fact[22], t, n;
string s;

string nth_permutation(string s, ll n) {
  if (s.empty())
    return "";
  if (n == 0) {
    return s;
  }

  ll f = fact[s.size() - 1];
  ll i = n / f;
  n -= f * i;

  char c = s[i];
  s.erase(i, 1);
  return c + nth_permutation(s, n);
}

int main() {
  fact[0] = 1;
  for (ll i = 1; i < 22; ++i)
    fact[i] = i * fact[i - 1];

  cin >> t;
  for (ll i = 0; i < t; ++i) {
    cin >> s >> n;
    sort(s.begin(), s.end());
    cout << nth_permutation(s, n) << endl;
  }
}