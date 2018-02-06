#include <chrono>
#include <ctime>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

std::string GetLocalTime()
{
	std::chrono::system_clock::time_point now = 
		std::chrono::system_clock::now() ;
	std::chrono::time_point<std::chrono::system_clock,std::chrono::microseconds> ms = std::chrono::time_point_cast<std::chrono::microseconds>(now) ;

	std::time_t t= std::chrono::system_clock::to_time_t(now) ;
	std::tm tm = *std::localtime(&t) ;

	char mbstr[64] = {0} ;
	std::strftime(mbstr,64,"%Y-%m-%d %H:%M:%S.",&tm) ;
	std::stringstream ss ;
	ss << mbstr ;
	ss << std::setw(6) << std::setfill('0')<<ms.time_since_epoch().count() % 1000000 ;
	return ss.str() ;
}

int main()
{
	for(int i = 0 ;i <10 ;i++)
	{
		std::cout<<GetLocalTime()<<std::endl;
	}
	return 0 ;
}
