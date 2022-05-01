#include <algorithm>
#include <array>
#include <ciso646>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

/*
 * a sub-problem of this general problem is to split a plank with any two edges
 * c[i] and c[j]. when you split a plank with indexxes 'start' and 'end' in
 * position 'i', the total cost is
 * c[end] - c[start] + split(s, i) + split(i, e), that is, the cost
 * of splitting the upper portion plus the cost of splitting the lower portion
 * plus the length of the plank.
 *
 * this way, we have the recursion:
 *
 * min_cut(start, end):
 *
 * - if end = start + 1, there are no cuts to be made in between. return 0.
 *
 * - else, return c[end] - c[start]
 *		+ min { min_cut(start, i) + min_cut(i, end), for start < i < end
 *}.
 *
 * ps: note that the problem input does not have to be sorted. so we must sort
 * it before starting the algorithm.
 * also, we must add the start and end of the original (unsplit) plank, which
 * are 0 and 'l'.
 *
 * */

int l, n, c[55], dp[55][55];

int min_cut(int start, int end) {
  if (end == 1 + start)
    return 0;
  if (dp[start][end] != -1)
    return dp[start][end];
  dp[start][end] = numeric_limits<int>::max();
  for (int i = start + 1; i < end; ++i)
    dp[start][end] =
        min(dp[start][end],
            min_cut(start, i) + min_cut(i, end) + c[end] - c[start]);
  return dp[start][end];
}

int main() {
  while (cin >> l, l) {
    cin >> n;
    c[0] = 0, c[n + 1] = l;
    for (int i = 1; i <= n; ++i)
      cin >> c[i];
    sort(c, c + n);
    memset(dp, -1, sizeof dp);
    cout << "The minimum cutting is " << min_cut(0, n + 1) << "." << endl;
  }
}