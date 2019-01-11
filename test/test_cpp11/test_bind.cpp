#include <iostream>
#include <functional>

void f2(int a,int b,int c){}
void f(){}

int main()
{

	auto b_f0 = std::bind(f,std::placeholders::_1,std::placeholders::_2);
	auto b_f2 = std::bind(f2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	b_f0() ;
	b_f2(1,2,3);
	return 0 ;
}
