#include <iostream>
using namespace std;

typedef long long int nat;

nat x,y;
void extendedEuclid(nat a, nat b) {
	if(b==0){
		x=1; y=0; return;
	}
	extendedEuclid(b,a%b);
	nat x1 = y;
	nat y1 = x - (a/b)*y;
	x = x1;
	y = y1;
}

int pot(int b,int p,int m)
{
	if(p==0) return 1;
	nat meio=pot(b,p/2,m);
	meio=(meio*meio)%m;
	if(p%2==1) meio=(meio*b)%m;
	return meio;
}

int main()
{
	int n,e,c;
	cin >> n >> e >> c;
	
	int p=3;
	while(n%p!=0)
		p++;
	int q=n/p;
	
	int phi = (p-1)*(q-1);
	
	extendedEuclid(e,phi);
	nat d = ((x%phi)+phi)%phi;
	
	cout << pot(c,d,n) << endl;
}