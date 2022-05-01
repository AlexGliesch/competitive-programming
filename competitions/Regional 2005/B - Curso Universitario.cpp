#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <queue>
#include <ciso646>

using namespace std;

/* 
 * modified toposort. use a pq instead of a normal queue, where a node will
 * come before another one if it has higher priority. priorities are assigned 
 * at the beginning, with the first nodes that appear having higher priority.
 * 
 * at every semester, pop M courses from the pq (or do it until pq is empty).
 * add the neighbours of each course to "to-add" set, which will be joined
 * with the pq at the end of the semester (iteration).
 * 
 * note: don't forget to sort the courses belonging to the same semester 
 * lexicografically before printing them.
 * */

int main() {
	int N, M, prio_id;
	while (cin >> N >> M, not(N == 0 and M == 0)) {
		map<string, vector<string> > g;
		map<string, int> in, prio;
		prio_id = (1 << 28);
		for (int i = 0; i < N; ++i) {
			string str0, strk; int k;
			cin >> str0 >> k;
			if (prio.find(str0) == prio.end()) prio[str0] = --prio_id;
			for (int j = 0; j < k; ++j) {
				cin >> strk;
				if (prio.find(strk) == prio.end()) prio[strk] = --prio_id;
				g[strk].push_back(str0);
				++in[str0];
			}
		}

		for (map<string, int>::iterator i = prio.begin();
			i != prio.end(); ++i) {
			if (in.find(i->first) == in.end()) in[i->first] = 0;
			if (g.find(i->first) == g.end()) g[i->first].clear();
		}

		vector<vector<string> > semester(g.size() + 1);
		priority_queue<pair<int, string> > pq;
		for (map<string, int>::iterator i = in.begin(); i != in.end(); ++i) {
			if (i->second == 0) 
				pq.push(make_pair(prio[i->first], i->first));
		}
		
		/* run toposort */
		int num_semesters = 1, expanded = 0;
		while (pq.size()) {
			vector<string> to_add;
			expanded = 0;
			while (pq.size() and expanded < M) {				
				string v = pq.top().second; pq.pop();
				semester[num_semesters].push_back(v);
				++expanded;

				for (int i = 0; i < g[v].size(); ++i) {
					if (--in[g[v][i]] == 0)
						to_add.push_back(g[v][i]);
				}
			}
			++num_semesters;
			for (int i = 0; i < to_add.size(); ++i)
				pq.push(make_pair(prio[to_add[i]], to_add[i]));
		}

		cout << "Formatura em " << num_semesters - 1 << " semestres" << endl;
		for (int i = 1; i <= num_semesters - 1; ++i) {
			sort(semester[i].begin(), semester[i].end());
			cout << "Semestre " << i << " :";
			for (int j = 0; j < semester[i].size(); ++j)
				cout << " " << semester[i][j];
			cout << endl;
		}
	}
}