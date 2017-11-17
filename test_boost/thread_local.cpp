#include <thread>
#include <iostream>
#include <string>
#include <mutex>

static thread_local int rage = 1 ;
std::mutex cout_mutex  ;
void increase_rage(const std::string & thread_name)
{
	++ rage ;
	std::lock_guard<std::mutex> lock(cout_mutex) ;
	std::cout<<"rage count for "<< thread_name << ":"<<rage <<std::endl;
	std::cout<<"address:"<< &rage << std::endl;
}

int main()
{
	std::thread a(increase_rage,"a"),b(increase_rage,"b") ;
	{
		std::lock_guard<std::mutex> lock(cout_mutex) ;
		std::cout<<"rage count for main:"<<rage<<" address:"<<&rage<<std::endl;
	}
	a.join() ;
	b.join() ;
	return 0 ;
}
