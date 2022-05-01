#include <algorithm>
#include <iostream>
#include <ciso646>
#include <cmath>
#include <string>
#include <vector>
#include <iomanip>
#include <cstring>

using namespace std;

/* 
 * to consider pressing letters on the same key, i do a pre-processing on the
 * input string that inserts a # after two letters on the same key. therefore
 * the maximum size of the input becomes 280 (ex: aaaa...aaa (140 times)).
 * 
 * a state can be represented with
 * 1. the index on the input string (max 280 possible indices)
 * 2. the position of the first thumb (10 possible positions)
 * 3. the position of the second thumb (10 possible positions)
 * 
 * there are only 280*10*10 = 28000 possible states. therefore, we can run a 
 * bottom-up dp to visit all those states. the dp works as follows:
 * 
 * (where N is the size of the input, i is the current index)
 * 
 * dp(N, posA, posB) = 0
 * dp(i, posA, posB) = dist_press(input[i]) + min(
 *		dp[i+1][position(input[i])][posB] + dist_move(posA, position(input[i])),
 *		dp[i+1][posA][position(input[i])] + dist_move(posB, position(input[i])));
 * 
 * in the end, get dp(0, 4, 6)
 * 
 * further optimizations possible (but I'm lazy):
 * 
 * - dp[i][posA][posB] is always equal, so we only have to compute the upper 
 * half of each i's matrix 
 * - actually, only one position on the dp is needed, because we know that the 
 * other position is ALWAYS the same as the previous character's position. this
 * reduces the search space by 10x.
 * */

struct Point {
	Point(double x = 0, double y = 0) : x(x), y(y) {}
	double x, y;
};

double dist2d(const Point& a, const Point& b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

Point positions[] = { Point(0.5, 1.5), Point(0.5, 2.5), Point(1.5, 0.5),
					  Point(1.5, 1.5), Point(1.5, 2.5), Point(2.5, 0.5),
					  Point(2.5, 1.5), Point(2.5, 2.5), Point(3.5, 1.5),
					  Point(3.5, 2.5) };
string letters[] = { "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz", 
					 " ", "#" };
int ix[300];
double dist_press[300];
double dist_move[15][15];
string input, buffer;

double eval() {
	vector<vector<vector<double> > > dp(input.size() + 2, 
		vector<vector<double> >(12, vector<double>(12, 0)));
	for (int i = input.size() - 1; i >= 0; --i) {
		char c = input[i];
		for (int posA = 0; posA < 10; ++posA) {
			for (int posB = 0; posB < 10; ++posB) {
				dp[i][posA][posB] = dist_press[c];
				dp[i][posA][posB] += min(
					dp[i + 1][ix[c]][posB] + dist_move[posA][ix[c]],
					dp[i + 1][posA][ix[c]] + dist_move[posB][ix[c]]);
			}
		}
	}
	return dp[0][2][4];
}

int main() {
	ios_base::sync_with_stdio(false);
	memset(ix, 0, sizeof ix);
	memset(dist_press, 0, sizeof dist_press);	
	for (int i = 0; i < 256; ++i) {
		for (int j = 0; j < 10; ++j) {
			size_t where = letters[j].find((char)i);
			if (where != string::npos) {
				ix[i] = j;
				dist_press[i] = 0.2 * (1 + where);
				break;
			}
		}
	}

	memset(dist_move, 0, sizeof dist_move);
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			dist_move[i][j] = dist2d(positions[i], positions[j]) / 30.0;
		}
	}

	while (getline(cin, buffer)) {		
		input.clear();
		for (int i = 0; i < buffer.size() - 1; ++i) {
			input.push_back(buffer[i]);
			if (ix[buffer[i]] == ix[buffer[i + 1]])
				input.push_back('#');
		}
		input.push_back(buffer[buffer.size() - 1]);

		cout << setprecision(2) << fixed << eval() << endl;
	}
}