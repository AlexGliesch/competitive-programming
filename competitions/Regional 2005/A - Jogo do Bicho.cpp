#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <ciso646>
#include <iomanip>

using namespace std;

/* 
 * ad-hoc. convert M and N to strings, and consider only the last 4 characters
 * of the string. if < 4 characters, pad the string with 0 to the left.
 * 
 * compare the strings, and return the appropriate value. for the last case,
 * both M and N are in the same group if 
 * (N - 1 + 100) % 100 / 4 == (M - 1 + 100) % 100 / 4
 * 
 * */

string int_to_str(int x) {
	ostringstream ss;
	ss << setw(6) << setfill('0') << x;
	return ss.str();
}

int N, M;
double V;

int main() {
	while (cin >> V >> M >> N, not (M == 0 and N == 0 and V == 0.0)) {
		string ms = int_to_str(M), ns = int_to_str(N);
		while (ms.size() > 4) ms.erase(0, 1);
		while (ns.size() > 4) ns.erase(0, 1);

		double x;
		if (ms == ns) {
			x = V * 3000;
		} else if (string(ms, 1) == string(ns, 1)) {
			x = V * 500;
		} else if (string(ms, 2) == string(ns, 2)) {
			x = V * 50;
		} else if (((N - 1 + 100) % 100) / 4 == ((M - 1 + 100) % 100) / 4) {
			x = V * 16;
		} else {
			x = 0;
		}
		cout << setprecision(2) << fixed << x << endl;
	}
}