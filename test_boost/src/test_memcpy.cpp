#include <cstring>
#include <iostream>
int main()
{
	char *p = (char*)malloc(10) ;
	memcpy(p,"luojian",8) ;
	memcpy(p,p,6) ;
	std::cout<<p<<std::endl;
	return 0 ;
}
