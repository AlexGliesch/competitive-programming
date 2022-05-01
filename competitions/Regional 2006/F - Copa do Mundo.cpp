#include <iostream>
#include <string>
#include <ciso646>

using namespace std;

/*
* the answer is 3*N minus the sum of all the final points of all the teams.
* */

int main() {
	int T, N;
	while (cin >> T >> N) {
		if (T == 0 and N == 0) break;
		int ans = 3 * N;
		for (int i = 0; i < T; ++i) {
			string s; cin >> s;
			int points; cin >> points;
			ans -= points;
		}
		cout << ans << endl;
	}
}