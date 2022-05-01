#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	int N; cin >> N;
	int min_i = 0, min_val = (1 << 28);
	for (int i = 0; i < N; ++i) {
		int x; cin >> x;
		if (x < min_val) {
			min_val = x;
			min_i = i;
		}
	}
	cout << min_i + 1<< endl;
}