#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int k, n;
	cin >> k >> n;
	vector<int> counts(k+1, 0);
	int max_count = 0, min_count = 100000;
	int max_count_x = -1, min_count_x = -1;
	for (int i = 0; i < n; ++i)
	{
	    int x;
	    cin >> x;
	    counts[x] += 1;

	}
	for (int i =1; i < counts.size(); ++i)
	{
        if (min_count > counts[i])
            { min_count = counts[i]; min_count_x = i; }
        if (max_count < counts[i])
            { max_count = counts[i]; max_count_x = i; }
	}
    vector<int> counts2(counts);
    sort(counts2.begin(), counts2.end());
        

	if (max_count - min_count == 2)
	{
	    int count_min = 0, count_max = 0;
	    for (int i = 0; i < counts.size(); ++i)
	    {
	        if (counts[i] == min_count)
	            count_min++;
            else if (counts[i] == max_count)
                count_max++;
	    }
	    if (count_min > 1 or count_max > 1)
	        cout << "*" << endl;
        else
        {
            cout << "-" << max_count_x << " +" << min_count_x << endl;
        }
	}
	
	else if (max_count - min_count == 1)
	{

        if (counts2[1] == counts2[2])
        {
            if (counts2[k] == counts2[k-1])
                { cout << "*" << endl; return 0; }
            for (int i = 1 ; i < counts.size(); ++i)
            {
                if (counts[i] == counts2[counts2.size()-1])
                    { cout << "-" << i << endl; break;}
            }
        }
        else
        {
           
           for (int i = 1; i < counts.size(); ++i)
           {
            if (counts[i] == counts2[1])
                { cout << "+" << i << endl; break; }
           }
        }
        
	}
	else
	    cout << "*" << endl;
}
