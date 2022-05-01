#include <algorithm>
#include <iostream>

using namespace std;

int k, v[13];

int main() {
  bool first = true;
  while (cin >> k, k != 0) {
    if (first)
      first = false;
    else
      cout << endl;
    for (int i = 0; i < k; ++i)
      cin >> v[i];
    for (int i1 = 0; i1 < k; ++i1)
      for (int i2 = i1 + 1; i2 < k; ++i2)
        for (int i3 = i2 + 1; i3 < k; ++i3)
          for (int i4 = i3 + 1; i4 < k; ++i4)
            for (int i5 = i4 + 1; i5 < k; ++i5)
              for (int i6 = i5 + 1; i6 < k; ++i6)
                cout << v[i1] << " " << v[i2] << " " << v[i3] << " " << v[i4]
                     << " " << v[i5] << " " << v[i6] << endl;
  }
}