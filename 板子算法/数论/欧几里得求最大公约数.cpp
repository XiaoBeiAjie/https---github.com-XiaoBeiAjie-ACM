#include <iostream>
using namespace std;

int gcd( int x, int y){
	return y==0 ? x: gcd( y,x%y);
}

int main()
{
	int a,b;
	cin>>a>>b;
	cout<<gcd(a,b)<<endl;
	return 0;
}
