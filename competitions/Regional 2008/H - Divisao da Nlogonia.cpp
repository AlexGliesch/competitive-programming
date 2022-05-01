#include <iostream>
#include <ciso646>

using namespace std;

int main() {
	int K;
	while (cin >> K, K) {
		int N, M; cin >> N >> M;
		for (int i = 0; i < K; ++i) {
			int X, Y; cin >> X >> Y;
			if (X == N or Y == M) cout << "divisa" << endl;
			else if (X > N and Y > M) cout << "NE" << endl;
			else if (X < N and Y < M) cout << "SO" << endl;
			else if (X > N and Y < M) cout << "SE" << endl;
			else cout << "NO" << endl;
		}
	}
}