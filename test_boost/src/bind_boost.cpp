#include <boost/bind.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace boost;
using namespace std;

struct point
{
	int x ,y ;
	point(int a =0 ,int b = 0 ):x(a),y(b){}
	void print(int &i)
	{
		cout<<i<<endl;
		cout<<"("<<x<<","<<y<<")"<<endl;
	}
};


int main()

{
	
	vector<int> v(10) ;
	point x(1,2) ;
	std::for_each(v.begin(),v.end(),boost::bind(&point::print,&x,_1)); 
	return 0 ;
}
