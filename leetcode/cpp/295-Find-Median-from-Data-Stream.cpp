class MedianFinder {
  priority_queue<int> hl;
  priority_queue<int, vector<int>, greater<int>> hr;
  int n;

  // elements <median or >median don't need to be sorted
  // keep a heap on either side (?)
  //

public:
  MedianFinder() : n(0) {}

  void addNum(int num) {
    if (n == 0 || num <= hl.top())
      hl.push(num);
    else
      hr.push(num);
    ++n;

    while (hl.size() < hr.size() + n % 2) {
      assert(hr.size() > 0);
      hl.push(hr.top());
      hr.pop();
    }
    while (hr.size() < hl.size() - n % 2) {
      assert(hl.size() > 0);
      hr.push(hl.top());
      hl.pop();
    }
    assert(hl.size() - hr.size() <= 1);
  }

  double findMedian() {
    if (n % 2 == 1)
      return hl.top();
    else
      return (hl.top() + hr.top()) / 2.0;
  }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */