#include <cmath>
#include <algorithm>
#include <iostream>
#include <ciso646>
#include <cassert>

using namespace std;
using ll = long long;

ll N, B;

ll f(ll x) {
	return 2 * (x - 1) * (-2 * (x - 1) + 2 * N - 1) + N;
}

int main() {
	ios_base::sync_with_stdio(false);
	while (cin >> N >> B) {
		double disc = sqrt(pow(2 - 4 * N, 2) - 16.0*(B - N));
		ll k = (ll)ceil(min((4 * N - 2 + disc) / 8.0,
							(4 * N - 2 - disc) / 8.0));
		ll v = f(k);
		ll d = (N - k * 2 + 1);

		if (B <= N) { // trivial 
			cout << "1 " << B << endl;
		} else if (B == f(k + 1)) { // diagonal 
			cout << k + 1 << " " << N - k << endl;
		} else if (B >= v and B < v + d) { // first turn 
			cout << k + B - v << " " << N - k + 1 << endl;
		} else if (B >= v + d and B < v + 2 * d) { // second turn
			cout << k + d << " " << -B + v + 2 * d + k << endl;
		} else if (B >= v + 2 * d and B < v + d * 3 - 1) { // third turn
			cout << k - B + v + d * 3 << " " << k << endl;
		} else { // fourth turn
			cout << k + 1 << " " << k + 1 - d * 3 + B - v << endl;
		}
	}		
}