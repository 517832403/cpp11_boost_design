#include <boost/smart_ptr.hpp>
#include <assert.h>
int main()
{
	int *p = new int[100] ;
	boost::shared_array<int> sa(p) ;
	boost::shared_array<int> sa2 = sa ;
	sa[0] = 10 ;
	assert(sa2[0]==10) ;
	return 0 ;
}
