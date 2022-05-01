#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;

struct segment_tree {
private:
  int n;
  vi st, v;

  void build(int i, int l, int r) {
    if (l == r) {
      st[i] = v[l];
    } else {
      int m = (l + r) / 2;
      build(2 * i + 1, l, m);
      build(2 * i + 2, m + 1, r);
      st[i] = min(st[2 * i + 1], st[2 * i + 2]);
    }
  }

  int find(int i, int sl, int sr, int l, int r) {
    if (sl >= l && sr <= r) {
      return st[i];
    } else if (l > sr || r < sl) {
      return 10000000;
    } else {
      int m = (sl + sr) / 2;
      return min(find(2 * i + 1, sl, m, l, r),
                 find(2 * i + 2, m + 1, sr, l, r));
    }
  }

public:
  segment_tree(vi w) {
    swap(v, w);
    n = v.size();
    st.assign(4 * n, 0);
    build(0, 0, n - 1);
  }

  int find(int l, int r) { return find(0, 0, n - 1, l, r); }
};

int main() {
  int n;
  while (cin >> n) {
    vi h(n, 0);
    vi p;
    for (int i = 0; i < n; i++) {
      cin >> h[i];
      if (i > 1 && h[i - 1] > h[i] && h[i - 1] > h[i - 2])
        p.push_back(i - 1);
    }

    vi left(n, 0);
    left[0] = -1;
    for (int i = 1; i < n; i++) {
      left[i] = i - 1;
      while (left[i] >= 0 && h[i] >= h[left[i]]) {
        left[i] = left[left[i]];
      }
    }

    vi right(n, 0);
    right[n - 1] = n;
    for (int i = n - 2; i >= 0; i--) {
      right[i] = i + 1;
      while (right[i] < n && h[i] >= h[right[i]]) {
        right[i] = right[right[i]];
      }
    }

    bool b = false;
    segment_tree st(h);
    for (int i = 0; i < p.size(); i++) {
      int l = st.find(left[p[i]], p[i]);
      int r = st.find(p[i], right[p[i]]);

      if (h[p[i]] - r >= 150000 && h[p[i]] - l >= 150000) {
        if (b)
          cout << " ";
        cout << (p[i] + 1);
        b = true;
      }
    }
    cout << endl;
  }

  return 0;
}