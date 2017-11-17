#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>

int main()

{
	boost::format fmt("|%s|\n") ;

	std::string str = " samus aran   " ;

	std::cout<< fmt % boost::trim_copy(str) <<std::endl;

	std::cout<< fmt % boost::trim_left_copy(str) <<std::endl;

	boost::trim_right(str) ;

	std::cout<< fmt % str <<std::endl;

	std::string str2 = "2010 Happy new year !!!" ;

	std::cout<< fmt % boost::trim_left_copy_if(str2,boost::is_digit()) ;

	std::cout<< fmt % boost::trim_right_copy_if(str2,boost::is_punct()) ;

	std::cout<< fmt % boost::trim_copy_if(str2,boost::is_punct()|| boost::is_digit()|| boost::is_space()) ;

	return 0 ;
}
