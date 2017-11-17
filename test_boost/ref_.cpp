#include <boost/ref.hpp>
#include <boost/assign.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <boost/function.hpp>
#include <boost/bind.hpp>
using namespace boost;
class square
{
public:
	typedef void result_type ;
	void operator()(int& x) 
	{
		x = x*x ;
	}
};

class pnf
{
public:
	typedef void result_type ;
	void operator()(int& x)
	{
		std::cout<<x << std::endl;
	}
};

void prin(std::ostream &os,int i)
{
	os<<i<<std::endl;
}


int main()
{
	typedef double (*pfunc)(double) ;
	pfunc pf = sqrt ;
	std::cout<< boost::ref(pf) (5.0) <<std::endl;

	square sq ;
	pnf p ;
	int x = 5 ;
	sq(x) ;
	std::cout<<x <<std::endl;
	std::vector<int> v = (boost::assign::list_of(1),2,3,4,5) ;
	std::for_each(v.begin(),v.end(),sq) ;
	std::for_each(v.begin(),v.end(),p) ;

	std::function<void (int)> pt = std::bind(prin,boost::ref(std::cout),std::placeholders::_1) ;
	std::for_each(v.begin(),v.end(),pt) ;
	std::for_each(v.begin(),v.end(),p);
	return 0 ;
}
