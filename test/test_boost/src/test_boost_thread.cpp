#include <iostream>
#include <boost/thread/thread.hpp>
#include <cstdlib>
using namespace std;

volatile bool isRunning = true ;
void func1()
{
	static int cnt = 0 ;
	while(isRunning)
	{
		cout<< "func1:"<< cnt ++ <<endl;
		sleep(1) ;
	}
}


void func2()
{
	static int cnt2 = 0 ;
	while(isRunning)
	{
		cout<<"func2:"<< cnt2 ++ <<endl;
		sleep(1) ;
	}
}


int main()
{
	boost::thread thread1(&func1) ;
	boost::thread thread2(&func2) ;
	sleep(10);
	isRunning = false ;
	thread1.join() ;
	thread2.join() ;
	cout<<"exit"<<endl;
        sleep(1) ; 	
	return 0 ;
}





