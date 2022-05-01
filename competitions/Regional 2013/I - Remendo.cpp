#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int n, c, size_big, size_small;
vector<int> holes, holes2;
int dp[1010];

int remendos(int i) {
	if (i >= n) return 0;
	if (dp[i] == -1) {
		int njb = i;
		while (holes2[njb] <= holes2[i] + size_big and njb < n) 
			++njb;
		
		int njs = i;
		while (holes2[njs] <= holes2[i] + size_small and njs < n) 
			++njs;
			
		dp[i] = min(size_big + remendos(njb), size_small + remendos(njs));
	}
	return dp[i];
}

int main() {
	while (cin >> n >> c >> size_big >> size_small) {
		holes.clear(); holes.resize(n);
		for (int i = 0; i < n; ++i) {
			cin >> holes[i];
		}
		sort(holes.begin(), holes.end());
		
		int best = (1 << 28);
		for (int i = 0; i < n; ++i) {
			holes2 = holes;			
			for (int j = 0; j < n; ++j) {
				holes2[j] = holes[(j + i) % n];
				if (n - j <= i) holes2[j] += c;
			}
			memset(dp, -1, sizeof dp);
			int ans = remendos(0);
			if (ans < best)
				best = ans;
		}
		cout << best << endl;
	}	
}
