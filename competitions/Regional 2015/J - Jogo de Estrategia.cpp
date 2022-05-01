#include <iostream>
#include <cstring>

using namespace std;

int main() {
	int p[510], J, R;
	while (cin >> J >> R) {
		memset(p, 0, sizeof p);
		for (int i = 0; i < R; ++i) {
			for (int j = 0; j < J; ++j) {
				int x; cin >> x;
				p[j] += x;
			}
		}
		int best = J - 1;
		for (int i = J - 1; i >= 0; --i) {
			if (p[i] > p[best]) 
				best = i;
		}
		cout << best + 1 << endl;
	}
}