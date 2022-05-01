#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

bitset<1100> prime;
vector<ll> primes;

void sieve(ll N) {
  prime.set();
  prime[0] = prime[1] = 0;
  primes.push_back(1);
  for (ll i = 2; i <= N + 1; ++i) {
    if (prime[i]) {
      for (ll j = i * i; j <= N + 1; j += i)
        prime[j] = false;
      primes.push_back(i);
    }
  }
}

int main() {
  sieve(1010);
  ll N, C, START, END;
  while (cin >> N >> C) {
    ll last = lower_bound(begin(primes), end(primes), N) - begin(primes) + 1;
    if (last % 2 == 0)
      cout << "even" << endl;
    else
      cout << "odd" << endl;
    ll lim = C * 2 - (last % 2 == 0 ? 1 : 0);
    if (lim > last) {
      START = 0, END = last;
    } else {
      if (last % 2 == 1)
        START = (last - lim + 1) / 2, END = last - (last - lim + 1) / 2;
      else
        START = (last - lim) / 2, END = last - (last - lim) / 2;
    }
    cout << N << " " << C << ":";
    for (ll i = START; i < END; ++i)
      cout << " " << primes[i];
    cout << endl << endl;
  }
}