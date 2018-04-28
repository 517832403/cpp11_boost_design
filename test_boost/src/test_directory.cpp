
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>


std::string g_path("/home/luojian/github/cpp11_boost_design/test_boost/") ;
int main()
{
	boost::filesystem::path plugin_path(g_path) ;
	if(!boost::filesystem::is_directory(plugin_path))
	{
		std::cout<<"is not a directory "<<g_path<<std::endl;
		return 0 ;
	}
	boost::regex expression(".*\.cpp");
	boost::filesystem::directory_iterator end_iter ;
	for(boost::filesystem::directory_iterator iter(plugin_path); iter != end_iter; ++iter)
	{
		if(!boost::filesystem::is_regular_file(iter->status()))
		{
			std::cout<<"it is not a regular file :"<<iter->path().leaf().string()<<std::endl;
			continue ;
		}
		if(!boost::regex_match(iter->path().leaf().string(),expression))
		{
			std::cout<<"it is not a cpp file : "<<iter->path().leaf().string()<<std::endl;
			continue ;
		}
		std::cout<<iter->path().leaf().string()<<std::endl;
	}
	return 0 ;
}

