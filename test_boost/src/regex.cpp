#include <boost/regex.hpp>
#include <iostream>
int main()
{
	std::string str = "chinaen 8Glish";
	boost::regex expression("(\\w+)\\s(\\w+)");

	std::cout<<boost::regex_match(str,expression)<<std::endl;
	boost::smatch what ;
	if(boost::regex_search(str,what,expression))
	{
		std::cout<<what[0]<<std::endl;
		std::cout<<what[1]<<std::endl;
		std::cout<<what[2]<<std::endl;
		std::cout<<what[3]<<std::endl;
	}
	return 0 ;
}
