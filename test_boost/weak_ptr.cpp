#include <boost/smart_ptr.hpp>
#include <assert.h>
#include <iostream>
int main()
{
	std::shared_ptr<int> sp(new int(10)) ;
	assert(sp.use_count()==1) ;

	std::weak_ptr<int> wp(sp) ;
	assert(wp.use_count()==1) ;

	if( !wp.expired())
	{
		std::shared_ptr<int> sp2 = wp.lock() ;
		*sp2 = 100 ;
		assert(wp.use_count()==2) ;
	}

	assert(*sp==100) ;
	assert(wp.use_count()==1) ;
	std::cout<<"weak_ptr is spector"<<std::endl;
	return 0 ;
}
