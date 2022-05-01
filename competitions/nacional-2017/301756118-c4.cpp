#include <iostream>
#include <vector>

using namespace std;

int main() {

  int k, n;
  cin >> k >> n;
  vector<int> freq(k, 0);
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    freq[x-1]++;
  }
  int goal = (n+1)/k;
  int dec=-1, inc=-1;
  bool valid = true;
  for (int i=0; i < k; ++i)
    if (freq[i] != goal) {
      if (freq[i] == goal-1)
        if (inc == -1)
          inc = i;
        else
          valid = false;
      else if (freq[i] == goal+1)
        if (dec == -1)
          dec = i;
        else
          valid = false;
      else
        valid = false;
    }
  inc++; dec++;
  if (valid == false)
    cout << '*' << endl;
  else if (inc == 0)
    cout << '-' << dec << endl;
  else if (dec == 0)
    cout << '+' << inc << endl;
  else
    cout << '-' << dec << " +" << inc << endl;
}
