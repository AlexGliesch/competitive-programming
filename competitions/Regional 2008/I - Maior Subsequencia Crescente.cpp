#include <iostream>
#include <algorithm>
#include <ciso646>

using namespace std;

/* 
 * Note that normal LIS algorithm won't work here, because we need a longest
 * increasing CONTIGUOUS subsequence. The idea:
 * 
 * First, for element in the matrix, compute the longest strictly increasing
 * contiguous sequence starting at that element, taking into account only
 * the element's line in the matrix. So, if we have the matrix:
 * 
 * 1 2 1 2
 * 9 6 7 3
 * 8 7 2 8
 * 
 * we will create a matrix "line-lis", having the values:
 * 
 * 2 1 2 1
 * 1 2 1 1
 * 1 1 2 1
 * 
 * This should be done in O(n^2).
 * 
 * Now, the main part: for every element in the matrix, you try to find the
 * longest LIS on the matrix that has that element as top-left corner. To do 
 * that, you start with a sub-matrix width equal to the line-lis of that 
 * element, and work your way downwards (that is, increasing the row index),
 * trying to add as many elements from the line below as you can. As the
 * height of the sub-matrix increases, the width will decrease, as you will find
 * that the line-lis of the element below the original one will be smaller than
 * the current width; you should take the new width to be the minimum of those 
 * values. Also, when the first element on the line below is <= than the
 * last element of the current line, you should shrink the width, until either
 * the width is 0 (which means adding an extra line is not acceptable), or the
 * new element is greater. In order to find out how much you need to shrink, 
 * you can use a binary search to find the first element in the current line 
 * which is smaller than the first element in the line below.
 * 
 * Before adding a line to the sub-matrix, you should update the best value 
 * so far with the current sub-matrix size.
 * 
 * So far, this algorithm has O(n^3 log(n)) and should work. However, this 
 * complexity is too large for the given limits (n = 600), so one optimization 
 * is needed: the sub-matrix of an element (i, j) will surely be greater or
 * equal then all the sub-matrices of that sub-matrix. So we can possibly 
 * jump more than one column after every iteration, by adding to j the
 * width of the last found sub-matrix (if that width is 0, you just add 1).
 * 
 * Anyway, it's very hard to explain in plain English, so please do yourself a 
 * favor and just look at the code. 
 * 
 * */

int line_lis[610][610], mat[610][610], N, M;

int main() {
	ios_base::sync_with_stdio(false);
	while (cin >> N >> M, N or M) {
		for (int i = 0; i < N; ++i) {
			int last_lis = 0;
			for (int j = 0; j < M; ++j) {
				cin >> mat[i][j];
				if (j == 0 or mat[i][j] <= mat[i][j - 1]) {
					for (int k = j - 1; k >= last_lis; --k)
						line_lis[i][k] = j - k;
					last_lis = j;
				}
			}

			for (int k = M - 1; k >= last_lis; --k)
				line_lis[i][k] = M - k;
		}

		int ans = 0;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M;) {
				int width = line_lis[i][j];
				ans = max(ans, width);
				for (int k = i + 1; k < N; ++k) {
					width = lower_bound(&mat[k - 1][j], 
						&mat[k - 1][j + width], mat[k][j]) - &mat[k - 1][j];					
					if (width == 0) break;

					width = min(width, line_lis[k][j]);
					ans = max(ans, width * (k - i + 1));
				}
				j += max(1, width);
			}
		}
		cout << ans << endl;
	}
}