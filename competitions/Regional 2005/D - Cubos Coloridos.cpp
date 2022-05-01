#include <set>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

/* 
 * idea: two cubes are the same if all their corners are equal.
 * 
 * two corners are equal if they have all equal indices as neighbours, and also,
 * the indices appear in the same order (clockwise or counter-clockwise).
 * for instance, the corner (0,1,2) is equal to (2,0,1) and (1,2,0), but it is
 * NOT equal to the corners (0,2,1), (1,0,2) and (2,1,0). 
 * 
 * in order to do that, you must store in memory the corner order of the cube 
 * consistently: all corners must have their index orders in either clockwise
 * or counter-clockwise direction.
 * 
 * a corner can be represented by a single integer, the following way:
 * enumerate all equivalent corners, i.e.,  equiv((x,y,z)) 
 * = [(x,y,z), (z,x,y), (y,z,x)]. the integer for the corner C is then
 * max(e[0] * 3 + e[2] * 5 + e[2] * 7 for e in equiv(C)). we use 3, 5 and 7
 * because they are primes and therefore will provide a unique representation.
 * it doesn't matter if you use max or min.
 *  
 * a cube is represented as a vector of corners. so add all the vectors of
 * corners corresponding to each cube to a set, and count how many elements
 * in that set.
 * */

int main() {
	int N, order[] = { 4, 1, 0, 4, 0, 3, 4, 3, 5, 4, 5, 1, 2, 3, 0,
		2, 0, 1, 2, 1, 5, 2, 5, 3 };
	while (cin >> N, N) {
		set<vector<int> > corners;
		for (int i = 0; i < N; ++i) {
			vector<int> c(6), corner(8);
			for (int j = 0; j < 6; ++j) cin >> c[j];
			for (int j = 0; j < 8; ++j) {
				int x = c[order[j * 3]], y = c[order[j * 3 + 1]],
					z = c[order[j * 3 + 2]];
				int a = 3 * x + 5 * y + 7 * z;
				int b = 3 * z + 5 * x + 7 * y;
				int c = 3 * y + 5 * z + 7 * x;
				corner[j] = (max(a, max(b, c)));
			}
			sort(corner.begin(), corner.end());
			corners.insert(corner);
		}
		cout << corners.size() << endl;
	}
}