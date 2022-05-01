#include <iostream>
using namespaces std;

int main()
{
	int n;
	cin >> n;
	n++;
	int resp=1, power=2%n;
	while(power!=1)
	{
		resp++;
		power=(power*2)%n;
	}
	cout << resp << endl;
}