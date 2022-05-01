#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

/* 
 * a system of equations that is guaranteed that there will always be at least
 * one equation that is trivially solvable. so we can just run a simulation on
 * it: at every iteration, find the equation where all variables are the same,
 * and then you can trivially identify that variable's value, and substitute
 * it on all the other equations. store the variable values in a map so that
 * you can iterate over them in order, at the end. 
 * */

int L, C;

int main() {
    ios_base::sync_with_stdio(false);
    while(cin >> L >> C) {
        vector<int> sys_val(L + C);
        vector<vector<string>> sys(L + C);
        set<string> vars;
        map<string, int> vals;

        for (int i = 0; i < L; ++i) {
            for (int j = 0; j < C; ++j) {
                string s; cin >> s;
                vars.insert(s);
                sys[i].push_back(s);
                sys[L + j].push_back(s);
            }
            cin >> sys_val[i];
        }
        for (int i = 0; i < C; ++i)
            cin >> sys_val[i + L];

        while (vals.size() != vars.size()) {
            string cur;
            for (int i = 0; i < L + C; ++i) {
                if (sys[i].size() and all_of(begin(sys[i]), end(sys[i]),
                    [&](const string& s) { return s == sys[i][0]; })) {
                    vals[sys[i][0]] = sys_val[i] / (int)sys[i].size();
                    cur = sys[i][0];
                    break;
                }
            }

            int v = vals[cur];
            for (int i = 0; i < L + C; ++i) {
                int ct = count(begin(sys[i]), end(sys[i]), cur);
                if (ct) {
                    sys_val[i] -= ct * v;
                    sys[i].erase(
                        remove_if(begin(sys[i]), end(sys[i]),
                                  [&](const string& s) { return s == cur; }),
                        sys[i].end());
                }
            }
        }

        for (auto& p : vals) {
            cout << p.first << " " << p.second << endl;
        }
    }
}
