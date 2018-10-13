#include <iostream>
#include <thread>
#include <mutex>
std::once_flag flag ;
int index = 0 ;
std::mutex g_mutex ;

void do_once()
{
	{
		std::lock_guard<std::mutex> locker(g_mutex) ;
		index++ ;
		std::cout<<std::this_thread::get_id()<<" index:"<<index<<std::endl;
	}
	std::call_once(flag,[](){std::cout<<"call once"<<std::endl;}) ;
}
int main()
{
	std::thread t1(do_once);
	std::thread t2(do_once) ;
	std::thread t3(do_once) ;
	t1.join() ;
	t2.join() ;
	t3.join() ;
	return 0 ;
}
