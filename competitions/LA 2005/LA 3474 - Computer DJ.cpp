#include <iostream>
#include <vector>
#include <ciso646>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

void convert(vector<int>& d, int digits, int base, int val) {
	d.assign(digits, 0);
	int i = digits - 1;

	while (i >= 0) {
		d[i] = val % base;
		val /= base;
		--i;		
	}
}

int main() {
	int n, q;
 	while (cin >> n >> q, not (n == 0 and q == 0)) {
 		vector<string> titles(n);
 		for (int i = 0; i < n; ++i)
 			cin >> titles[i];
 
		for (int i = 0; i < q; ++i) {
			int k;
			cin >> k;
			--k;

			int p = 1;
			while (k >= p * pow(n, p)) {
				k -= p * pow(n, p);
				++p;
			}

			int val = k / p;
			k = k % p;
			vector<int> d;
			convert(d, p, n, val);
			cout << titles[d[k]] << endl;
		}

		cout << endl;
 	}
}