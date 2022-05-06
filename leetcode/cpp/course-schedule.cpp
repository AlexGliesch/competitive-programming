#include "includes.h"

class Solution {
public:
  bool dfs(int i, vector<vector<int>>& g, vector<bool>& vis, vector<bool>& ok) {
    if (ok[i]) return true;
    for (int j : g[i]) {
      if (vis[j]) return false;
      vis[j] = true;
      if (!dfs(j, g, vis, ok)) return false;
      vis[j] = false;
    }
    return ok[i] = true;
  }

  bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> g(numCourses);
    vector<int> req(numCourses, 0);
    for (const auto& v : prerequisites) {
      g[v[0]].push_back(v[1]);
      ++req[v[1]];
    }
    vector<bool> ok(numCourses, false);
    vector<bool> vis(numCourses, false);
    for (int i = 0; i < numCourses; ++i)
      if (req[i] == 0) {
        vis[i] = true;
        if (!dfs(i, g, vis, ok)) return false;
        vis[i] = false;
      }
    return count(ok.begin(), ok.end(), true) == numCourses;
  }
};

int main() {
  Solution s;
  vector<vector<int>> pr{{1, 4}, {4, 1}, {3, 1}, {3, 2}};
  int c = 5;
  cout << s.canFinish(c, pr) << endl;
}