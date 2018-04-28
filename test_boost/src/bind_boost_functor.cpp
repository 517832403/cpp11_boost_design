#include <boost/bind.hpp>
#include <iostream>
struct f
{
	typedef int result_type ;
	int operator()(int a,int b)
	{
		return a+b ;
	}
};
int main()
{
	std::cout<< boost::bind(f(),_1,_2)(10,20) <<std::endl;
	return 0 ;
}
