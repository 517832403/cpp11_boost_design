#include <boost/algorithm/string.hpp>
#include <iostream>
using namespace boost ;


int main()
{
	std::string str("I Don't know\n") ;
	std::cout<<to_upper_copy(str)<<std::endl;
	std::cout<<str<<std::endl;
	to_lower(str) ;
	std::cout<< str<<std::endl;


	

	return 0 ;
}
