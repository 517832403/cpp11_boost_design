#include "observer_11.h"
int main()
{
	Events<std::function<void(int,int)>> myevent ;

	auto key = myevent.Register(print) ;
	stA t ;
	auto lambda_key = myevent.Register([&t](int a,int b){ t.a = a,t.b = b ;}) ;
	
	std::function<void(int,int)> f = std::bind(&stA::print,&t,std::placeholders::_1,std::placeholders::_2) ;

	myevent.Register(f) ;

	int a = 1,b = 2 ;
	myevent.Notify(a,b) ;

	std::cout<<t.a<<",t,"<<t.b<<std::endl;
	return 0 ;
}
