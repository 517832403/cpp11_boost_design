#include <boost/smart_ptr.hpp>

int main()
{
	// one ptr two shared_ptr will wrong, with delete ptr twice;
	int * int_ptr = new int(1) ;
	{
	std::shared_ptr<int> sp(int_ptr) ;
	}
	{
	std::shared_ptr<int> sp2(int_ptr) ;
	}
	return 0 ;
}
