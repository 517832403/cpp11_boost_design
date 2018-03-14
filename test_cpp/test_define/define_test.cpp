#include <iostream>
#include <string>
#define FixedPointValue \
	std::string str("luojian") ;\
	std::string str1("luojian1") ;\
	std::string str2("luojian2") ;\
	std::string str3("luojian3") ;

#define MAX 100000
#define Integer int64_t

struct SpxInteger
{
	SpxInteger(Integer i)
	{
		val_ = i ;
	}
	Integer val_ ;
};

int main()
{
	FixedPointValue ;
	std::cout<<str<<str1<<str2<<str3<<std::endl;
	
	int64_t diff = 'a' * MAX;
	std::cout<<diff<<std::endl;

	Integer i = diff ;
	std::cout<<"Integer:"<<i<<std::endl;
	SpxInteger val((int8_t)12) ;
	std::cout<<"SpxInteger:"<<val.val_<<std::endl;
	return 0 ;
}
