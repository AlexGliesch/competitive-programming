#include <bitset>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

/*
 * use sieve to generate all primes up to 1000000. then, for each prime p,
 * test if n - p is prime also; if so, there's the solution.
 * in order to maximize the difference, just use the first prime (starting from
 * the smallest) for which the conjecture holds.
 *
 * the conjecture will never be false for this problem.
 * */

bitset<1000100> prime;
vector<ll> primes;

void sieve(ll N) {
  prime.set();
  prime[0] = prime[1] = 0;
  for (ll i = 2; i <= N + 1; ++i) {
    if (prime[i]) {
      for (ll j = i * i; j <= N + 1; j += i)
        prime[j] = false;
      primes.push_back(i);
    }
  }
}

int main() {
  sieve(1000000);
  ll n;
  while (cin >> n, n) {
    for (ll i = 0; primes[i] <= n; ++i) {
      if (prime[n - primes[i]]) {
        cout << n << " = " << primes[i] << " + " << n - primes[i] << endl;
        break;
      }
    }
  }
}