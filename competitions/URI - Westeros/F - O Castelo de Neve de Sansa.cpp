#include <iostream>
#include <ciso646>
#include <vector>

using namespace std;

int main() {
	int N, K; cin >> N >> K;
	int peaks = 0, vales = 0;

	vector<int> v(N);
	for (int i = 0; i < N; ++i) cin >> v[i];

	for (int i = 1; i < N-1; ++i) {
		if (v[i] < v[i - 1] and v[i] < v[i + 1]) ++vales;
		else if (v[i] > v[i - 1] and v[i] > v[i + 1]) ++peaks;
	}
	if (peaks == K and vales == K - 1) {
		cout << "beautiful" << endl;
	} else {
		cout << "ugly" << endl;
	}

}