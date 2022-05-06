class RandomizedSet {
public:
  unordered_map<int, int> s;
  vector<int> v;
  RandomizedSet() { srand(time(0)); }

  bool insert(int val) {
    if (s.count(val)) return false;
    s[val] = v.size();
    v.push_back(val);
    return true;
  }

  bool remove(int val) {
    if (!s.count(val)) return false;
    int i = s[val];
    s.erase(val);
    if (i != v.size() - 1) {
      swap(v[i], v.back());
      s[v[i]] = i;
    }
    v.pop_back();
    return true;
  }

  int getRandom() {
    int i = rand() % v.size();
    return v[i];
  }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */