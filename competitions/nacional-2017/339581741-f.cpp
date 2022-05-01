#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

typedef long long int lli;

int main()
{
    int n;
    cin >> n;
    
    vector<pair<pair<int, int>, lli> > data;
    data.push_back(make_pair(make_pair(0, 0), 0));

    for (int i = 0; i < n; ++i)
    {
        int b, f, d;
        cin >> b >> f >> d;
        data.push_back(make_pair(make_pair(b, -f), d));
    }
    
    sort(data.begin(), data.end());
    
    map<int, lli> pd;
    pd[0] = 0;
    for (int i=0; i<data.size(); ++i) {
      int key = -data[i].first.second; lli value = data[i].second;
      auto it = pd.lower_bound(key);
      it--;
      value += it->second;
      if (pd.count(key)==0 || pd[key] < value) {
        pd[key] = value;
        while (pd.upper_bound(key) != pd.end() && pd.upper_bound(key)->second <= value)
          pd.erase(pd.upper_bound(key));
      }
    }
    cout << pd.rbegin()->second << endl;
}
