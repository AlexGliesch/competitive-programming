#include <iostream>
#include <ciso646>

using namespace std;

/* 
 * There are only 3 possibilities:
 * 
 * 0: source and dest are the same.
 * 1: source and dest are on the same line, column or diagonal.
 * 2: otherwise.
 * 
 * */

int main() {
	ios_base::sync_with_stdio(false);
	int xs, ys, xt, yt;
	while (cin >> xs >> ys >> xt >> yt, xs or ys or xt or yt) {
		if (xs == xt and ys == yt) {
			cout << 0 << endl;
		} else if (xs == xt or ys == yt) {
			cout << 1 << endl;
		} else {
			bool has1 = false;
			for (int i = -8; i <= 8; ++i) {
				if (xs + i == xt and ys + i == yt or 
					xs - i == xt and ys + i == yt) {
					has1 = true; 
					break;
				}
			}
			cout << (has1 ? 1 : 2) << endl;
		}
	}
}