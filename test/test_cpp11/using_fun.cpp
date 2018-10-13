#include <iostream>
class A
{
	public:
		A(){std::cout<<"A constructor"<<std::endl;}
		void fun(){std::cout<<"A fun"<<std::endl;}
};

class B:public A
{
public:
	using A::A ;	
	using A::fun;
	
	B(int a):A()
	{
		a_ = a ;
		std::cout<<"a:"<<a<<std::endl;
	}

	void fun(int a)
	{
		std::cout<<"B a:"<<a<<std::endl;
		a_ = a ;
	}
private:
		int a_ ;
};

int main()
{
	B *b = new B(10) ;
	b->fun() ;
	b->fun(100) ;
	return 0 ;
}
