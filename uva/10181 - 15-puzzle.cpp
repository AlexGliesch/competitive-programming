#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <queue>
#include <tuple>
#include <unordered_map>
#include <vector>
#define _inl inline __attribute__((always_inline))

using namespace std;

struct state {
	uint64_t v;
	char p0;
	_inl bool operator==(const state& s) const { return v == s.v; }
	_inl bool operator<(const state& s) const { return v < s.v; }
	_inl int get(int i) const { return (v & (15LL << i * 4)) >> i * 4; }
	_inl void set(int i, int val) {
		v &= ~(15LL << i * 4);
		v |= (uint64_t(val) << i * 4);
	}
	bool solvable() {
		int sum = 0, row, i, j;
		for (i = 0; i < 16; i++) {
			if (get(i) == 0) {
				row = i / 4 + 1;
				continue;
			}
			for (j = i + 1; j < 16; j++)
				sum += (get(j) < get(i) and get(j));
		}
		return 1 - (sum + row) % 2;
	}
	int heuristic() const {
		int val = 0;
		for (int i = 0; i < 16; ++i) {
			int num = get(i);
			if (num == 0)
				continue;
			int rd = i / 4, cd = i % 4;
			int ra = (num - 1) / 4, ca = (num - 1) % 4;
			val += abs(rd - ra) + abs(cd - ca);
		}
		return val;
	}
};

namespace std {
template <>
struct hash<state> {
	size_t operator()(const state& s) const { return s.v; }
};
}  // namespace std

void a_star(const state& initial) {
	unordered_map<state, int> dist;
	unordered_map<state, state> parent;
	priority_queue<tuple<int, int, state>> pq; /* tuple: f, h, state */

	dist[initial] = 0;
	pq.push(make_tuple(-initial.heuristic(), -initial.heuristic(), initial));
	int f, h, g;
	state s;
	vector<state> nbs;
	while (pq.size()) {
		f = -get<0>(pq.top());
		h = -get<1>(pq.top());
		g = f - h;
		s = get<2>(pq.top());
		pq.pop();
		if (h == 0 or f > 45)
			break;
		if (g != dist[s])
			continue;

		static constexpr int nbs[16][4] = {
			{1, 4, -1, -1},  {0, 2, 5, -1},   {1, 3, 6, -1},	{2, 7, -1, -1},
			{0, 5, 8, -1},   {1, 4, 9, 6},	{2, 5, 7, 10},	{3, 6, 11, -1},
			{4, 9, 12, -1},  {5, 8, 10, 13},  {6, 9, 11, 14},   {7, 10, 15, -1},
			{8, 13, -1, -1}, {9, 12, 14, -1}, {10, 13, 15, -1}, {11, 14, -1, -1}};

		for (int i = 0; i < 4 and nbs[s.p0][i] != -1; ++i) {
			state nb = s;
			nb.p0 = nbs[s.p0][i];
			nb.set(nb.p0, 0);
			nb.set(s.p0, s.get(nb.p0));

			auto dn = dist.find(nb);
			if (dn == dist.end() or dn->second > g + 1) {
				dist[nb] = g + 1;
				int hnb = nb.heuristic();
				if (hnb + g + 1 > 45)
					continue;
				pq.emplace(-(hnb + g + 1), -hnb, nb);
				parent[nb] = s;
			}
		}
	}
	assert(h == 0);
	int rs = s.p0 / 4, cs = s.p0 % 4;
	string ret;
	while (parent.find(s) != parent.end()) {
		auto ss = parent[s];
		int rss = ss.p0 / 4, css = ss.p0 % 4;
		if (css < cs)
			ret += 'R';
		else if (css > cs)
			ret += 'L';
		else if (rss < rs)
			ret += 'D';
		else if (rss > rs)
			ret += 'U';
		swap(s, ss);
		swap(rs, rss);
		swap(cs, css);
	}
	reverse(begin(ret), end(ret));
	cout << ret << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	int n, x;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		state s;
		for (int i = 0; i < 16; ++i) {
			cin >> x;
			s.set(i, x);
			assert(s.get(i) == x);
			if (x == 0)
				s.p0 = i;
		}
		if (not s.solvable())
			cout << "This puzzle is not solvable." << endl;
		else
			a_star(s);
	}
}