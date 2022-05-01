#include <cstring>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

/* Generate the graph, and count the number of edges for each node that can be
 * accessed from (0, 0). If it's even, add to 'even', otherwise 'odd'.
 *
 * In order to generate the graph, each position (r, c) can have 8 neighbours:
 * (r + M, c + N), (r + M, c - N), (r - M, c + N), (r - M, c - N),
 * (r + N, c + M), (r + N, c - M), (r - N, c + M), (r - N, c - M).
 *
 * It is important to note that, when you generate the graph, it is possible
 * that some neighbours be duplicated. You have to remove duplicates.
 * */

int R, C, N, M, W;
int visited[110][110];

int odd, even;

bool ok(int r, int c) {
  return (r >= 0 && r < R && c >= 0 && c < C && visited[r][c] != -1);
}

void dfs() {
  if (!ok(0, 0))
    return;
  stack<pair<int, int>> s;
  s.push(make_pair(0, 0));

  while (s.size()) {
    int r = s.top().first, c = s.top().second;
    s.pop();
    if (visited[r][c] == 1)
      continue;
    visited[r][c] = 1;

    int val = 0;
    if (ok(r + N, c + M))
      ++val, s.push(make_pair(r + N, c + M));
    if (M && ok(r + N, c - M))
      ++val, s.push(make_pair(r + N, c - M));
    if (N && ok(r - N, c + M))
      ++val, s.push(make_pair(r - N, c + M));
    if (M && N && ok(r - N, c - M))
      ++val, s.push(make_pair(r - N, c - M));

    if (M != N) {
      if (ok(r + M, c + N))
        ++val, s.push(make_pair(r + M, c + N));
      if (N && ok(r + M, c - N))
        ++val, s.push(make_pair(r + M, c - N));
      if (M && ok(r - M, c + N))
        ++val, s.push(make_pair(r - M, c + N));
      if (M && N && ok(r - M, c - N))
        ++val, s.push(make_pair(r - M, c - N));
    }

    // cout << "s.size() : " << s.size() << endl;
    val & 1 ? ++odd : ++even;
  }
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; ++t) {
    cin >> R >> C >> M >> N >> W;

    memset(visited, 0, sizeof visited);

    for (int w = 0; w < W; ++w) {
      int r, c;
      cin >> r >> c;
      visited[r][c] = -1;
    }

    even = odd = 0;
    dfs();
    cout << "Case " << t + 1 << ": " << even << " " << odd << endl;
  }
}