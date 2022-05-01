#include "includes.h"

class Solution {
public:
  vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
    vector<vector<string>> answer;

    map<string, vector<int>> accountsThatHaveEmail;
    for (size_t i = 0; i < accounts.size(); ++i) {
      const auto& a = accounts[i];
      set<string> emailsSet;
      for (size_t j = 1; j < a.size(); ++j)
        emailsSet.insert(a[j]);
      for (const auto& e : emailsSet)
        accountsThatHaveEmail[e].push_back(i);
    }

    vector<vector<int>> g(accounts.size());
    for (const auto& p : accountsThatHaveEmail) {
      for (int i : p.second)
        for (int j : p.second) {
          if (i != j) g[i].push_back(j), g[j].push_back(i);
        }
    }

    vector<bool> visited(accounts.size(), false);
    queue<int> q;

    for (size_t i = 0; i < accounts.size(); ++i) {
      if (!visited[i]) {
        set<string> emailsInAccI;
        q.push(i);
        visited[i] = true;
        while (q.size()) {
          int j = q.front();
          q.pop();
          for (size_t k = 1; k < accounts[j].size(); ++k)
            emailsInAccI.insert(accounts[j][k]);
          for (int nb : g[j])
            if (!visited[nb]) {
              visited[nb] = true;
              q.push(nb);
            }
        }
        vector<string> v;
        v.push_back(accounts[i][0]);
        for (const auto& e : emailsInAccI)
          v.push_back(e);
        answer.push_back(v);
      }
    }
    return answer;
  }
};