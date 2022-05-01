#include <algorithm>
#include <ciso646>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/* Problema fácil de resolver mas chato de codificar. Tricky cases: mandar mais
 * de um AC pro mesmo problema, times que só mandam submissões R, U ou E. Usei
 * stable_sort pra preservar a ordem de team number.
 * Não esquecer de printar linha em branco entre testes. */

using namespace std;

struct Team {
  bool operator<(const Team &t) const {
    return problems_solved > t.problems_solved or
           problems_solved == t.problems_solved and
               penalty_time < t.penalty_time;
  }

  vector<bool> solved = vector<bool>(10, false);
  vector<int> penalty = vector<int>(10, 0);
  bool on = false;
  int problems_solved = 0;
  int penalty_time = 0;
  int team_number = 0;
};

int main() {
  int T;
  cin >> T;
  string buf;
  getline(cin, buf);
  getline(cin, buf);
  for (int t = 0; t < T; ++t) {
    if (t)
      cout << endl;
    vector<Team> teams(101);
    for (int i = 0; i < teams.size(); ++i)
      teams[i].team_number = i;

    while (getline(cin, buf) and buf.size()) {
      istringstream ss(buf);
      int contestant, problem, time;
      char L;
      ss >> contestant >> problem >> time >> L;
      if (teams[contestant].solved[problem])
        continue;
      teams[contestant].on = true;
      if (L == 'C') {
        teams[contestant].solved[problem] = true;
        teams[contestant].penalty[problem] += time;
      } else if (L == 'I') {
        teams[contestant].penalty[problem] += 20;
      }
    }

    for (auto &team : teams) {
      for (int i = 0; i < team.solved.size(); ++i) {
        if (team.solved[i]) {
          ++team.problems_solved;
          team.penalty_time += team.penalty[i];
        }
      }
    }

    stable_sort(begin(teams), end(teams));
    for (auto &team : teams) {
      if (team.on)
        cout << team.team_number << ' ' << team.problems_solved << ' '
             << team.penalty_time << endl;
    }
  }
}