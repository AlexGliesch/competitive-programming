#include <iostream>

using namespace std;

/* 
 * result is sum{Vi/2}/2, where / is integer division. ignore Ci.
 * */

int main() {
	int N;
	while (cin >> N, N) {
		int sum = 0;
		for (int i = 0; i < N; ++i) {
			int C, V; cin >> C >> V;
			sum += V / 2;
		}
		cout << sum / 2 << endl;
	}
}