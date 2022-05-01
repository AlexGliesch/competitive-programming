#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <ciso646>
#include <map>

using namespace std;

/* 
 * DP problem. run a DP for each day of the week. the recurrence is:
 * 
 * maxpoints(time, i) {
 *		if (time >= 24:00) return 0;
 *		if (i >= N) return 0;
 *		ans = 0;
 *		min_end = minimum ending time for all tasks that start after 'time'
 *		for every task T with T.start >= time and T.start < min_end {
 *			ans = max(ans, T.points + maxpoints(T.end))
 *		}
 * }
 * 
 * do a dp on the 'time' parameter: dp[time] holds the maximum number of
 * points achievable if we start from 'time'. convert a time to int with 
 * hour * 60 + minute.
 * */

struct Task {
	int start, end, code, points;
	Task() { }
	bool operator<(const Task& t) const { return start < t.start; }
};

int time_to_int(const string& s) {
	size_t p = s.find_first_of(":");
	return atoi(string(s, 0, p).c_str()) * 60 + atoi(string(s, p + 1).c_str());
}

int dp[50 * 60], N, max_time = time_to_int("23:59");

int max_points(int time, int i, vector<Task>& tasks) {
	if (time >= max_time) return 0; 
	
	while (tasks[i].start < time and i < tasks.size()) ++i;
	if (i == tasks.size()) return 0;

	if (dp[time] == -1) {
		dp[time] = 0;
		int min_end = (1 << 28);
		for (int j = i; j < tasks.size(); ++j) {
			min_end = min(min_end, tasks[j].end);
		}

		for (int j = i; j < tasks.size() and tasks[j].start < min_end; ++j) {
			dp[time] = max(dp[time], 
				tasks[j].points + max_points(tasks[j].end, j + 1, tasks));
		}
	}
	return dp[time];
}

int main() {
	while (cin >> N, N) {
		map<string, vector<Task> > days;
		for (int i = 0; i < N; ++i) {
			string ts, te, day;
			Task T;
			cin >> T.code >> T.points >> day >> ts >> te;	
			T.start = time_to_int(ts);
			T.end = time_to_int(te);
			days[day].push_back(T);
		}

		map<string, int> day_points;
		int total_points = 0;
		for (map<string, vector<Task> >::iterator i = days.begin();
			i != days.end(); ++i) {
			memset(dp, -1, sizeof dp);
			sort(i->second.begin(), i->second.end());
			if (i->second.size()) {
				day_points[i->first] = max_points(i->second[0].start, 
					0, i->second);
				total_points += day_points[i->first];
			} else {
				day_points[i->first] = 0;
			}
		}

		cout << "Total de pontos: " << total_points << endl;
		cout << "Seg: " << day_points["Seg"] << endl;
		cout << "Ter: " << day_points["Ter"] << endl;
		cout << "Qua: " << day_points["Qua"] << endl;
		cout << "Qui: " << day_points["Qui"] << endl;
		cout << "Sex: " << day_points["Sex"] << endl;
	}
}
