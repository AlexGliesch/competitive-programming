#include <iostream>
#include <vector>

using namespace std;

int main() {

  int k, n;
  cin >> k >> n;
  vector<int> freq(k+1, 0);
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    freq[x]++;
  }

  if ((n+1) % k == 0) { // tem que aumentar
    int p = (n+1) / k;
    int index = -1;
    for (int i = 1; i <= k; i++) {
      if (freq[i] != p) {
	    if (index != -1 || freq[i] != p-1) {
	      cout << "*" << endl;
	      return 0;
	    }
	    index = i;
      }
    }
    cout << "+" << index << endl;
    return 0;
  }
  if ((n-1) % k == 0) {
    int p = (n-1) / k;
    int index = -1;
    for (int i = 1; i <= k; i++) {
      if (freq[i] != p) {
	    if (index != -1 || freq[i] != p+1) {
	      cout << "*" << endl;
	      return 0;
	    }
	    index = i;
      }
    }
    cout << "-" << index << endl;
    return 0;
  }
  if (n % k == 0) {
    int p = (n) / k;
    int indexa = -1, indexb = -1;
    for (int i = 1; i <= k; i++) {
      if (freq[i] != p) {
          if (freq[i] == p+1) {
	        if (indexa != -1) {
	          cout << "*" << endl;
	          return 0;
	        }
            indexa = i;
          } else if (freq[i] == p-1) {
	        if (indexb != -1) {
	          cout << "*" << endl;
	          return 0;
	        }
	        indexb = i;
          } else {
	          cout << "*" << endl;
	          return 0;
          }
      }
    }

    cout << "-" << indexa << " +" << indexb << endl;
  }
  return 0;
}
