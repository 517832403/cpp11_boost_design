#include <iostream>

#include "ioc_container.h"

struct IX
{
	virtual ~IX(){}
	virtual void g(){}
};

struct X : public IX
{
	public:
		void g() override
		{
			std::cout<<"it is a test in x"<<std::endl;
		}
};

class Y : public IX
{
	public:
		Y(int a):m_a(a){}
		void g() override
		{
			std::cout<<"it is a test in Y"<<std::endl;
		}
		
	public:
		int m_a ;
};

struct MyA
{
	public:
		MyA(IX *x):m_x(x) {}

		~MyA()
		{
			delete m_x ;
			m_x = nullptr ;
		}
		void Fun()
		{
			m_x->g() ;
		}
	private:
		IX* m_x ;
};

int main()
{
	IocContainer ioc ;
	ioc.RegisterType<MyA,X>("A") ;
	auto pa = ioc.ResolveShared<MyA>("A") ;
	pa->Fun() ;

	ioc.RegisterType<MyA,Y,int>("A1") ;
	auto pa1 = ioc.ResolveShared<MyA>("A1",2) ;
	pa1->Fun() ;


	return 0 ;
}
