#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <ciso646>
#include <map>
#define MAX_TIME 3600

using namespace std;

struct Task {
	int start, end, points;
	Task() {}
	bool operator<(const Task& t) const { return start < t.start; }
};

int dp[MAX_TIME + 10];

int max_points(int time, int i, vector<Task>& tasks) {
	if (time >= MAX_TIME) return 0;

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

int get_max_points(vector<Task>& tasks) {
	memset(dp, -1, sizeof dp);
	sort(tasks.begin(), tasks.end());
	return max_points(tasks[0].start, 0, tasks);
}

int main() {
	ios_base::sync_with_stdio(false);
	int N; cin >> N;
	vector<Task> tasks(N);
	for (int k = 0; k < N; ++k) {
		cin >> tasks[k].start >> tasks[k].end;
		tasks[k].points = tasks[k].end - tasks[k].start;
	}
	cout << get_max_points(tasks) << endl;
}