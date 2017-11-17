#include <iostream>
#include <utility>
#include <future>
#include <thread>
#include <vector>
int func(int x){return x+2;} 

int main()

{
	std::packaged_task<int(int)> task(std::bind(func,std::placeholders::_1)) ;
	std::future<int> fut = task.get_future() ;
	std::thread(std::move(task),2).detach() ;

	fut.wait() ;
	int value = fut.get() ;
	std::cout<<"value:"<<value<<std::endl;

	std::vector<std::shared_future<int>> v ;
	auto f2 = std::async(std::launch::async,[](int a,int b){return a+b;},2,3) ;
	v.push_back(std::forward<std::future<int>>(f2)) ;
	
	std::cout<<"share_future:"<<v[0].get()<<std::endl;
	return 0 ;
}
