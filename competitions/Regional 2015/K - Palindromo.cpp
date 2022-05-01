#include <string>
#include <iostream>
#include <algorithm>
#include <ciso646>
#include <cstring>
#include <vector>

using namespace std;

/* 
 * dp: two pointers, one going from begin to end and the other one the other 
 * way around.
 * 
 * f(p1, p2):
 *	   if (p1 > p2) -> 0
 *	   
 *	   if (p1 = p2) -> v[p1]
 * 
 *	   if (s[p1] = s[p2]) -> max(v[p1] + v[p2] + f(p1+1, p2-1), 
 *							     f(p1+1, p2),
 *							     f(p1, p2-1))
 *	   else -> max(f(p1+1, p2), 
 *				   f(p1, p2-1)) 
 * */

struct Answer {
	int score, size;
	Answer(int score = -1, int size = -1) : score(score), size(size) {}
	bool operator<(const Answer& a) const {
		return score < a.score or score == a.score and size < a.size;
	}
};

string s;
vector<int> v;
vector<vector<Answer>> dp;

Answer f(int p1, int p2) {
	if (p1 > p2) return { 0, 0 };
	if (dp[p1][p2].size != -1) 
		return dp[p1][p2];
	if (p1 == p2) 
		return dp[p1][p2] = max(Answer{ 0, 0 }, Answer{ v[p1], 1 });
	if (s[p1] == s[p2]) {
		auto a = f(p1 + 1, p2 - 1);
		return dp[p1][p2] = max(Answer{ v[p1] + v[p2] + a.score, 2 + a.size },
			max(f(p1 + 1, p2), f(p1, p2 - 1)));
	} else {
		return dp[p1][p2] = max(f(p1 + 1, p2), f(p1, p2 - 1));
	}	
}

int main() {
	ios_base::sync_with_stdio(false);
	while (cin >> s) {
		int N; cin >> N;
		v.assign(s.size() + 1, 0);
		dp.assign(s.size() + 1, vector<Answer>(s.size() + 1));
		for (int i = 0; i < N; ++i) {
			int x; cin >> x;
			v[x - 1] = 1;
		}
		auto a = f(0, s.size() - 1);
		cout << a.size << endl;
	}
}