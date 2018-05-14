#include <iostream>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <string>

int main()
{


	std::string exe_path = boost::filesystem::initial_path<boost::filesystem::path>().string() ;
	std::cout<<exe_path<<std::endl;
	return 0 ;
}
