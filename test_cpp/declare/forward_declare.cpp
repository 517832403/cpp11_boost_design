#include "forward_declare.h"

#include <iostream>

class A1
{};

template<typename T>
class A2
{
public:
	void t(){ std::cout<<"this is A2"<<std::endl;}
private:
	T t_ ;
};


template<typename T,typename N>
class A3
{
public:
	void tn(){ std::cout<<"this is A3"<<std::endl;
		n.t();
	}
private:
	T t;
	N n;
};


void A4::test()
{
	m->tn();
}
