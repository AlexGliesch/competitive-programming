#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

/* A really interesting problem. The search space is really, really large 
 * (if it weren't for the constraints for the input, it would be infinite),
 * so it's not possible to create and store a graph; it has to be created 
 * on-the-fly.
 * 
 * Since each step (reverse or add) has the same cost, a bfs suffices. Each
 * step of the bfs can add or reverse the current digit. Since the input numbers
 * are not more than 10000, we can make a global distance vector instead of
 * using a map (which would be the obvious option in the generic case).
 * 
 * Tip: changing the reverse_num routine from using strings to a numeric 
 * implementation improved my run-time from 1.8 seconds to 0.044 seconds! 
 * But strings will work anyway.
 * */

int A, B;
vector<int> dist(10000);

int reverse_num(int num) {
	int rev = 0;
	while (num > 0) {
		rev = rev * 10 + (num % 10);
		num = num / 10;
	}
	return rev;
}

int bfs() {
	if (A == B) return 0;

	queue<int> q;
	dist[A] = 0;
	q.push(A);
	
	while (q.size()) {
		int x = q.front(); q.pop();

		int added = 1 + x;
		if (added == B) return 1 + dist[x];
		if (dist[added] == -1) {
			dist[added] = 1 + dist[x];
			q.push(added);
		}

		int reversed = reverse_num(x);
		if (reversed == B) return 1 + dist[x];
		if (dist[reversed] == -1) {
			dist[reversed] = 1 + dist[x];
			q.push(reversed);
		}
	}
	return dist[B];
}

int main() {
	int T; cin >> T;
	for (int t = 0; t < T; ++t) {
		dist.assign(10000, -1);
		cin >> A >> B;
		cout << bfs() << endl;
	}
}