#include <vector>
#include <iostream>
#include <ciso646>

using namespace std;

int main() {
	int n, d;
	while (cin >> n >> d, n != 0 and d != 0) {		
		vector<int> v(n, 0);
		for (int i = 0; i < d; ++i) {
			for (int j = 0; j < n; ++j) {
				int x;
				cin >> x;
				v[j] += x;
			}
		}

		bool yes = false;
		for (int i = 0; i < n; ++i) {
			if (v[i] == d) {
				cout << "yes" << endl;
				yes = true;
				break;
			}
		}

		if (not yes) cout << "no" << endl;
	}
}