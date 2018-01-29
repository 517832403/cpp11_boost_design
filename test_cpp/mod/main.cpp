#include <iostream>
int main()
{
	int t1 = 123 ;
	int t_negative = -2;
	int t_positive = 2 ;
	int t2 = -123 ;
	double t3 = -123.123 ;
	std::cout<<t1 % t_negative<<std::endl;
	std::cout<<t1 % t_positive<<std::endl;
	std::cout<<t2 % t_negative<<std::endl;
	std::cout<<t2 % t_positive<<std::endl;
//	std::cout<<t3 % t_negative<<std::endl;
//	std::cout<<t3 % t_positive<<std::endl;
	return 0 ;
}
