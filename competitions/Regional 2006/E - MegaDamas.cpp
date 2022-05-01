#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

/* 
 * the board is maximum 20x20, so we can do a complete search. start a dfs
 * from every cell where there is a player's piece, and try to eat an opponent's
 * piece in every direction, calling the dfs recursively to count the number
 * of eats.
 * 
 * the dfs returns the maximum between eating in each diagonal and calling the
 * dfs recursively on the position after eating. if it can't eat anything, it
 * returns 0.
 * 
 * no need to store a 'visited' vector, but you must update the board and pass 
 * a copy of it to every function, or, update it and restore the previous state
 * after the call (what I did). 
 * 
 * watch out for edges; i recomment making a function that tells whether a 
 * position is in bounds, and whether it is free, player or an opponent.
 * 
 * the hard part of this problem, in my opinion, was setting up the board, i.e.,
 * putting the pieces in their correct positions as the input asked. for that,
 * I recommend adding a debugging function that prints your board as you read
 * it, so you make sure you're reading it correctly.
 * */

typedef vector<vector<int> > vvi;
int n, m;

bool is_valid(int row, int col){
	return row < n and col < m and row >= 0 and col >= 0;
}

bool is_opponent(int row, int col, const vvi& g) {
	return is_valid(row, col) and g[row][col] == 2;
}

bool is_free(int row, int col, const vvi& g){
	return is_valid(row, col) and g[row][col] == 0;
}

int dfs(int row, int col, vvi& g);

int tryeat(int row, int col, int offr, int offc, vvi& g) {
	int ans = 0;
	if (is_opponent(row + offr, col + offc, g) and 
		is_free(row + 2 * offr, col + 2 * offc, g)) {
		g[row + 2 * offr][col + 2 * offc] = 1;
		g[row + offr][col + offc] = 0;;
		g[row][col] = 0;

		ans = 1 + dfs(row + 2 * offr, col + 2 * offc, g);

		/* restore previous state*/
		g[row + 2 * offr][col + 2 * offc] = 0;
		g[row + offr][col + offc] = 2;
		g[row][col] = 1;
	}	
	return ans;
}

int dfs(int row, int col, vvi& g) {
	int ans = 0;
	ans = max(ans, tryeat(row, col, 1, 1, g));
	ans = max(ans, tryeat(row, col, 1, -1, g));
	ans = max(ans, tryeat(row, col, -1, 1, g));
	ans = max(ans, tryeat(row, col, -1, -1, g));
	return ans;
}

int main(){
	while (cin >> n >> m, not (m==0 and n==0)) {
		int num_cells = (int)(ceil((n*m) / 2.0));

		vvi g(30, vector<int>(30, -1));
		int row = 0, col = 0;
		for (int i = 0; i < num_cells; ++i) {
			cin >> g[row][col];
			col += 2;
			if (col >= m) {
				++row;
				if (row % 2 != 0) col = 1;
				else col = 0;
			}
		}

		int ans = 0;
		for (row = 0; row < n; ++row) {
			for (col = 0; col < m; ++col) {
				if (g[row][col] == 1) {
					vvi g2 = g;
					ans = max(ans, dfs(row, col, g));
				}
			}
		}
		cout << ans << endl;
	}
}