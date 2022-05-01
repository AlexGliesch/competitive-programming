#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ciso646>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	int x, y; cin >> x >> y;
	vector<string> m(y);
	for (int i = 0; i < y; ++i) {
		cin >> m[i];
	}
	if (m[0][0] == '*') {
		cout << "*" << endl; return 0;
	} else if (m[0][0] == '.') {
		cout << "!" << endl; return 0;
	}

	int dx = 0, dy = 0;
	int px = 0, py = 0;
	vector<vector<bool>> visited(y, vector<bool>(false, x));
	int num_visited = 0;
	bool yes = false;
	while (num_visited < x*y) {
		if (py < 0 or py >= y or px < 0 or px >= x) {
			yes = false;
			break;
		}

		char c = m[py][px];
		if (c == '*') { 
			yes = true;
			break;
		} else if (c == '.') {
			visited[py][px] = true;
			++num_visited;
			px += dx;
			py += dy;
			continue;
		}
		
		if (visited[py][px]) {
			yes = false;
			break;
		}
		visited[py][px] = true;
		++num_visited;

		if (c == '>') {
			dx = 1, dy = 0;
		} else if (c == '<') {
			dx = -1, dy = 0;
		} else if (c == '^') {
			dy = -1, dx = 0;
		} else if (c == 'v') {
			dy = 1, dx = 0;
		}
		
		px += dx;
		py += dy;
	}
	if (yes) cout << "*" << endl;
	else cout << "!" << endl;
}