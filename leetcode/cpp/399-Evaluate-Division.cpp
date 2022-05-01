#include "includes.h"

class Solution {
public:
  vector<double> calcEquation(vector<vector<string>>& equations,
                              vector<double>& values,
                              vector<vector<string>>& queries) {

    unordered_map<string, unordered_map<string, double>> g;
    for (size_t i = 0; i < equations.size(); ++i) {
      g[equations[i][0]][equations[i][1]] = values[i];
      g[equations[i][1]][equations[i][0]] = 1.0 / values[i];
    }

    vector<double> result;
    for (const auto& query : queries) {
      const string& s = query[0];
      const string& t = query[1];
      if (g.count(s) == 0 || g.count(t) == 0) {
        result.push_back(-1.0);
        continue;
      }
      unordered_map<string, double> dist;
      queue<string> q;
      dist.insert(make_pair(s, 1));
      q.push(s);
      while (q.size()) {
        string x = q.front();
        q.pop();
        if (x == t) {
          break;
        }
        for (const auto& y : g[x]) {
          if (dist.count(y.first) == 0) {
            dist[y.first] = dist[x] * y.second;
            q.push(y.first);
          }
        }
      }
      if (dist.count(t)) {
        result.push_back(dist[t]);
      } else {
        result.push_back(-1.0);
      }
    }
    return result;
    // a/b = 2
    // a = 2b
    // b = 0.5a
    // b/c = 3
    // b = 3c
    // c = (1/3)b
    // a/c = ?
  }
};