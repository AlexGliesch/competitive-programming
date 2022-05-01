#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <ciso646>

using namespace std;

int N;
vector<string> g;

vector<int> pset, size_set;

void init_set(int n) {
	pset.assign(n, 0); size_set.assign(n, 1);
	for (int i = 0; i < n; ++i) pset[i] = i;
}

int find_set(int i) {
	return pset[i] == i ? i : (pset[i] = find_set(pset[i]));
}

bool is_same_set(int i, int j) {
	return find_set(i) == find_set(j);
}

void union_set(int i, int j) {
	if (is_same_set(i, j)) return;
	size_set[find_set(j)] += size_set[find_set(i)];
	pset[find_set(i)] = find_set(j);
}

int main() {
	cin >> N;
	init_set(N + 1);
	g.resize(N + 1);
	for (int i = 0; i < N; ++i) {
		cin >> g[i];
	}

	bool yes = true;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (g[i][j] == 'S') {
				union_set(i, j);

			} else {
				if (is_same_set(i, j)) {
					yes = false;
					break;
				}
			}
		}
	}

	if (not yes) {
		cout << -1 << endl;
		return 0;
	}

	set<pair<int, int>> sets;
	for (int i = 0; i < N; ++i) {
		int S = find_set(i);
		sets.emplace(size_set[S], S);
	}

	cout << sets.size() << endl;
	bool first = true;
	for (auto r = sets.rbegin(); r != sets.rend(); ++r) {
		if (not first) cout << " ";
		first = false;
		cout << r->first;
	}	
	cout << endl;
}