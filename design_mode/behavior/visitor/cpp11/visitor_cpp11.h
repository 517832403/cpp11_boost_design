#include <iostream>
struct stA ;
struct stB ;

template<typename... Args>
struct Visitor ;

template<typename T,typename... Args>
struct Visitor<T,Args...> : Visitor<Args...>
{
	using Visitor<Args...>::Visit ;
	virtual void Visit(const T&) = 0 ;
};

template<typename T>
struct Visitor<T>
{
	virtual void Visit(const T&) = 0 ;
};

struct Base
{
	typedef Visitor<stA,stB> MyVisitor ;
	virtual void Accept(MyVisitor&) = 0 ;
};

struct stA:Base
{
	int val ;
	void Accept(Base::MyVisitor& v)
	{
		v.Visit(*this) ;
	}
};

struct stB:Base
{
	double val ;
	void Accept(Base::MyVisitor& v)
	{
		v.Visit(*this) ;
	}
};

struct PrintVisitor:Base::MyVisitor
{
	void Visit(const stA& a)
	{
		std::cout<<"from stA:"<<a.val<<std::endl;
	}

	void Visit(const stB& b)
	{
		std::cout<<"from  stB:"<<b.val<<std::endl ;
	}
};



