#include <iostream>
#include <vector>

using namespace std;

int main(){
	int c, n;
	cin >> c >> n;
	vector<int> pizza(c,0);
	
	for(i i=0;i<n;i++){
		int azeitona;
		cin >> azeitona;
		pizza[azeitona] = 1;
	}
	
	int p = c/n;
	vector<int> num(c,0);
	for(int i=0;i<p;++i)
	{
		num[0]+=pizza[i];
	}
	for(int i=1;i<c;++i)
	{
		num[i] = num[i-1]-pizza[i-1]+pizza[(i+p-1)%c];
	}
	
	bool resp=false;
	for(int i=0;i<p && !resp;++i)
	{
		bool curresp=true;
		for(int j=i;j<c && curresp;j+=p)
			if(num[j]!=1)
				curresp=false;
		if(curresp) resp=true;
	}
	
	cout << (resp?'S':'N') << endl;
}