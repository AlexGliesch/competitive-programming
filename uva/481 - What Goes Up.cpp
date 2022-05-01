#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

/* LIS O(n logk) version. In order to get the correct order, you need the
 * vectors 'index' and 'parent', and then recursively go over 'parents' to
 * get the reverse order of LIS.
 *
 * Remember that lower_bound is strictly increasing (>) and upper_bound is
 * not strictly increasing (>=) */

int N;
vector<int> A, lis, parent, index;

void lis_nlogk() {
  int i_longest = -1;
  int longest = 0;
  lis.assign(N, 0);
  parent.assign(N, -1);
  index.assign(N, 0);

  for (int i = 0; i < A.size(); ++i) {
    /* upper_bound: normal lis ;  lower_bound: strictly increasing */
    int pos =
        lower_bound(lis.begin(), lis.begin() + longest, A[i]) - lis.begin();
    lis[pos] = A[i];
    index[pos] = i;

    if (pos > 0)
      parent[i] = index[pos - 1];
    if (pos == longest)
      ++longest, i_longest = i;
  }

  lis.clear();
  while (i_longest != -1) {
    lis.push_back(A[i_longest]);
    i_longest = parent[i_longest];
  }
}

int main() {
  int x;
  while (cin >> x)
    A.push_back(x);
  N = A.size();

  lis_nlogk();

  cout << lis.size() << endl << '-' << endl;
  for (int i = lis.size() - 1; i >= 0; --i)
    cout << lis[i] << endl;
}