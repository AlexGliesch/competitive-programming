class FirstUnique {
public:
  map<int, int> f;
  queue<int> q;
    
  FirstUnique(vector<int>& nums) {
    for (int i : nums) add(i);
  }

  int showFirstUnique() {
    while (f[q.front()] != 1 && !q.empty()) q.pop();
    if (q.empty()) return -1;
    return q.front();
  }

  void add(int value) {
    if (f.count(value) == 0) f[value] = 0;
    ++f[value];
    if (f[value] == 1) q.push(value);
  }
};

/**
 * Your FirstUnique object will be instantiated and called as such:
 * FirstUnique* obj = new FirstUnique(nums);
 * int param_1 = obj->showFirstUnique();
 * obj->add(value);
 */