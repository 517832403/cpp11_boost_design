#include <iostream>

#include "factory.h"

struct base
{
	virtual void Func(){}
	virtual ~base(){}
};

struct DerivedB : public base
{
	DerivedB(int a,double b):m_a(a),m_b(b){}
	void Func() override
	{
		std::cout<<m_a+m_b<<std::endl;
	}
	private:
		int m_a ;
		double m_b ;
};

struct A
{
	A(base* ptr):m_ptr(ptr)
	{}

	~A()
	{
		if(m_ptr != nullptr)
		{
			delete m_ptr ;
			m_ptr = nullptr ;
		}

	}
	void Func()
	{
		m_ptr->Func() ;
	}

	private:
		base* m_ptr ;
};

struct DerivedC:public base
{};

int main()
{
	IocContainer ioc ;
	ioc.Register<A,DerivedC>("C") ;
	auto c = ioc.ResolveShared<A>("C") ;
	
	ioc.Register<A,DerivedB,int,double>("B");
	auto b = ioc.ResolveShared<A>("B",1,2.0) ;
	b->Func() ;
	return 0 ;
}
