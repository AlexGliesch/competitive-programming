#include <iostream>
#include <queue>
#include <vector>
#include <ciso646>
#include <algorithm>
#include <string>
#include <unordered_set>

using namespace std;

int N;

struct State : public string {
	State() : string(N * 4, ' ') { }
	bool operator==(const State& s) const {
		return (const string&)*this == (const string&)s;
	}
	bool operator<(const State& s) const {
		return g + h > s.g + s.h;
	}
	int g = 0, h = 0;
};

struct StateHasher {
	size_t operator()(const State& s) const {
		return std::hash<string>()((const string&)s);
	}
};

int heuristic(const State& s) {
	// Find largest possible sequence
	int biggest = 0;	
	int i = 0;
	while(i < s.size()) {
		int start = i;
		if (s[i] == 'A') {			
			while (i < s.size() and s[i] == 'A') ++i;
			while (i < s.size() and s[i] == 'B') ++i;
		} else if (s[i] == 'B') {
			while (i < s.size() and s[i] == 'B') ++i;
		} else {
			++i;
		}
		biggest = max(biggest, i - start);
	}
	return (N*2 - biggest) / 2;
}

int a_star() {
	State initial;
	for (int i = N * 2; i < N * 4; i += 2) {
		initial[i] = 'B';
		initial[i + 1] = 'A';
	}
	initial.g = 0;
	initial.h = heuristic(initial);

	unordered_set<State, StateHasher> open;
	open.insert(initial);

	priority_queue<State> pq;
	pq.push(initial);

	while (pq.size()) {
		State s = pq.top();
		pq.pop();

		auto it = open.find(s);
		if (s.g != it->g) continue;

		if (s.h == 0) return s.g;

		// Neighbours of s
		for (int i = 0; i < s.size()-1; ++i) {
			if (s[i] != ' ' and s[i + 1] != ' ') {
				// Candidate boxes to move i and i+1: find possible moving place
				for (int j = 0; j < s.size() - 1; ++j) {
					if (s[j] == ' ' and s[j + 1] == ' ') {
						// Places j and j+1 are free to move
						State r = s;
						r[j] = s[i];
						r[j + 1] = s[i + 1];
						r[i] = r[i + 1] = ' ';
						it = open.find(r);
						r.g = s.g + 1;
						if (it == open.end()) {
							r.h = heuristic(r);
							open.insert(r);
							pq.push(r);
						} else if (it->g > r.g) {
							const_cast<State&>(*it).g = r.g;
							pq.push(*it);
						}
					}
				}
			}
		}
	}
}

int main() {
	while (cin >> N) {
		cout << a_star() << endl;
	}
}