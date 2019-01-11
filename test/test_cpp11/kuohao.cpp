#include <iostream>


#define MIN(x,y) ({ \
		decltype(x) _min1 = (x); \
		decltype(y) _min2 = (y); \
		(void) (&_min1 == &_min2);\
		_min1 < _min2 ? _min1 : _min2 ;})

int main()
{
	auto z = MIN(1,2);
	std::cout<<z<<std::endl;
	auto zz = ({int x=1;int y=2; x;});
	return 0 ;
}
