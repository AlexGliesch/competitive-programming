class TimeMap {
  unordered_map<string, map<int, string>> t;

public:
  TimeMap() {}

  void set(string key, string value, int timestamp) {
    t[key].emplace(timestamp, value);
  }

  string get(string key, int timestamp) {
    auto& m = t[key];
    auto it = m.lower_bound(timestamp);
    if (it == end(m)) return m.size() ? m.rbegin()->second : "";
    assert(m.size() > 0);
    if (it->first == timestamp) return it->second;
    if (it->first == begin(m)->first)
      return "";
    else
      return prev(it)->second;
  }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */