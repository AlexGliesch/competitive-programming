#include <iostream>
#include <string>
#include <vector>
using namespace std;

// input[i-manacher[2*i], i+manacher[2*i]] is a palindrome
// input(i-manacher[2*i+1], i+manacher[2*i+1]] is a palindrome
vector<int> manacher(string input) {
  string s(2*input.size()+3, '#');
  s[0] = '^'; s[s.size()-1] = '$';
  for (int i=0; i<input.size(); ++i)
    s[2*i+2] = input[i];
  vector<int> radius(s.size(), 0);
  int center = 1, range = 1;
  for (int i = 2; i < s.size()-2; ++i) {
    if (i + radius[2*center-i] < range) {
      radius[i] = radius[2*center-i];
    } else {
      radius[i] = range-i;
      while (s[i+radius[i]+1] == s[i-radius[i]-1])
        radius[i]++;
      center = i;
      range = i + radius[i];
    }
  }
  vector<int> result(2*input.size()-1);
  for (int i=0; i<result.size(); ++i)
    result[i] = radius[i+2]/2;
  return result;
}

char input[5000002];
int main() {
  scanf("%s", input);
  string s(input);
  vector<int> mn = manacher(s);
  vector<int> degree(s.size()+1, 0);
  for (int i=0; i<s.size(); ++i)
    if (mn[i] == (i+1)/2)
      degree[i+1] = 1+degree[(i+1)/2];
  long long int sum=0;
  for (int i=0; i<degree.size(); ++i)
    sum += degree[i];
  cout << sum << endl;
}