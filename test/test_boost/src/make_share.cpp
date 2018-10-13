#include <boost/make_shared.hpp>
#include <vector>
#include <iostream>

int main()
{
	typedef std::vector<std::shared_ptr<int>> vs ;
	vs v(10) ;

	int i = 0 ;
	for(vs::iterator pos = v.begin();pos != v.end();++pos)
	{
		(*pos) = std::make_shared<int>(++i) ;
		std::cout<< *(*pos) <<",";
	}
	std::cout<< std::endl;

	std::shared_ptr<int> p = v[9] ;
	*p = 100 ;
	std::cout<< *v[9] <<std::endl;
	return 0 ;
}
