#include <thread>
#include <iostream>
void func()
{
	std::cout<<"func"<<std::endl;
}

int main()

{
	std::thread t(func) ;
	std::thread t2(std::move(t));
	//t.join() ;// invalid operation
	t2.join() ;

	return 0 ;
}
