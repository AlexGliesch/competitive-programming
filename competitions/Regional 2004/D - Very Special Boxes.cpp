#include <vector>
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

/*
 * the problem is easy, but one important detail: a box (2, 5, 9) and a box 
 * (5, 2, 9), for example, are to be viewed as THE SAME BOX. that is, if no 
 * other boxes are listed, the number of boxes (2, 5, 9) would be 2, not 1. 
 * 
 * in order to test whether a box can be put inside another box, just test all
 * possible combinations of (x, y, z), to check if there exists one where 
 * x <= X and y <= Y and z <= Z.
*/

struct Box {
	int x, y, z, vol;
	Box(int a, int b, int c) {
		x = min(a, min(b, c));
		y = max(min(a, b), min(max(a, b), c)); /* nifty code to get mid element
											   of 3 elements. ;-)*/
		z = max(a, max(b, c));
		vol = x * y * z;
	}

	bool operator<(const Box& b) const {
		return x < b.x or x == b.x and make_pair(y, z) < make_pair(b.y, b.z);
	}

};

int N, M, X, Y, Z;

bool can_put(const Box& b) {
	return b.x >= X and b.y >= Y and b.z >= Z or
	       b.x >= X and b.y >= Z and b.z >= Y or
	       b.x >= Y and b.y >= X and b.z >= Z or
	       b.x >= Y and b.y >= Z and b.z >= X or
	       b.x >= Z and b.y >= X and b.z >= Y or
	       b.x >= Z and b.y >= Y and b.z >= X;
}

int main() {
	while (cin >> N, N) {
		cin >> M >> X >> Y >> Z;		
		vector<Box> v;
		map<Box, int> num_boxes;

		for (int i = 0; i < M; ++i) {
			int a, b, c;
			cin >> a >> b >> c;
			v.push_back(Box(a, b, c));
			++num_boxes[Box(a, b, c)];
		}

		int min_box = -1, vol_item = X * Y * Z;
		for (int i = 0; i < M; ++i) {
			if (can_put(v[i]) and num_boxes[v[i]] >= N) {
				if (min_box == -1 or v[min_box].vol > v[i].vol) 
					min_box = i;				
			}
		}

		if (min_box == -1) cout << "impossible\n";
		else cout << v[min_box].vol - vol_item << endl;
	}
}