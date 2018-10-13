#include <iostream>
#include <typeinfo>
typedef union Fixed{
 unsigned char full;
 struct part
 {
 	unsigned char fraction:7;
	unsigned char integer:1 ;
 }part;
}FIXED;

#define SHIFT (1<<16) 
int main()
{
	FIXED fixed,fixed_1 ;
	fixed.full = 1;
	fixed_1.full = 1 ;
	auto result = (fixed.full << 7)+(fixed_1.full << 7)  ;
	std::cout<<" int:"<<typeid(int32_t).name()<<std::endl;
	std::cout<<" double:"<<typeid(double).name()<<std::endl;
	std::cout<<"result:"<<result<<" name:"<<typeid(result).name()<<std::endl;
	double dd = 1.512 ;
	double dd2=1.512 ;
	long tmp1 = dd*SHIFT ;
	long tmp2 = dd2*SHIFT ;
	long l_result = tmp1 + tmp2 ;
	double dd_result = (double)(l_result) / SHIFT ;
	std::cout<<"dd_result:"<<dd_result<<std::endl;
	std::cout<<"result raw:"<<dd + dd2<<std::endl;
	return 0 ;
}
