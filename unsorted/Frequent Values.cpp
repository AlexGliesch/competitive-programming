#include <iostream>
#include <map>
#include <vector>

using namespace std;
using vi = vector<int>;

struct seg_tree {
  seg_tree(vi A_) {
    swap(A, A_);
    n = A.size();
    st.assign(4 * n, 0);
    build(1, 0, n - 1);
  }
  int rmq(int i, int j) { return rmq(1, 0, n - 1, i, j); }

private:
  vi st, A;
  int n;
  int left(int p) { return p << 1; }
  int right(int p) { return (p << 1) + 1; }
  void build(int p, int L, int R) {
    if (L == R) {
      st[p] = L;
    } else {
      build(left(p), L, (L + R) / 2);
      build(right(p), (L + R) / 2 + 1, R);
      int p1 = st[left(p)], p2 = st[right(p)];
      st[p] = (A[p1] <= A[p2] ? p1 : p2);
    }
  }
  int rmq(int p, int L, int R, int i, int j) {
    if (i > R or j < L)
      return -1;
    if (L >= i and R <= j)
      return st[p];
    int p1 = rmq(left(p), L, (L + R) / 2, i, j);
    int p2 = rmq(right(p), (L + R) / 2 + 1, R, i, j);
    if (p1 == -1)
      return p2;
    if (p2 == -1)
      return p1;
    return A[p1] <= A[p2] ? p1 : p2;
  }
};

int main() {
  int n, q;
  while (cin >> n, n) {
    cin >> q;
    map<int, int> fc, st, nxt;
    vi v(n), freq(n);

    for (int i = 0; i < n; ++i) {
      cin >> v[i];
      if (i > 0 and v[i] != v[i - 1]) {
        st[v[i]] = i;
        nxt[v[i - 1]] = i;
        fc[v[i]] = 0;
      }
      ++fc[v[i]];
    }
    st[v[0]] = 0;
    nxt[v[n - 1]] = n;

    for (int i = 0; i < n; ++i)
      freq[i] = -fc[v[i]];

    seg_tree t(freq);

    for (int i = 0; i < q; ++i) {
      int a1, b1;
      cin >> a1 >> b1;
      --a1, --b1;
      int a2 = min(b1, nxt[v[a1]]), b2 = max(a1, st[v[b1]]);
      int rmq = (a2 > b2 - 1 ? -1 : -freq[t.rmq(a2, b2 - 1)]);
      // cout<<"a1: "<<a1<<", a2: "<<a2<<", b1: "<<b1<<", b2: "<<b2<<", "
      // << "rmq: "<<rmq<<endl;
      cout << max(a2 - a1, max(b1 - b2 + 1, rmq)) << endl;
    }
  }
}