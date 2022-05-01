#include <string>
#include <iostream>
#include <algorithm>
#include <ciso646>
#include <vector>

using namespace std;

/* 
 * Greedy algorithm. The idea is recursive:
 * 
 * get_max(str, D) {
 *		N = str.size()
 *      j = maximum element index in S[0..N-D]
 *		return S[j] + get_max(S[j+1..N], D-1)
 * }
 * 
 * This recursive idea can easily be implemented as a while. Also, another
 * optimization needed is, instead of creating a new string at every call 
 * (S[j+1..N]), pass just an offset of the original string to the recursive 
 * call.
 * 
 * This should work reasonably well, but it's not enough for TLE. The problem is
 * getting the maximum element index in S[0..N-D] is too costly, O(N), so we
 * need an efficient range-minimum-query algorithm: construct a segment tree
 * for the original S. Then the queries can be done in O(logN).
 * 
 * */

template<typename T>
struct SegmentTree {
public:
	SegmentTree(const T& A) {
		this->A = A;
		n = A.size();
		st.assign(4 * n, 0);
		build(1, 0, n - 1);		
	}

	/* Get index of maximum/minimum element between indices 
	 * i and j, inclusive. */
	int rmq(int i, int j) { return rmq(1, 0, n - 1, i, j); }

private:
	vector<int> st;
	T A;
	int n;

	int left(int p) { return p << 1; }
	int right(int p) { return (p << 1) + 1; }

	void build(int p, int L, int R) {
		if (L == R) {
			st[p] = L;
		} else {
			build(left(p), L, (L + R) / 2);
			build(right(p), (L + R) / 2 + 1, R);
			int p1 = st[left(p)], p2 = st[right(p)];
			/* change >= to <= according to necessity */
			st[p] = (A[p1] >= A[p2]) ? p1 : p2;
		}
	}

	int rmq(int p, int L, int R, int i, int j) {
		if (i > R or j < L) return -1;
		if (L >= i and R <= j) return st[p];
		int p1 = rmq(left(p), L, (L + R) / 2, i, j);
		int p2 = rmq(right(p), (L + R) / 2 + 1, R, i, j);
		if (p1 == -1) return p2;
		if (p2 == -1) return p1;
		/* change >= to <= according to necessity */
		return (A[p1] >= A[p2]) ? p1 : p2;
	}	
};

int main() {
	ios_base::sync_with_stdio(false);
	int N, D;
	string S, ans;
	while (cin >> N >> D, N or D) {
		string S; cin >> S;						
		SegmentTree<string> st(S);
		ans.clear();
		int j = 0;
		D = N - D;
		while (D > 0) {
			int N = S.size() - j;
			int i = st.rmq(j, j + N - D);
			ans.push_back(S[i]);
			j = (i + 1);
			--D;
		}

		cout << ans << endl;		
	}
}