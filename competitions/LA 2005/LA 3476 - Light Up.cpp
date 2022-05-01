#include <algorithm>
#include <ciso646>
#include <iostream>
#include <cstring>

using namespace std;

int R, C, B, min_lamps;
char bar[7][7], around[7][7];
const int dr[] = { 1, -1, 0, 0 }, dc[] = { 0, 0, 1, -1 };

bool ok(int r, int c) { return r >= 0 and r < R and c >= 0 and c < C; }
long long ix(int r, int c) { return (1LL << (long long)(c + C * r)); }

void backtrack(long long lit, long long lamps, int num_lamps, int r, int c) {
	if (num_lamps >= min_lamps) return;
	if (r == R) {
		if (lit != ((1LL << (R * C)) - 1)) return;
		for (int ri = 0; ri < R; ++ri) {
			for (int ci = 0; ci < C; ++ci) {
				if (bar[ri][ci] >= 0 and around[ri][ci] != bar[ri][ci]) 
					return;				
			}
		}
		min_lamps = min(min_lamps, num_lamps);
	}

	if (ok(r - 1, c - 1) and bar[r - 1][c - 1] >= 0
		and around[r - 1][c - 1] != bar[r - 1][c - 1]) return;

	backtrack(lit, lamps, num_lamps, 
		(c == C - 1) ? r + 1 : r, (c == C - 1) ? 0 : c + 1);

	if (bar[r][c] != -100 or(lit & ix(r, c))) return;

	int i = r;
	while (i >= 0 and bar[i][c] == -100) 
		lit |= ix(i--, c);	
	i = r;
	while (i < R and bar[i][c] == -100) 
		lit |= ix(i++, c);	
	i = c;
	while (i >= 0 and bar[r][i] == -100) 
		lit |= ix(r, i--);	
	i = c;
	while (i < C and bar[r][i] == -100) 
		lit |= ix(r, i++);	

	for (int i = 0; i < 4; ++i) 
		if (ok(r + dr[i], c + dc[i])) ++around[r + dr[i]][c + dc[i]];

	backtrack(lit, lamps | ix(r, c), 1 + num_lamps,
		(c == C - 1) ? r + 1 : r, (c == C - 1) ? 0 : c + 1);

	for (int i = 0; i < 4; ++i) 
		if (ok(r + dr[i], c + dc[i])) --around[r + dr[i]][c + dc[i]];
}

int main() {
	while (cin >> R >> C, R != 0 && C != 0) {
		cin >> B;
		memset(bar, -100, sizeof bar);
		memset(around, 0, sizeof around);
		long long lit = 0;
		for (int i = 0; i < B; ++i) {
			int r, c, k; cin >> r >> c >> k;
			bar[r - 1][c - 1] = k;
			lit |= ix(r - 1, c - 1);
		}
		min_lamps = (1 << 28);
		backtrack(lit, 0, 0, 0, 0);
		if (min_lamps == (1 << 28)) cout << "No solution" << endl;
		else cout << min_lamps << endl;
	}
}