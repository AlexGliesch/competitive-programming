#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <ciso646>
#include <cstring>

using namespace std;

int R, C, K;
int dc[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dr[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
int num_visited;
int best_area;
bool visited[310][310];
vector<string> board;

bool valid(int row, int col, int lbr, int lbc, int ubr, int ubc) {
	return not (row < lbr or row >= ubr or col < lbc or col >= ubc);
}

void dfs(int row, int col, int lbr, int lbc, int ubr, int ubc) {
	//cout << "dfs (" << row << ", " << col << ", " << lbr << ", " 
		//<< lbc << ", " << ubr << ", " << ubc << ")" << endl;;	
	if (not valid(row, col, lbr, lbc, ubr, ubc)) return;
	if (visited[row][col]) return;
	++num_visited;
	visited[row][col] = true;
	for (int i = 0; i < 8; ++i) {
		int nr = row + dr[i], nc = col + dc[i];
		if (not valid(nr, nc, lbr, lbc, ubr, ubc)) continue;			
		if (board[nr][nc] == '.') {
			dfs(nr, nc, lbr, lbc, ubr, ubc);
		}
	}
}

int main() {
	while (cin >> R >> C >> K, not(R == 0 and C == 0 and K == 0)) {
		board.clear(); board.resize(R);
		for (int i = 0; i < R; ++i) cin >> board[i];

		best_area = (1 << 28);
		for (int Br = 1; Br <= R; ++Br) {
			for (int Bc = 1; Bc <= C; ++Bc) {
				if (Br*Bc < K) continue;
				for (int r = 0; r + Br <= R; ++r) {
					for (int c = 0; c + Bc <= C; ++c) {
						memset(visited, false, sizeof visited);						
						for (int i = 0; i < Br; ++i) {
							for (int j = 0; j < Bc; ++j) {								
								if (board[r + i][c + j] == '.' and
									not visited[r + i][c + j]) {									
									num_visited = 0;
									dfs(r + i, c + j, r, c, r + Br, c + Bc);
									if (num_visited >= K) {										
										/*if (best_area > Br*Bc) {
											cout << "best at (" << r << ", "
												<< c << ", " << Br << ", " << Bc << ")" << endl;
										}*/
										best_area = min(best_area, Br*Bc);										
									}
								}
							}
						}
					}
				}
			}
		}
		cout << best_area << endl;
	}
}