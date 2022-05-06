// TLE 

#include "includes.h"

class Solution {
public:
  struct State {
    bool back = false; // going back or forward?
    int r = 0, c = 0;
    vector<bool> vis;
    int dist = 0;
    int g, h;
    bool operator<(const State& s) const {
      return tie(back, r, c, vis) < tie(s.back, s.r, s.c, s.vis);
    }
  };

  int dpfw[50][50], dpbw[50][50];

  int heur(const State& s, int n, const auto& grid) {
    if (s.back) {
      return dpbw[s.r][s.c] - grid[s.r][s.c];
    } else {
      return dpfw[s.r][s.c] - grid[s.r][s.c] + dpbw[n - 1][n - 1];
    }
  }

  int recfw(int r, int c, int n, const auto& grid, auto& dp) {
    if (r == n - 1 && c == n - 1) return grid[r][c];
    if (dp[r][c] != (1 << 28)) return dp[r][c];
    int right =
        posValid(r, c + 1, n, grid) ? recfw(r, c + 1, n, grid, dp) : (1 << 28);
    int down =
        posValid(r + 1, c, n, grid) ? recfw(r + 1, c, n, grid, dp) : (1 << 28);
    return dp[r][c] = (grid[r][c] + min(right, down));
  }

  int recbw(int r, int c, int n, const auto& grid, auto& dp) {
    if (r == 0 && c == 0) return 1;
    if (dp[r][c] != (1 << 28)) return dp[r][c];
    int left =
        posValid(r, c - 1, n, grid) ? recbw(r, c + 1, n, grid, dp) : (1 << 28);
    int up =
        posValid(r - 1, c, n, grid) ? recbw(r + 1, c, n, grid, dp) : (1 << 28);
    return dp[r][c] = (grid[r][c] + min(left, up));
  }

  bool posValid(int r, int c, int n, const auto& grid) {
    return r >= 0 && r < n && c >= 0 && c < n && grid[r][c] != -1;
  }

  int cherryPickup(vector<vector<int>>& grid) {
    int n = grid.size();
    if (n == 1) {
      return grid[0][0] == 1 ? 1 : 0;
    }
    for (size_t i = 0; i < n; ++i)
      for (size_t j = 0; j < n; ++j)
        if (grid[i][j] != -1) grid[i][j] = 1 - grid[i][j];

    for (size_t i = 0; i < n; ++i)
      for (size_t j = 0; j < n; ++j)
        dpfw[i][j] = dpbw[i][j] = (1 << 28);

    recfw(0, 0, n, grid, dpfw);
    recbw(n - 1, n - 1, n, grid, dpbw);

    State init;
    init.r = init.c = 0;
    init.back = false;
    init.vis.assign(n * n, false);
    init.vis[0] = true;
    init.dist = 1;
    init.g = grid[0][0];
    init.h = heur(init, n, grid);

    set<State> states;
    priority_queue<pair<int, State>, vector<pair<int, State>>,
                   greater<pair<int, State>>>
        pq;

    states.insert(init);
    pq.emplace(init.g + init.h, init);

    auto visitState = [&](int r, int c, const State& parent) {
      State s = parent;
      s.r = r, s.c = c;
      s.g = parent.g + (s.vis[r * n + c] ? 1 : grid[r][c]);
      s.dist++;
      s.vis[r * n + c] = true;
      s.h = heur(s, n, grid);
      auto it = states.find(s);
      if (it == end(states) || s.g < it->g) {
        if (it != end(states)) states.erase(it);
        states.insert(s);
        pq.emplace(s.g + s.h, s);
      }
    };

    while (pq.size()) {
      auto [d, s] = pq.top();
      pq.pop();
      auto it = states.find(s);
      if (it == end(states) || it->g + it->h != d) continue;
      // cout << s.r << " " << s.c << " " << s.back << " " << s.dist << " " << d
      //  << endl;
      if (s.back && s.r == 0 && s.c == 0) {
        return s.dist - s.g;
      }
      if (!s.back && s.r == n - 1 && s.c == n - 1) s.back = true;

      int dr[2] = {0, 1}, dc[2] = {1, 0};
      if (s.back) dr[1] = dc[0] = -1;
      for (int i = 0; i < 2; ++i)
        if (posValid(s.r + dr[i], s.c + dc[i], n, grid))
          visitState(s.r + dr[i], s.c + dc[i], s);
    }
    return 0;
  }
};

int main() {
  Solution s;
  vector<vector<int>> v{{1, 1, 1, 1, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0},
                        {0, 0, 0, 1, 0, 0, 1}, {1, 0, 0, 1, 0, 0, 0},
                        {0, 0, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0},
                        {0, 0, 0, 1, 1, 1, 1}};
  cout << s.cherryPickup(v) << endl;
}
// dp[i][j][back][mask]?

/*

[[1,1,1,1,0,0,0],
 [0,0,0,1,0,0,0],
 [0,0,0,1,0,0,1],
 [1,0,0,1,0,0,0],
 [0,0,0,1,0,0,0],
 [0,0,0,1,0,0,0],
 [0,0,0,1,1,1,1]]

*/