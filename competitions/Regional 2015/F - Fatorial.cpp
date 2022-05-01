#include <iostream>

using namespace std;

/* greedy */

int fact[] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800 };

int main() {
	int N; 
	while (cin >> N) {
		int k = 0;
		for (int i = 9; i >= 1; --i) {
			while (N >= fact[i]) {
				N -= fact[i];
				++k;
			}
		}
		cout << k << endl;
	}
}