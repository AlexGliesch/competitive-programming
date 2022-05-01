#include <algorithm>
#include <ciso646>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

/* Find all SCC. I found the problem hard because of the way the input/output
 * was given, not because of the algorithm.
 * Watch out for the final sorting. */

int n;
map<char, vector<char>> g;
map<char, vector<char>> g_t;
vector<char> s;
vector<set<char>> comp;
set<char> visited;
int num_scc;
string buf[6];

void dfs1(char v) {
  if (visited.count(v) == 1)
    return;
  visited.insert(v);
  for (int i = 0; i < g[v].size(); ++i)
    dfs1(g[v][i]);
  s.push_back(v);
}

void dfs2(char v) {
  if (visited.count(v) == 1)
    return;
  visited.insert(v);
  comp[num_scc].insert(v);
  for (int i = 0; i < g_t[v].size(); ++i)
    dfs2(g_t[v][i]);
}

void kosaraju() {
  s.clear();
  num_scc = 0;
  comp.clear();
  comp.resize(g.size());
  visited.clear();

  for (map<char, vector<char>>::iterator i = g.begin(); i != g.end(); ++i) {
    dfs1(i->first);
  }

  visited.clear();
  for (int i = s.size() - 1; i >= 0; --i) {
    if (visited.count(s[i]) == 0) {
      dfs2(s[i]);
      ++num_scc;
    }
  }
}

int main() {
  bool first = true;
  while (cin >> n, n != 0) {
    g.clear();
    g_t.clear();

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < 6; ++j) {
        cin >> buf[j];
        if (!g.count(buf[j][0]))
          g[buf[j][0]] = vector<char>();
        if (!g_t.count(buf[j][0]))
          g_t[buf[j][0]] = vector<char>();
      }

      for (int j = 0; j < 5; ++j) {
        if (buf[j][0] != buf[5][0]) {
          g[buf[5][0]].push_back(buf[j][0]);
          g_t[buf[j][0]].push_back(buf[5][0]);
        }
      }
    }

    kosaraju();

    if (first)
      first = false;
    else
      cout << endl;

    set<string> sets;
    for (int i = 0; i < num_scc; ++i) {
      string s;
      for (set<char>::iterator j = comp[i].begin(); j != comp[i].end(); ++j) {
        if (j != comp[i].begin())
          s += ' ';
        s += *j;
      }
      sets.insert(s);
    }

    for (set<string>::iterator i = sets.begin(); i != sets.end(); ++i) {
      cout << *i << endl;
    }
  }
}