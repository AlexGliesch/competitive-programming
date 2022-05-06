#include "includes.h"

class Solution {
public:
  bool dfs(int i, vector<vector<int>>& g, vector<bool>& vis, vector<bool>& ok,
           vector<int>& v) {
    if (ok[i]) return true;
    for (int j : g[i]) {
      if (vis[j]) return false;
      vis[j] = true;
      if (!dfs(j, g, vis, ok, v)) return false;
      vis[j] = false;
    }
    v.push_back(i);
    return ok[i] = true;
  }

  vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> g(numCourses);
    vector<int> req(numCourses, 0);
    for (const auto& v : prerequisites) {
      g[v[0]].push_back(v[1]);
      ++req[v[1]];
    }
    vector<bool> ok(numCourses, false);
    vector<bool> vis(numCourses, false);
    vector<int> v;
    for (int i = 0; i < numCourses; ++i)
      if (req[i] == 0) {
        vis[i] = true;
        if (!dfs(i, g, vis, ok, v)) return vector<int>();
        vis[i] = false;
      }
    if (count(ok.begin(), ok.end(), true) != numCourses) return vector<int>();
    return v;
  }
};
