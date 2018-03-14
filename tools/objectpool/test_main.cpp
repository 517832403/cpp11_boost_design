#include<iostream>

#include "objectpool.h"
struct BigObject
{
	BigObject(){}
	BigObject(int a){}
	BigObject(const int& a,const int&b){}

	void Print(const std::string& str)
	{
		std::cout<<str<<std::endl;
	}
};

void Print(std::shared_ptr<BigObject> p,const std::string& str)
{
	if(p!=nullptr)
	{
		p->Print(str) ;
	}
}

int main()
{
	ObjectPool<BigObject> pool ;
	pool.Init(2) ;
	{
		auto p = pool.Get() ;
		Print(p,"p") ;
		auto p2 = pool.Get() ;
		Print(p2,"p2") ;

	}

	auto p = pool.Get() ;
	auto p2 = pool.Get() ;

	Print(p,"p") ;
	Print(p2,"p2") ;

	pool.Init(2,1) ;
	auto p3 = pool.Get<int>() ;
	Print(p3,"p3") ;

	auto p4 = pool.Get<int>() ;
	Print(p4,"p4") ;

	pool.Init(2,1,3) ;
	auto p5 = pool.Get<int,int>() ;
	Print(p5,"p5") ;
	pool.Stop() ;
	std::cout<<"what wrong...."<<std::endl;	
	return 0 ;
}
