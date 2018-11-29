#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/cat.hpp>
#include <iostream>

#define SEQ ((Y,W))((X,Y))((Y,X))

#define MACRO(r,data,elem) BOOST_PP_TUPLE_ELEM(2,1,elem)::GetInstance(r);


class W
{
	public:
	static void GetInstance(int i)
	{
		std::cout<<"WWW:"<<i<<std::endl;
	}
};
class X
{
	public:
	static void GetInstance(int i)
	{
		std::cout<<"XXXX:"<<i<<std::endl;
	}
};
class Y
{
	public:
	static void GetInstance(int i)
	{
		std::cout<<"YYY:"<<i<<std::endl;
	}
};


int main()
{
	BOOST_PP_SEQ_FOR_EACH(MACRO,_,SEQ)	
	return 0 ;
}
