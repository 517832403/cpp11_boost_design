#include <iostream>
#include <string>
#include "11cpp_singleton.h"
using namespace std;

struct A
{
	A(const string &x)
	{
		cout<<"lvalue"<<endl;
	}
	A(string && x)
	{
		cout<<"right"<<endl;
	}
};
struct B
{
	B(const string &x)
	{
		cout<<"lvalue"<<endl;
	}
	B(string &&x)
	{
		cout<<"rvalue"<<endl;
	}
};
struct C
{
	C(int x,double y){}
	void fun(){cout<<"test"<<endl;}
};

int main()
{
	string str = "bb";
	Singleton<A>::Instance(str) ;
	Singleton<B>::Instance(std::move(str));
	Singleton<C>::Instance(1,3.14) ;
	return 0 ;
}
