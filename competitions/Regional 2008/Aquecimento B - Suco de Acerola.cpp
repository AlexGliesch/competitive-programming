#include <iostream>
#include <iomanip>
#include <ciso646>

using namespace std;
typedef long long ll;

int main() {
	ll N, F;
	while (cin >> N >> F) {
		if (N == 0 and F == 0) break;
		double liters = F * 50.0 / 1000.0;
		cout << setprecision(2) << fixed << liters / N << endl;
	}
}
