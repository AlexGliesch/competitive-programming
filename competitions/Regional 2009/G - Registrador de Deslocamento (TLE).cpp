#include <iostream>
#include <iomanip>
#include <set>
#include <ciso646>

using namespace std;

/* 
 * TLE, no idea how to improve it. 
 * */

int main(){
	ios_base::sync_with_stdio(false);
	unsigned N, T, tap[35];
	
	while (cin >> N >> T, N or T) {
		for (unsigned i = 0; i < T; ++i) {
			cin >> tap[i];
		}

		unsigned init, fin;
		cin >> hex >> init >> hex >> fin;
		unsigned x = init;
		set<unsigned> visited;

		bool impossible = false;
		unsigned i = 0;

		while (x != fin) {
			++i;
			if (visited.count(x >> 1)) {
				impossible = true;
				break;
			}
			visited.insert(x >> 1);
			unsigned y = x;
			x >>= 1;

			for (unsigned i = 0; i < T; ++i) {
				x ^= ((y & (1 << tap[i])) >> (tap[i])) << (N - 1);
			}
		}
		if (impossible) cout << "*\n";
		else cout << i << endl;
	}
}