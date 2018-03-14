#include <chrono>
#include <iostream>

#include "thread_task_pool.h"

int main()
{
	ThreadPool pool(2) ;
	//pool.Start(2) ;
	std::thread thd1([&pool]{
			for(int32_t i  = 0 ;i<10 ;i++)
			{
				auto threadid = std::this_thread::get_id() ;
				pool.AddTask([threadid]
						{
							std::cout<<"sync thread id is:"<< threadid<<std::endl;
						}) ;
				std::this_thread::sleep_for(std::chrono::microseconds(10));
			}
			}) ;
	
	std::thread thd2([&pool]{
			for(int32_t i  = 0 ;i<10 ;i++)
			{
				auto threadid = std::this_thread::get_id() ;
				pool.AddTask([threadid]
						{
							std::cout<<"sync thread id is:"<< threadid<<std::endl;
						}) ;
				std::this_thread::sleep_for(std::chrono::microseconds(10));
			}
			}) ;
	std::this_thread::sleep_for(std::chrono::seconds(2)) ;
	pool.Stop() ;
	thd1.join() ;
	thd2.join() ;
	return 0 ;
}
