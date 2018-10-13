#include <thread>
#include <iostream>

int main()
{
	std::thread t ;
	//std::cout<<t<<std::endl;
	/* 1. a thread is finished,but not yet been joined is still considered an active thread of execution and is therefore joinable.
	 * 2. the default constuct thread is considered to been a unjoinable.
	 */
	if(t.joinable())
	{
		std::cout<<"joinable"<<std::endl;
		t.join() ;
	}
	return 0 ;
}
