#include <iostream>
#include <algorithm>

using namespace std;

/* 
 * greedy: sort the hours and ALWAYS pair hours that are right next to each
 * other. so there are 2 possible pairings: taking 0 and 1, 2 and 3, ..., 
 * or taking N-1 and 0, 1 and 2, 3 and 4, ... (going around).
 * 
 * just test those two pairings and take the minimum between them.
 * */

int main() {
	ios_base::sync_with_stdio(false);
	int N, v[1001];
	while (cin >> N) {
		for (int i = 0; i < N; ++i)
			cin >> v[i];

		sort(v, v + N);
		int a1 = 0, a2 = 0;
		for (int i = 1; i < N; i += 2) {
			int aft = (i == N - 1 ? 0 : i + 1);
			a1 += min(abs(v[aft] - v[i]), 24 - abs(v[aft] - v[i]));
			a2 += min(abs(v[i] - v[i - 1]), 24 - abs(v[i] - v[i - 1]));
		}
		cout << min(a1, a2) << endl;
	}	
}