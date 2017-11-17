#include <iostream>
#include <chrono>

int main()
{
	std::chrono::seconds s(1) ;
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds> (s) ;
	ms += std::chrono::milliseconds(2500) ;
	s += std::chrono::duration_cast<std::chrono::seconds>(ms) ;
	std::cout<<"ms:"<<ms.count()<<std::endl;
	std::cout<<"s:"<<s.count()<<std::endl;
	return 0 ;
}
