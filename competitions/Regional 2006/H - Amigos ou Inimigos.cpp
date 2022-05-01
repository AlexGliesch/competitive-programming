#include <iostream>

using namespace std;

/* 
 * ad-hoc, i believe you can solve it with a math formula or something, but 
 * the limit is small (input number is at most 65535), so it can be done by
 * brute force.
 * 
 * the idea is to create a function that assigns the result of the line 
 * equation for every number i. the hard part is find out how to iterate 
 * spirally over a grid, but it only requires a little bit of thinking, not 
 * hard.
 * 
 * tip: run the program up to at least 10 numbers more than 65535, just to
 * make sure!
 * */

int T, a, b, K, dp[70000], line_eq, M, N;

int line_equation(int x, int y) {
	return y - a*x - b;
}

void find_numbers(int x, int y, int l, int c) {
	while (c < 65555) {
		line_eq = line_equation(x + 1, y);
		if (line_eq) dp[c++] = line_eq;

		while (y < l) {
			line_eq = line_equation(x, y++);
			if (line_eq) dp[c++] = line_eq;
		}
		while (x < l) {
			line_eq = line_equation(x++, y);
			if (line_eq) dp[c++] = line_eq;
		}
		while (y > -l) {
			line_eq = line_equation(x, y--);
			if (line_eq) dp[c++] = line_eq;
		}
		while (x > -l) {
			line_eq = line_equation(x--, y);
			if (line_eq) dp[c++] = line_eq;
		}

		x = -l - 1, y = -l;
		++l;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin >> T;
	for (int i = 0; i < T; ++i) {
		cout << "Caso " << i + 1 << endl;
		cin >> a >> b >> K;

		find_numbers(-1, 0, 1, 0);

		for (int j = 0; j < K; ++j) {
			cin >> M >> N;
			if (dp[M] * dp[N] > 0) cout << "Mesmo lado da fronteira" << endl;
			else cout << "Lados opostos da fronteira" << endl;
		}
	}

}