#include <bitset>
#include <ciso646>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;
using ll = long long;

/*
 * here we need to use the segmented sieve algorithm. it's impractical to
 * calculate sieve of 2^31, because the memory requirements are too high.
 *
 * what we do here is calculate all the primes up to 2^16 = 65536 with a normal
 * sieve (because 2^16 <= sqrt(x) for any x <= 2^31). then, we run a
 * "displaced" sieve  on all numbers between L and U.
 *
 * since U - L <= 1000000, we can use a bitset of 1kk bits, where bit #i
 * tells whether L + i is prime or not.
 *
 * 1. start with a bitset of size 1kk, mark it with all ones. *
 * 2. for every prime p between 0 and sqrt(U) (all are less than 2^16):
 *		3. start for the first multiple of p that is greater than L, that
 *is,
 *			p * ceil(L / p).
 *		4. mark that multiple and all multiples of p less than U as not
 *prime.
 *
 * then you will have a bitset saying whether any number from L up until U is
 * prime or not.
 *
 * */

bitset<66010> prime;
bitset<1000010> is_prime;
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
  sieve(66000);
  ll L, U;
  ios_base::sync_with_stdio(false);
  while (cin >> L >> U) {
    if (L == 1)
      ++L;

    /* Segmented sieve algorithm */
    is_prime.set();
    for (ll i = 0; primes[i] <= (ll)sqrt(U); ++i) {
      ll p = primes[i];
      for (ll j = p * ceil(L / (double)p); j <= U + 1; j += p)
        is_prime[j - L] = false;
    }

    ll previous = -1, num_primes = 0;
    ll min0 = 0, min1 = numeric_limits<int>::max(),
       max0 = numeric_limits<int>::max(), max1 = 0;
    for (ll i = L; i <= U; ++i) {
      if ((U <= 66000 and prime[i]) or (U > 66000 and is_prime[i - L])) {
        ++num_primes;
        if (previous != -1) {
          if (min1 - min0 > i - previous)
            min0 = previous, min1 = i;
          if (max1 - max0 < i - previous)
            max0 = previous, max1 = i;
        }
        previous = i;
      }
    }
    if (num_primes >= 2) {
      cout << min0 << "," << min1 << " are closest, " << max0 << "," << max1
           << " are most distant." << endl;
    } else {
      cout << "There are no adjacent primes." << endl;
    }
  }
}
