#include <iostream>
using namespace std;

int main()
{
	int x,y;
	cin >> x >> y;
	int volta=2;
	while((volta*x) > (volta-1)*y)
		volta++;
	cout << volta << endl;
}