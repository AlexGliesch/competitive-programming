#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int ca, ba, pa;
    cin >> ca >> ba >> pa;
    
    int cr, br, pr;
    cin >> cr >> br >> pr;
    
    cout << -(min(0, ca - cr) + min(0, ba - br) + min(0, pa - pr)) << endl;
}
