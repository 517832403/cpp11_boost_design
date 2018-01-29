#include <iostream>
#include <string>
#define FixedPointValue \
	std::string str("luojian") ;\
	std::string str1("luojian1") ;\
	std::string str2("luojian2") ;\
	std::string str3("luojian3") ;

#define MAX 100000000

int main()
{
	FixedPointValue ;
	std::cout<<str<<str1<<str2<<str3<<std::endl;
	
	int64_t diff = 'a' * MAX;
	std::cout<<diff<<std::endl;
	return 0 ;
}
