#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

vector<bool> is_prime;
vector<ll> primes, cases;

void prime_sum(ll x, ll& p1, ll& p2) {
    for (ll i = 0; i < primes.size(); ++i) {
        if (primes[i] >= x) break;
        if (is_prime[x - primes[i]]) {
            p1 = primes[i];
            p2 = x - primes[i];
            return;
        }
    }
    p1 = p2 = -1;
}

int main() {
    ll t, x, p1, p2, max_n = 0;
    cin >> t;
    cases.resize(t);
    for (ll i = 0; i < t; ++i) {
        cin >> cases[i];
        max_n = max(max_n, cases[i]);
    }
    is_prime.assign(max_n, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i <= max_n + 1; ++i)
        if (is_prime[i]) {
            for (ll j = i * i; j <= max_n + 1; j += i) is_prime[j] = false;
            primes.push_back(i);
        }

    for (ll k = 0; k < t; ++k) {
        cout << "Case #" << k + 1 << ": ";
        x = cases[k];
        if (x & 1) {
            prime_sum(x - 2, p1, p2);
            if (p1 != -1) {
                cout << "2 " << min(p1, p2) << " " << max(p1, p2) << endl;
                continue;
            }
            cout << "3 ";
            x -= 3;
        }
        prime_sum(x, p1, p2);
        cout << min(p1, p2) << " " << max(p1, p2) << endl;
    }
}