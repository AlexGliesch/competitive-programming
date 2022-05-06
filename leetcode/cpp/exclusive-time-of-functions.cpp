// Annoying problem...

class Solution {
public:
  vector<int> exclusiveTime(int n, vector<string>& logs) {
    // Assuming 'logs' is a well-formed list of function calls, and input is
    // always well-formed
    vector<int> id, start /*1 or 0*/, timestamp, order(logs.size());
    iota(begin(order), end(order), 0);
    for (const string& s : logs) {
      auto pos = s.find_first_of(':');
      id.push_back(stoi(s.substr(0, pos)));
      auto pos2 = s.find_first_of(':', pos + 1);
      start.push_back(bool(s.substr(pos + 1, pos2 - pos - 1) == "start"));
      timestamp.push_back(stoi(s.substr(pos2 + 1, s.size() - pos2 - 1)));
    }

    sort(begin(order), end(order),
         [&](int i, int j) { return timestamp[i] < timestamp[j]; });

    vector<int> s;
    s.reserve(logs.size());
    vector<int> ans(n, 0);

    assert(order.size() == logs.size());
    for (int i = 0; i < logs.size(); ++i) {
      assert(s.empty() || start[s.back()]);
      if (start[order[i]]) { // pushing
        if (!s.empty()) {
          ans[id[s.back()]] += timestamp[order[i]] - timestamp[s.back()];
        }
        s.push_back(order[i]);
      } else { // popping
        assert(!s.empty() && id[s.back()] == id[order[i]]);
        ans[id[order[i]]] += timestamp[order[i]] - timestamp[s.back()] + 1;
        s.pop_back();
        if (!s.empty()) timestamp[s.back()] = timestamp[order[i]] + 1;
      }
    }
    return ans;
  }
};