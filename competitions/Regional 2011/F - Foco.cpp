#include <iostream>
#include <vector>
#include <ciso646>
#include <algorithm>

using namespace std;

/* 
 * idea: the shot points will always be at the edge of a range.
 * 
 * greedy: sort all ranges (first the ones that start first), and starting from
 * index i = 0, do the following:
 * 
 * (given that the current range is i)
 * 
 * 1. find the range j such that j.end is smallest among all ranges that start 
 * between i.begin and i.end (including i)
 * 2. i = j
 * 3. add 1 to the final answer
 * 4. if j >= number of ranges, terminate the algorithm
 * 
 * */

struct Segment {
	Segment(int start = 0, int end = 0)
		: start(start), end(end) { }
	int start, end;

	bool operator<(const Segment& s) const {
		return start < s.start or start == s.start and end < s.end;
	}
};

int main() {
	int N; 
	ios_base::sync_with_stdio(false);
	while (cin >> N) {
		vector<Segment> v(N);
		for (int i = 0; i < N; ++i) {
			cin >> v[i].start >> v[i].end;
		}

		sort(v.begin(), v.end());

		int ans = 0, i = 0;
		while (i < N) {
			int smallest_end = v[i].end;
			int j = i;
			for (; v[j].start <= smallest_end and j < N; ++j) {
				smallest_end = min(smallest_end, v[j].end);
			}
			++ans;
			i = j;
		}
		cout << ans << endl;
	}
}