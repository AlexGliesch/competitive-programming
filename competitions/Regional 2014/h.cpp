#include <iostream>
using namespace std;

int main()
{
	int n,m;
	cin >> n >> m;
	int resp=0;
	for(int i=0;i<n;++i)
	{
		bool fez=true;
		for(int j=0;j<m;++j)
		{
			int g;
			cin >> g;
			if(g==0) fez=false;
		}
		if(fez) resp++;
	}
	cout << resp << endl;
}